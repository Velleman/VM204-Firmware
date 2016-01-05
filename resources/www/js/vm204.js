function requestSettings() {
    var e = new Object;
    e = $.ajax({
        type: "GET",
        url: "/cgi/settings_json.shtml",
        dataType: "text",
        data: $(this).serialize(),
        success: function(e) {
            try {
                json = $.parseJSON(e), update_content()
            } catch (t) {
                console.log(t)
            }
        }
    })
}

function isElementVisible(e) {
    var t = $(window).scrollTop(),
        a = $(e).offset().top,
        n = a + $(e).height();
    return n >= t
}

function update_content() {
    update_auth_settings(), update_network_settings(), update_email_settings(), update_names(), update_notif_settings()
}

function update_auth_settings() {
    var e = $("#login_field"),
        t = $("#password_field");
    e.val(json.authentication.login), t.val(json.authentication.password)
}

function update_email_settings() {
    var e = $("#smtp_server"),
        t = $("#smtp_port"),
        a = $("#smtp_user"),
        n = $("#smtp_pass"),
        s = $("#smtp_tls");
    e.val(json.email.smtpserver), t.val(json.email.smtpport), a.val(json.email.username), n.val(json.email.password), s.prop("checked", json.email.usessltls)
}

function update_network_settings() {
    var e = $("#value_terminalport"),
        t = $("#value_webserverport"),
        a = $("#dhcp_enabled_checkbox"),
        n = $("#value_ipaddress"),
        s = $("#value_gateway"),
        l = $("#value_subnetmask"),
        o = $("#value_primarydns"),
        i = $("#value_secondarydns");
    e.val(json.network.terminalport), t.val(json.network.webserverport), a.prop("checked", json.network.dhcpenable), n.val(json.network.ipaddress), s.val(json.network.gateway), l.val(json.network.subnetmask), o.val(json.network.primarydns), i.val(json.network.secondarydns)
}

function update_names() {
    var e = $("#name_card"),
        t = $("#name_relay1"),
        a = $("#name_relay2"),
        n = $("#name_relay3"),
        s = $("#name_relay4"),
        l = $("#pulse_relay1"),
        o = $("#pulse_relay2"),
        i = $("#pulse_relay3"),
        r = $("#pulse_relay4"),
        u = $("#name_input1"),
        c = $("#name_input2"),
        d = $("#name_input3"),
        m = $("#name_input4"),
        p = $("#name_analog"),
        v = $("#name_custom_js"),
        _ = $("#name_custom_css");
    t.val(json.io.relays[0].name), a.val(json.io.relays[1].name), n.val(json.io.relays[2].name), s.val(json.io.relays[3].name), $(".r1Name").html(json.io.relays[0].name), $(".r2Name").html(json.io.relays[1].name), $(".r3Name").html(json.io.relays[2].name), $(".r4Name").html(json.io.relays[3].name), u.val(json.io.inputs[0].name), c.val(json.io.inputs[1].name), d.val(json.io.inputs[2].name), m.val(json.io.inputs[3].name), l.val(json.io.relays[0].time), o.val(json.io.relays[1].time), i.val(json.io.relays[2].time), r.val(json.io.relays[3].time), $("#i1Name").html(json.io.inputs[0].name), $("#i2Name").html(json.io.inputs[1].name), $("#i3Name").html(json.io.inputs[2].name), $("#i4Name").html(json.io.inputs[3].name), p.val(json.io.analog.name), v.val(json.customjs), _.val(json.customcss), e.val(json.cardname)
}

function update_notif_settings() {
    var e, t = notif_select.val();
    t || (t = 0), e = json.notifications[t], $("#notif_enabled_checkbox").prop("checked", e.enable), $("#recipient_field").val(e.recipients), $("#alarmvalue_field").val(json.io.analog.alarmvalue), 9 == notif_select.val() ? $("#alarmvalue_div").show() : $("#alarmvalue_div").hide()
}

function sendRelay(e, t) {
    relaysettings = "OFF" == $(t).html() ? "/" + e + "/on" : "/" + e + "/off";
    $.ajax({
        type: "POST",
        url: "/relay" + relaysettings,
        dataType: "text",
        data: relaysettings,
        success: function(e) {
            try {
                updateIO(e)
            } catch (t) {
                console.log(t)
            }
        }
    })
}

function sendPulse(e) {
    {
        var t = "/" + e;
        $.ajax({
            type: "POST",
            url: "/relay" + t + "/pulse",
            dataType: "text",
            data: "pulse",
            success: function(e) {
                try {
                    updateIO(e)
                } catch (t) {
                    console.log(t)
                }
            }
        })
    }
}

function timerClearEvent() {
    $("#statuslabel").text("")
}

function sendEmailSettings() {
    var e = {
        smtpserver: $("#smtp_server").val(),
        smtpport: $("#smtp_port").val(),
        user: $("#smtp_user").val(),
        password: $("#smtp_pass").val(),
        tls: $("#smtp_tls").prop("checked") ? 1 : 0
    };
    $("#sendMailSettingsButton").html("SAVING...");
    $.ajax({
        type: "POST",
        url: "/email_settings",
        dataType: "text",
        data: e,
        success: function(e) {
            "OK" == e ? ($("#sendMailSettingsButton").html("SAVED"), requestSettings()) : console.log("FAILED TO SAVE EMAILSETTINGS")
        }
    })
}

function sendRegenerateAPIKey() {
    $.ajax({
        type: "GET",
        url: "/regenerate_api",
        dataType: "text",
        success: function(e) {
            var t = $.parseJSON(e);
            $("#api_key").val(t.ApiKey)
        }
    })
}

function sendRequestBootloader() {
    $.ajax({
        type: "GET",
        url: "/bootloader",
        dataType: "text",
        success: function() {}
    })
}

function sendAlarm() {
	
	if(validateEmail($("#recipient_field").val()))
	{
		var e = {
			alarm: $("#notification_select").val(),
			enable: $("#notif_enabled_checkbox").is(":checked") ? 1 : 0,
			recipient: $("#recipient_field").val(),
			alarmvalue: $("#alarmvalue_field").val()
		};
		$("#sendAlarmButton").html("SAVING...");
		$.ajax({
			type: "POST",
			url: "/alarm_settings",
			dataType: "text",
			data: e,
			success: function(e) {
				try {
					"OK" == e ? ($("#sendAlarmButton").html("SAVED"), requestSettings()) : console.log("FAILED TO SAVE EMAILSETTINGS")
				} catch (t) {
					console.log(t)
				}
			}
		})
	}
	else
	{
		$("#sendAlarmButton").html("INVALID EMAIL ADDRESS");
		setTimeout(function(){$("#sendAlarmButton").html("Save");}, 5000);
	}
}

function validateEmail(email) {
	var emails = email.split(";");
	var valid = false;
	var re = /^([\w-]+(?:\.[\w-]+)*)@((?:[\w-]+\.)*\w[\w-]{0,66})\.([a-z]{2,6}(?:\.[a-z]{2})?)$/i;
	for(var i = emails.length; i>0;i--)
	{
		if(!re.test(emails[i-1]))
		{
			valid = false;
			break;
		}
		else
		{
			valid = true;
		}
		
	}
    return valid
}

function sendAuthSettings() {
    var e = {
        login: $("#login_field").val(),
        password: $("#password_field").val()
    };
    $("#sendAuthSettingsButton").html("SAVING...");
    $.ajax({
        type: "POST",
        url: "/auth_settings",
        dataType: "text",
        data: e,
        success: function(e) {
            try {
                "OK" == e ? ($("#sendAuthSettingsButton").html("SAVED"), requestSettings()) : ($("#sendAuthSettingsButton").html("FAILED SAVING"), console.log("FAILED TO SAVE EMAILSETTINGS"))
            } catch (t) {
                console.log(t)
            }
        }
    })
}

function ValidateIPaddress(e) {
    return /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/.test(e) ? !0 : (alert("You have entered an invalid IP address!"), !1)
}

function sendNetworkSettings() {
    if (ValidateIPaddress($("#value_ipaddress").val()) && ValidateIPaddress($("#value_gateway").val()) && ValidateIPaddress($("#value_subnetmask").val()) && ValidateIPaddress($("#value_primarydns").val()) && ValidateIPaddress($("#value_secondarydns").val())) {
		if($("#value_webserverport").val() > 0)
		{
			var e = {
				webserverport: $("#value_webserverport").val(),
				dhcpenable: $("#dhcp_enabled_checkbox").is(":checked") ? 1 : 0,
				ipaddress: $("#value_ipaddress").val(),
				gateway: $("#value_gateway").val(),
				subnetmask: $("#value_subnetmask").val(),
				primarydns: $("#value_primarydns").val(),
				secondarydns: $("#value_secondarydns").val()
			};
			
			$("#sendNetworkSettingsButton").html("SAVING..."); {
				$.ajax({
					type: "POST",
					url: "/network_settings",
					dataType: "text",
					data: e,
					success: function(e) {
						try {
							"OK" == e ? ($("#sendNetworkSettingsButton").html("SAVED"), requestSettings()) : console.log("FAILED TO SAVE NETWORKSETTINGS")
						} catch (t) {
							console.log(t)
						}
					}
				})
			}
		}
		else
		{
			$("#sendNetworkSettingsButton").html("INVALID PORT NUMBER");
		}
    } else $("#sendNetworkSettingsButton").html("INVALID IP ADDRESSES")
}

function sendNames() {
    var e = {
        r1: $("#name_relay1").val(),
        r2: $("#name_relay2").val(),
        r3: $("#name_relay3").val(),
        r4: $("#name_relay4").val(),
        p1: $("#pulse_relay1").val(),
        p2: $("#pulse_relay2").val(),
        p3: $("#pulse_relay3").val(),
        p4: $("#pulse_relay4").val(),
        i1: $("#name_input1").val(),
        i2: $("#name_input2").val(),
        i3: $("#name_input3").val(),
        i4: $("#name_input4").val(),
        an: $("#name_analog").val(),
        js: $("#name_custom_js").val(),
        css: $("#name_custom_css").val(),
        cardname: $("#name_card").val()
    };
	
    $("#sendNameSettingsButton").html("SAVING...");
    $.ajax({
        type: "POST",
        url: "/names",
        dataType: "text",
        data: e,
        success: function(e) {
            try {
                "OK" == e ? ($("#sendNameSettingsButton").html("SAVED"), requestSettings()) : console.log("FAILED TO SAVE EMAILSETTINGS")
            } catch (t) {
                console.log(t)
            }
        }
    })
}

function sliderOnInitialized() {
    $("body").css("display", "block")
}

function timerRelayEvent() {

	if(location.pathname == "/index.shtml" || location.pathname =="/")
	{
		$.ajax({
			type: "GET",
			url: "/status",
			dataType: "text",
			success: function(e) {
				try {
					updateIO(e), setTimeout(function() {
						timerRelayEvent()
					}, 500)
				} catch (t) {
					console.log(t)
				}
			}
		})
	}
}

function updateSettings(e) {
    e.authentication.login
}

function updateIO(e) {
    var t = $.parseJSON(e);
    try {
        var a;
        for (a = 1; 4 >= a; a++) $("#relay" + a + "Status").html(t.relays[a - 1] ? "ON" : "OFF"), $("#pulse" + a + "Status").html(t.pulse[a - 1] ? "ACTIVE" : "ACTIVATE"), $("#input" + a + "Status").html(t.inputs[a - 1] ? "ON" : "OFF");
        var n = t.analog / 1023;
        n *= 3.3, n *= 2, $("#analogLabel").text("Analog value: " + n.toFixed(2) + "V")
    } catch (s) {
        console.log(s)
    }
}

function testEmailSettings() {
    $.ajax({
        type: "POST",
        url: "/testmail",
        dataType: "text",
        success: function(e) {
            try {
                var jsonMail = $.parseJSON(e);
                $("#testMailSettingsButton").html(jsonMail.status);
            } catch (t) {
                console.log(t)
            }
        }
    })
}

function enableButtons() {
    var e;
    for (e = 1; 4 >= e; e++) $("#relay" + e + "Status").removeClass("pure-button-disabled"), $("#pulse" + e + "Status").removeClass("pure-button-disabled")
}
var json, notif_select = new Object;
$(document).ready(function() {
    requestSettings(), notif_select = $("#notification_select"), notif_select.change(update_notif_settings), $("#splashscreen").delay(750).fadeOut(500), enableButtons()
});
var current_slide = 0;
$(function() {
    $("#sendMailButton").removeAttr("disabled"), timerRelayEvent(), $("#relay1Status").click(function() {
        sendRelay(1, this)
    }), $("#relay2Status").click(function() {
        sendRelay(2, this)
    }), $("#relay3Status").click(function() {
        sendRelay(3, this)
    }), $("#relay4Status").click(function() {
        sendRelay(4, this)
    }), $("#pulse1Status").click(function() {
        sendPulse(1, this)
    }), $("#pulse2Status").click(function() {
        sendPulse(2, this)
    }), $("#pulse3Status").click(function() {
        sendPulse(3, this)
    }), $("#pulse4Status").click(function() {
        sendPulse(4, this)
    }), $("#sendAuthSettingsButton").click(function() {
        return sendAuthSettings(), !1
    }), $("#sendNetworkSettingsButton").click(function() {
        return sendNetworkSettings(), !1
    }), $("#sendMailSettingsButton").click(function() {
        return sendEmailSettings(), !1
    }), $("#sendNameSettingsButton").click(function() {
        return sendNames(), !1
    }), $("#sendAlarmButton").click(function() {
        return sendAlarm(), !1
    }), $("#regeneratekeyButton").click(function() {
        return sendRegenerateAPIKey(), !1
    }), $("#requestBootloader").click(function() {
        return sendRequestBootloader(), !1
    }), $("#testMailSettingsButton").click(function() {
		$("#testMailSettingsButton").html("Sending...")
        $.ajax({
        type: "POST",
        url: "/testmail",
        dataType: "text",
        success: function(e) {
            try {
                var jsonMail = $.parseJSON(e);
                var jsonMail = $.parseJSON(e);
                $("#testMailSettingsButton").html(jsonMail.status)
                setTimeout(function(){$("#testMailSettingsButton").html("Test Mail Settings");}, 5000);
            } catch (t) {
                console.log(t)
            }
        }
    })
    })
});