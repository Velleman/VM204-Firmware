function requestSettings() {
    var e = new Object;
    e = $.ajax({
        type: "GET",
        url: "/cgi/settings_json.shtml",
        dataType: "text",
        data: $(this).serialize(),
        success: function(e, t) {
            try {
                json = $.parseJSON(e);
                update_content()
            } catch (n) {
                console.log(n)
            }
        }
    })
}

function isElementVisible(e) {
    var t = $(window).scrollTop();
    var n = $(e).offset().top;
    var r = n + $(e).height();
    return r >= t
}

function update_content() {
    update_auth_settings();
    update_network_settings();
    update_email_settings();
    update_names();
    update_notif_settings()
}

function update_auth_settings() {
    var e = $("#login_field");
    var t = $("#password_field");
    e.val(json.authentication.login);
    t.val(json.authentication.password)
}

function update_email_settings() {
    var e = $("#smtp_server");
    var t = $("#smtp_port");
    var n = $("#smtp_user");
    var r = $("#smtp_pass");
	var s = $("#smtp_tls")
    e.val(json.email.smtpserver);
    t.val(json.email.smtpport);
    n.val(json.email.username);
    r.val(json.email.password);
	s.prop("checked", json.email.usessltls);
}

function update_network_settings() {
    var e = $("#value_terminalport");
    var t = $("#value_webserverport");
    var n = $("#dhcp_enabled_checkbox");
    var r = $("#value_ipaddress");
    var i = $("#value_gateway");
    var s = $("#value_subnetmask");
    var o = $("#value_primarydns");
    var u = $("#value_secondarydns");
    e.val(json.network.terminalport);
    t.val(json.network.webserverport);
    n.prop("checked", json.network.dhcpenable);
    r.val(json.network.ipaddress);
    i.val(json.network.gateway);
    s.val(json.network.subnetmask);
    o.val(json.network.primarydns);
    u.val(json.network.secondarydns)
}

function update_names() {
	var c = $("#name_card");
    var e = $("#name_relay1");
    var t = $("#name_relay2");
    var n = $("#name_relay3");
    var r = $("#name_relay4");
    var i = $("#name_input1");
    var s = $("#name_input2");
    var o = $("#name_input3");
    var u = $("#name_input4");
    var a = $("#name_analog");
	var js = $("#name_custom_js");
	var css = $("#name_custom_css");
    e.val(json.io.relays[0].name);
    t.val(json.io.relays[1].name);
    n.val(json.io.relays[2].name);
    r.val(json.io.relays[3].name);
    $("#r1Name").html(json.io.relays[0].name);
    $("#r2Name").html(json.io.relays[1].name);
    $("#r3Name").html(json.io.relays[2].name);
    $("#r4Name").html(json.io.relays[3].name);
    i.val(json.io.inputs[0].name);
    s.val(json.io.inputs[1].name);
    o.val(json.io.inputs[2].name);
    u.val(json.io.inputs[3].name);
    $("#i1Name").html(json.io.inputs[0].name);
    $("#i2Name").html(json.io.inputs[1].name);
    $("#i3Name").html(json.io.inputs[2].name);
    $("#i4Name").html(json.io.inputs[3].name);
    a.val(json.io.analog.name)
	js.val(json.customjs);
	css.val(json.customcss);
	c.val(json.cardname);
}

function update_notif_settings() {
    var e;
	var selectedNotifValue = notif_select.val();
	if(!selectedNotifValue)
	{
		selectedNotifValue = 0;
	}
    e = json.notifications[selectedNotifValue];
	
	$("#notif_enabled_checkbox").prop("checked", e.enable);
    $("#recipient_field").val(e.recipients)
	$("#alarmvalue_field").val(json.io.analog.alarmvalue);
    if (notif_select.val() == 9) 
		$("#alarmvalue_field").show();
    else 
		$("#alarmvalue_field").hide();
    
   
}

function sendRelay(e, t) {
    if ($(t).html() == "OFF") {
        relaysettings = "/" + e + "/on"
    } else {
        relaysettings = "/" + e + "/off"
    }
    var n = $.ajax({
        type: "POST",
        url: "/relay" + relaysettings,
        dataType: "text",
        data: relaysettings,
        success: function(e, t) {
            try {
                updateIO(e)
            } catch (n) {
                console.log(n)
            }
        }
    })
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
		tls: $('#smtp_tls').prop('checked') ? 1 : 0
    };

	
    $("#emailSettingsStatus").html("SAVING...");
    var t = $.ajax({
        type: "POST",
        url: "/email_settings",
        dataType: "text",
        data: e,
        success: function(e, t) {
            if (e == "OK") {
                $("#emailSettingsStatus").html("SAVED");
                requestSettings()
            } else {
                console.log("FAILED TO SAVE EMAILSETTINGS")
            }
        }
    })
}

function sendRegenerateAPIKey(){
	var t = $.ajax({
        type: "GET",
        url: "/regenerate_api",
        dataType: "text",
        success: function(e, t) { 
				var api =  $.parseJSON(e);
                $("#api_key").val(api.ApiKey);          
        }
    })
}

function sendRequestBootloader(){
	var t = $.ajax({
        type: "GET",
        url: "/bootloader",
        dataType: "text",
        success: function(e, t) {          
                
        }
    })
}

function sendAlarm() {
    var e = {
        alarm: $("#notification_select").val(),
        enable: $("#notif_enabled_checkbox").is(":checked") ? 1 : 0,
        recipient: $("#recipient_field").val(),
        alarmvalue: $("#alarmvalue_field").val()
    };
    $("#sendAlarmButton").html("SAVING...");
    var t = $.ajax({
        type: "POST",
        url: "/alarm_settings",
        dataType: "text",
        data: e,
        success: function(e, t) {
            try {
                if (e == "OK") {
                    $("#sendAlarmButton").html("SAVED");
                    requestSettings()
                } else {
                    console.log("FAILED TO SAVE EMAILSETTINGS")
                }
            } catch (n) {
                console.log(n)
            }
        }
    })
}

function sendAuthSettings() {
    var e = {
        login: $("#login_field").val(),
        password: $("#password_field").val()
    };
    $("#sendAuthSettingsButton").html("SAVING...");
    var t = $.ajax({
        type: "POST",
        url: "/auth_settings",
        dataType: "text",
        data: e,
        success: function(e, t) {
            try {
                if (e == "OK") {
                    $("#sendAuthSettingsButton").html("SAVED");
                    requestSettings();
                } else {
                    $("#sendAuthSettingsButton").html("FAILED SAVING");
                    console.log("FAILED TO SAVE EMAILSETTINGS")
                }
            } catch (n) {
                console.log(n)
            }
        }
    })
}

function ValidateIPaddress(e) {
    if (/^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/.test(e)) {
        return true
    }
    alert("You have entered an invalid IP address!");
    return false
}

function sendNetworkSettings() {
    if (ValidateIPaddress($("#value_ipaddress").val()) && ValidateIPaddress($("#value_gateway").val()) && ValidateIPaddress($("#value_subnetmask").val()) && ValidateIPaddress($("#value_primarydns").val()) && ValidateIPaddress($("#value_secondarydns").val())) {
        var e = {
            terminalport: $("#value_terminalport").val(),
            webserverport: $("#value_webserverport").val(),
            dhcpenable: $("#dhcp_enabled_checkbox").is(":checked") ? 1 : 0,
            ipaddress: $("#value_ipaddress").val(),
            gateway: $("#value_gateway").val(),
            subnetmask: $("#value_subnetmask").val(),
            primarydns: $("#value_primarydns").val(),
            secondarydns: $("#value_secondarydns").val()
        };
        $("#sendNetworkSettingsButton").html("SAVING...");
        var t = $.ajax({
            type: "POST",
            url: "/network_settings",
            dataType: "text",
            data: e,
            success: function(e, t) {
                try {
                    if (e == "OK") {
                        $("#sendNetworkSettingsButton").html("SAVED");
                        requestSettings()
                    } else {
                        console.log("FAILED TO SAVE NETWORKSETTINGS")
                    }
                } catch (n) {
                    console.log(n)
                }
            }
        })
    } else {
        $("#sendNetworkSettingsButton").html("INVALID IP ADDRESSES")
    }
}

function sendNames() {
    var e = {
        r1: $("#name_relay1").val(),
        r2: $("#name_relay2").val(),
        r3: $("#name_relay3").val(),
        r4: $("#name_relay4").val(),
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
    var t = $.ajax({
        type: "POST",
        url: "/names",
        dataType: "text",
        data: e,
        success: function(e, t) {
            try {
                if (e == "OK") {
                    $("#sendNameSettingsButton").html("SAVED");
                    requestSettings()
                } else {
                    console.log("FAILED TO SAVE EMAILSETTINGS")
                }
            } catch (n) {
                console.log(n)
            }
        }
    })
}

function sliderOnInitialized(e, t) {
    $("body").css("display", "block")
}

function timerRelayEvent() {
    var e = $.ajax({
        type: "GET",
        url: "/status",
        dataType: "text",
        success: function(e, t) {
            try {
                updateIO(e);               
                setTimeout(function(){timerRelayEvent()}, 500);
            } catch (n) {
                console.log(n)
            }
        }
    })
}

function updateSettings(e) {
    var t = e.authentication.login
}

function updateIO(e) {
    var t = 0;
    var n = $.parseJSON(e);
    try {
	var i;
		for(i=1; i<=4;i++)
		{
			n.relays[i-1] ? $("#relay"+i+"Status").html("ON") : $("#relay"+i+"Status").html("OFF");
			n.inputs[i-1] ? $("#input"+i+"Status").html("ON") : $("#input"+i+"Status").html("OFF");
		}
		var analogValue = n.analog / 1023;
		analogValue *=3.3;
		analogValue *=2;
        $("#analogLabel").text("Analog Value: " + analogValue.toFixed(2) + "V")
    } catch (r) {console.log(r);}
}
var json;
var notif_select = new Object;
$(document).ready(function() {
    requestSettings();
    notif_select = $("#notification_select");
    notif_select.change(update_notif_settings)
});
var current_slide = 0;
$(function() {
    if ($.browser.msie) {
        $(".header").corner("top 30px");
        $(".footer").corner("bottom 30px")
    }
    $("#sendMailButton").removeAttr("disabled");
    timerRelayEvent();
    $("#relay1Status").click(function() {
        sendRelay(1, this)
    });
    $("#relay2Status").click(function() {
        sendRelay(2, this)
    });
    $("#relay3Status").click(function() {
        sendRelay(3, this)
    });
    $("#relay4Status").click(function() {
        sendRelay(4, this)
    });
    $("#sendAuthSettingsButton").click(function() {
        sendAuthSettings();
        return false
    });
    $("#sendNetworkSettingsButton").click(function() {
        sendNetworkSettings();
        return false
    });
    $("#sendMailSettingsButton").click(function() {
        sendEmailSettings();
        return false
    });
    $("#sendNameSettingsButton").click(function() {
        sendNames();
        return false
    });
    $("#sendAlarmButton").click(function() {
        sendAlarm();
        return false
    })
	$("#regeneratekeyButton").click(function() {
        sendRegenerateAPIKey();
        return false
    })
	$("#requestBootloader").click(function() {
        sendRequestBootloader();
        return false
    })
});