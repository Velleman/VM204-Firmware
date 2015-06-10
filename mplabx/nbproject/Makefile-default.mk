#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../common/date_time.c ../common/endian.c ../common/path.c ../common/resource_manager.c ../common/str.c ../common/os_port_freertos.c ../cyclone_crypto/aes.c ../cyclone_crypto/aria.c ../cyclone_crypto/asn1.c ../cyclone_crypto/base64.c ../cyclone_crypto/camellia.c ../cyclone_crypto/cipher_mode_cbc.c ../cyclone_crypto/cipher_mode_ccm.c ../cyclone_crypto/cipher_mode_cfb.c ../cyclone_crypto/cipher_mode_ctr.c ../cyclone_crypto/cipher_mode_ecb.c ../cyclone_crypto/cipher_mode_gcm.c ../cyclone_crypto/cipher_mode_ofb.c ../cyclone_crypto/des.c ../cyclone_crypto/des3.c ../cyclone_crypto/dh.c ../cyclone_crypto/dsa.c ../cyclone_crypto/ec.c ../cyclone_crypto/ec_curves.c ../cyclone_crypto/ecdh.c ../cyclone_crypto/ecdsa.c ../cyclone_crypto/hmac.c ../cyclone_crypto/idea.c ../cyclone_crypto/md2.c ../cyclone_crypto/md4.c ../cyclone_crypto/md5.c ../cyclone_crypto/mpi.c ../cyclone_crypto/oid.c ../cyclone_crypto/pem.c ../cyclone_crypto/pkcs5.c ../cyclone_crypto/rc4.c ../cyclone_crypto/rc6.c ../cyclone_crypto/ripemd128.c ../cyclone_crypto/ripemd160.c ../cyclone_crypto/rsa.c ../cyclone_crypto/seed.c ../cyclone_crypto/sha1.c ../cyclone_crypto/sha224.c ../cyclone_crypto/sha256.c ../cyclone_crypto/sha384.c ../cyclone_crypto/sha512.c ../cyclone_crypto/sha512_224.c ../cyclone_crypto/sha512_256.c ../cyclone_crypto/tiger.c ../cyclone_crypto/whirlpool.c ../cyclone_crypto/x509.c ../cyclone_crypto/yarrow.c ../cyclone_ssl/ssl_common.c ../cyclone_ssl/tls.c ../cyclone_ssl/tls_cache.c ../cyclone_ssl/tls_cipher_suites.c ../cyclone_ssl/tls_client.c ../cyclone_ssl/tls_common.c ../cyclone_ssl/tls_io.c ../cyclone_ssl/tls_misc.c ../cyclone_ssl/tls_record.c ../cyclone_ssl/tls_server.c ../cyclone_tcp/core/bsd_socket.c ../cyclone_tcp/core/ethernet.c ../cyclone_tcp/core/ip.c ../cyclone_tcp/core/net.c ../cyclone_tcp/core/net_mem.c ../cyclone_tcp/core/nic.c ../cyclone_tcp/core/ping.c ../cyclone_tcp/core/raw_socket.c ../cyclone_tcp/core/socket.c ../cyclone_tcp/core/tcp.c ../cyclone_tcp/core/tcp_fsm.c ../cyclone_tcp/core/tcp_misc.c ../cyclone_tcp/core/tcp_timer.c ../cyclone_tcp/core/udp.c ../cyclone_tcp/dhcp/dhcp_client.c ../cyclone_tcp/dhcp/dhcp_common.c ../cyclone_tcp/dhcp/dhcp_debug.c ../cyclone_tcp/dns/dns_cache.c ../cyclone_tcp/dns/dns_client.c ../cyclone_tcp/dns/dns_common.c ../cyclone_tcp/dns/dns_debug.c ../cyclone_tcp/drivers/dp83848.c ../cyclone_tcp/drivers/pic32mx_eth.c ../cyclone_tcp/http/http_server.c ../cyclone_tcp/http/http_server_auth.c ../cyclone_tcp/http/http_server_misc.c ../cyclone_tcp/http/mime.c ../cyclone_tcp/http/ssi.c ../cyclone_tcp/ipv4/arp.c ../cyclone_tcp/ipv4/auto_ip.c ../cyclone_tcp/ipv4/icmp.c ../cyclone_tcp/ipv4/igmp.c ../cyclone_tcp/ipv4/ipv4.c ../cyclone_tcp/ipv4/ipv4_frag.c ../cyclone_tcp/mdns/mdns_client.c ../cyclone_tcp/mdns/mdns_common.c ../cyclone_tcp/mdns/mdns_responder.c ../cyclone_tcp/netbios/nbns_client.c ../cyclone_tcp/netbios/nbns_common.c ../cyclone_tcp/netbios/nbns_responder.c ../cyclone_tcp/smtp/smtp_client.c ../cyclone_tcp/sntp/sntp_client.c ../cyclone_tcp/std_services/chargen.c ../cyclone_tcp/std_services/daytime.c ../cyclone_tcp/std_services/discard.c ../cyclone_tcp/std_services/echo.c ../common/freertos/portable/mplab/pic32mx/port.c ../common/freertos/portable/mplab/pic32mx/port_asm.S ../common/freertos/croutine.c ../common/freertos/event_groups.c ../common/freertos/list.c ../common/freertos/queue.c ../common/freertos/tasks.c ../common/freertos/timers.c ../common/freertos/portable/memmang/heap_3.c ../src/main.c ../src/debug.c ../src/sprintf.c ../src/strtok_r.c ../src/ext3_irq_wrapper.S ../src/eth_irq_wrapper.S ../src/res.c ../src/ext_int_driver.c ../src/SPIFlash.c ../src/SPIMACEEPROM.c ../src/VM204.c ../src/analog.c ../src/discovery.c ../src/inputs.c ../src/relays.c ../src/cJSON.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1270477542/date_time.o ${OBJECTDIR}/_ext/1270477542/endian.o ${OBJECTDIR}/_ext/1270477542/path.o ${OBJECTDIR}/_ext/1270477542/resource_manager.o ${OBJECTDIR}/_ext/1270477542/str.o ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o ${OBJECTDIR}/_ext/1390087560/aes.o ${OBJECTDIR}/_ext/1390087560/aria.o ${OBJECTDIR}/_ext/1390087560/asn1.o ${OBJECTDIR}/_ext/1390087560/base64.o ${OBJECTDIR}/_ext/1390087560/camellia.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o ${OBJECTDIR}/_ext/1390087560/des.o ${OBJECTDIR}/_ext/1390087560/des3.o ${OBJECTDIR}/_ext/1390087560/dh.o ${OBJECTDIR}/_ext/1390087560/dsa.o ${OBJECTDIR}/_ext/1390087560/ec.o ${OBJECTDIR}/_ext/1390087560/ec_curves.o ${OBJECTDIR}/_ext/1390087560/ecdh.o ${OBJECTDIR}/_ext/1390087560/ecdsa.o ${OBJECTDIR}/_ext/1390087560/hmac.o ${OBJECTDIR}/_ext/1390087560/idea.o ${OBJECTDIR}/_ext/1390087560/md2.o ${OBJECTDIR}/_ext/1390087560/md4.o ${OBJECTDIR}/_ext/1390087560/md5.o ${OBJECTDIR}/_ext/1390087560/mpi.o ${OBJECTDIR}/_ext/1390087560/oid.o ${OBJECTDIR}/_ext/1390087560/pem.o ${OBJECTDIR}/_ext/1390087560/pkcs5.o ${OBJECTDIR}/_ext/1390087560/rc4.o ${OBJECTDIR}/_ext/1390087560/rc6.o ${OBJECTDIR}/_ext/1390087560/ripemd128.o ${OBJECTDIR}/_ext/1390087560/ripemd160.o ${OBJECTDIR}/_ext/1390087560/rsa.o ${OBJECTDIR}/_ext/1390087560/seed.o ${OBJECTDIR}/_ext/1390087560/sha1.o ${OBJECTDIR}/_ext/1390087560/sha224.o ${OBJECTDIR}/_ext/1390087560/sha256.o ${OBJECTDIR}/_ext/1390087560/sha384.o ${OBJECTDIR}/_ext/1390087560/sha512.o ${OBJECTDIR}/_ext/1390087560/sha512_224.o ${OBJECTDIR}/_ext/1390087560/sha512_256.o ${OBJECTDIR}/_ext/1390087560/tiger.o ${OBJECTDIR}/_ext/1390087560/whirlpool.o ${OBJECTDIR}/_ext/1390087560/x509.o ${OBJECTDIR}/_ext/1390087560/yarrow.o ${OBJECTDIR}/_ext/1058722139/ssl_common.o ${OBJECTDIR}/_ext/1058722139/tls.o ${OBJECTDIR}/_ext/1058722139/tls_cache.o ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o ${OBJECTDIR}/_ext/1058722139/tls_client.o ${OBJECTDIR}/_ext/1058722139/tls_common.o ${OBJECTDIR}/_ext/1058722139/tls_io.o ${OBJECTDIR}/_ext/1058722139/tls_misc.o ${OBJECTDIR}/_ext/1058722139/tls_record.o ${OBJECTDIR}/_ext/1058722139/tls_server.o ${OBJECTDIR}/_ext/1043526636/bsd_socket.o ${OBJECTDIR}/_ext/1043526636/ethernet.o ${OBJECTDIR}/_ext/1043526636/ip.o ${OBJECTDIR}/_ext/1043526636/net.o ${OBJECTDIR}/_ext/1043526636/net_mem.o ${OBJECTDIR}/_ext/1043526636/nic.o ${OBJECTDIR}/_ext/1043526636/ping.o ${OBJECTDIR}/_ext/1043526636/raw_socket.o ${OBJECTDIR}/_ext/1043526636/socket.o ${OBJECTDIR}/_ext/1043526636/tcp.o ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o ${OBJECTDIR}/_ext/1043526636/tcp_misc.o ${OBJECTDIR}/_ext/1043526636/tcp_timer.o ${OBJECTDIR}/_ext/1043526636/udp.o ${OBJECTDIR}/_ext/1043504026/dhcp_client.o ${OBJECTDIR}/_ext/1043504026/dhcp_common.o ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o ${OBJECTDIR}/_ext/1906001428/dns_cache.o ${OBJECTDIR}/_ext/1906001428/dns_client.o ${OBJECTDIR}/_ext/1906001428/dns_common.o ${OBJECTDIR}/_ext/1906001428/dns_debug.o ${OBJECTDIR}/_ext/236961974/dp83848.o ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o ${OBJECTDIR}/_ext/1043372803/http_server.o ${OBJECTDIR}/_ext/1043372803/http_server_auth.o ${OBJECTDIR}/_ext/1043372803/http_server_misc.o ${OBJECTDIR}/_ext/1043372803/mime.o ${OBJECTDIR}/_ext/1043372803/ssi.o ${OBJECTDIR}/_ext/1043346854/arp.o ${OBJECTDIR}/_ext/1043346854/auto_ip.o ${OBJECTDIR}/_ext/1043346854/icmp.o ${OBJECTDIR}/_ext/1043346854/igmp.o ${OBJECTDIR}/_ext/1043346854/ipv4.o ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o ${OBJECTDIR}/_ext/1043239407/mdns_client.o ${OBJECTDIR}/_ext/1043239407/mdns_common.o ${OBJECTDIR}/_ext/1043239407/mdns_responder.o ${OBJECTDIR}/_ext/159451891/nbns_client.o ${OBJECTDIR}/_ext/159451891/nbns_common.o ${OBJECTDIR}/_ext/159451891/nbns_responder.o ${OBJECTDIR}/_ext/1043051829/smtp_client.o ${OBJECTDIR}/_ext/1043050868/sntp_client.o ${OBJECTDIR}/_ext/1333908079/chargen.o ${OBJECTDIR}/_ext/1333908079/daytime.o ${OBJECTDIR}/_ext/1333908079/discard.o ${OBJECTDIR}/_ext/1333908079/echo.o ${OBJECTDIR}/_ext/1653734595/port.o ${OBJECTDIR}/_ext/1653734595/port_asm.o ${OBJECTDIR}/_ext/563807591/croutine.o ${OBJECTDIR}/_ext/563807591/event_groups.o ${OBJECTDIR}/_ext/563807591/list.o ${OBJECTDIR}/_ext/563807591/queue.o ${OBJECTDIR}/_ext/563807591/tasks.o ${OBJECTDIR}/_ext/563807591/timers.o ${OBJECTDIR}/_ext/1209349994/heap_3.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/sprintf.o ${OBJECTDIR}/_ext/1360937237/strtok_r.o ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o ${OBJECTDIR}/_ext/1360937237/res.o ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o ${OBJECTDIR}/_ext/1360937237/SPIFlash.o ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o ${OBJECTDIR}/_ext/1360937237/VM204.o ${OBJECTDIR}/_ext/1360937237/analog.o ${OBJECTDIR}/_ext/1360937237/discovery.o ${OBJECTDIR}/_ext/1360937237/inputs.o ${OBJECTDIR}/_ext/1360937237/relays.o ${OBJECTDIR}/_ext/1360937237/cJSON.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1270477542/date_time.o.d ${OBJECTDIR}/_ext/1270477542/endian.o.d ${OBJECTDIR}/_ext/1270477542/path.o.d ${OBJECTDIR}/_ext/1270477542/resource_manager.o.d ${OBJECTDIR}/_ext/1270477542/str.o.d ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o.d ${OBJECTDIR}/_ext/1390087560/aes.o.d ${OBJECTDIR}/_ext/1390087560/aria.o.d ${OBJECTDIR}/_ext/1390087560/asn1.o.d ${OBJECTDIR}/_ext/1390087560/base64.o.d ${OBJECTDIR}/_ext/1390087560/camellia.o.d ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o.d ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o.d ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o.d ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o.d ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o.d ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o.d ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o.d ${OBJECTDIR}/_ext/1390087560/des.o.d ${OBJECTDIR}/_ext/1390087560/des3.o.d ${OBJECTDIR}/_ext/1390087560/dh.o.d ${OBJECTDIR}/_ext/1390087560/dsa.o.d ${OBJECTDIR}/_ext/1390087560/ec.o.d ${OBJECTDIR}/_ext/1390087560/ec_curves.o.d ${OBJECTDIR}/_ext/1390087560/ecdh.o.d ${OBJECTDIR}/_ext/1390087560/ecdsa.o.d ${OBJECTDIR}/_ext/1390087560/hmac.o.d ${OBJECTDIR}/_ext/1390087560/idea.o.d ${OBJECTDIR}/_ext/1390087560/md2.o.d ${OBJECTDIR}/_ext/1390087560/md4.o.d ${OBJECTDIR}/_ext/1390087560/md5.o.d ${OBJECTDIR}/_ext/1390087560/mpi.o.d ${OBJECTDIR}/_ext/1390087560/oid.o.d ${OBJECTDIR}/_ext/1390087560/pem.o.d ${OBJECTDIR}/_ext/1390087560/pkcs5.o.d ${OBJECTDIR}/_ext/1390087560/rc4.o.d ${OBJECTDIR}/_ext/1390087560/rc6.o.d ${OBJECTDIR}/_ext/1390087560/ripemd128.o.d ${OBJECTDIR}/_ext/1390087560/ripemd160.o.d ${OBJECTDIR}/_ext/1390087560/rsa.o.d ${OBJECTDIR}/_ext/1390087560/seed.o.d ${OBJECTDIR}/_ext/1390087560/sha1.o.d ${OBJECTDIR}/_ext/1390087560/sha224.o.d ${OBJECTDIR}/_ext/1390087560/sha256.o.d ${OBJECTDIR}/_ext/1390087560/sha384.o.d ${OBJECTDIR}/_ext/1390087560/sha512.o.d ${OBJECTDIR}/_ext/1390087560/sha512_224.o.d ${OBJECTDIR}/_ext/1390087560/sha512_256.o.d ${OBJECTDIR}/_ext/1390087560/tiger.o.d ${OBJECTDIR}/_ext/1390087560/whirlpool.o.d ${OBJECTDIR}/_ext/1390087560/x509.o.d ${OBJECTDIR}/_ext/1390087560/yarrow.o.d ${OBJECTDIR}/_ext/1058722139/ssl_common.o.d ${OBJECTDIR}/_ext/1058722139/tls.o.d ${OBJECTDIR}/_ext/1058722139/tls_cache.o.d ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o.d ${OBJECTDIR}/_ext/1058722139/tls_client.o.d ${OBJECTDIR}/_ext/1058722139/tls_common.o.d ${OBJECTDIR}/_ext/1058722139/tls_io.o.d ${OBJECTDIR}/_ext/1058722139/tls_misc.o.d ${OBJECTDIR}/_ext/1058722139/tls_record.o.d ${OBJECTDIR}/_ext/1058722139/tls_server.o.d ${OBJECTDIR}/_ext/1043526636/bsd_socket.o.d ${OBJECTDIR}/_ext/1043526636/ethernet.o.d ${OBJECTDIR}/_ext/1043526636/ip.o.d ${OBJECTDIR}/_ext/1043526636/net.o.d ${OBJECTDIR}/_ext/1043526636/net_mem.o.d ${OBJECTDIR}/_ext/1043526636/nic.o.d ${OBJECTDIR}/_ext/1043526636/ping.o.d ${OBJECTDIR}/_ext/1043526636/raw_socket.o.d ${OBJECTDIR}/_ext/1043526636/socket.o.d ${OBJECTDIR}/_ext/1043526636/tcp.o.d ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o.d ${OBJECTDIR}/_ext/1043526636/tcp_misc.o.d ${OBJECTDIR}/_ext/1043526636/tcp_timer.o.d ${OBJECTDIR}/_ext/1043526636/udp.o.d ${OBJECTDIR}/_ext/1043504026/dhcp_client.o.d ${OBJECTDIR}/_ext/1043504026/dhcp_common.o.d ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o.d ${OBJECTDIR}/_ext/1906001428/dns_cache.o.d ${OBJECTDIR}/_ext/1906001428/dns_client.o.d ${OBJECTDIR}/_ext/1906001428/dns_common.o.d ${OBJECTDIR}/_ext/1906001428/dns_debug.o.d ${OBJECTDIR}/_ext/236961974/dp83848.o.d ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o.d ${OBJECTDIR}/_ext/1043372803/http_server.o.d ${OBJECTDIR}/_ext/1043372803/http_server_auth.o.d ${OBJECTDIR}/_ext/1043372803/http_server_misc.o.d ${OBJECTDIR}/_ext/1043372803/mime.o.d ${OBJECTDIR}/_ext/1043372803/ssi.o.d ${OBJECTDIR}/_ext/1043346854/arp.o.d ${OBJECTDIR}/_ext/1043346854/auto_ip.o.d ${OBJECTDIR}/_ext/1043346854/icmp.o.d ${OBJECTDIR}/_ext/1043346854/igmp.o.d ${OBJECTDIR}/_ext/1043346854/ipv4.o.d ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o.d ${OBJECTDIR}/_ext/1043239407/mdns_client.o.d ${OBJECTDIR}/_ext/1043239407/mdns_common.o.d ${OBJECTDIR}/_ext/1043239407/mdns_responder.o.d ${OBJECTDIR}/_ext/159451891/nbns_client.o.d ${OBJECTDIR}/_ext/159451891/nbns_common.o.d ${OBJECTDIR}/_ext/159451891/nbns_responder.o.d ${OBJECTDIR}/_ext/1043051829/smtp_client.o.d ${OBJECTDIR}/_ext/1043050868/sntp_client.o.d ${OBJECTDIR}/_ext/1333908079/chargen.o.d ${OBJECTDIR}/_ext/1333908079/daytime.o.d ${OBJECTDIR}/_ext/1333908079/discard.o.d ${OBJECTDIR}/_ext/1333908079/echo.o.d ${OBJECTDIR}/_ext/1653734595/port.o.d ${OBJECTDIR}/_ext/1653734595/port_asm.o.d ${OBJECTDIR}/_ext/563807591/croutine.o.d ${OBJECTDIR}/_ext/563807591/event_groups.o.d ${OBJECTDIR}/_ext/563807591/list.o.d ${OBJECTDIR}/_ext/563807591/queue.o.d ${OBJECTDIR}/_ext/563807591/tasks.o.d ${OBJECTDIR}/_ext/563807591/timers.o.d ${OBJECTDIR}/_ext/1209349994/heap_3.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/debug.o.d ${OBJECTDIR}/_ext/1360937237/sprintf.o.d ${OBJECTDIR}/_ext/1360937237/strtok_r.o.d ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.d ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.d ${OBJECTDIR}/_ext/1360937237/res.o.d ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o.d ${OBJECTDIR}/_ext/1360937237/SPIFlash.o.d ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o.d ${OBJECTDIR}/_ext/1360937237/VM204.o.d ${OBJECTDIR}/_ext/1360937237/analog.o.d ${OBJECTDIR}/_ext/1360937237/discovery.o.d ${OBJECTDIR}/_ext/1360937237/inputs.o.d ${OBJECTDIR}/_ext/1360937237/relays.o.d ${OBJECTDIR}/_ext/1360937237/cJSON.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1270477542/date_time.o ${OBJECTDIR}/_ext/1270477542/endian.o ${OBJECTDIR}/_ext/1270477542/path.o ${OBJECTDIR}/_ext/1270477542/resource_manager.o ${OBJECTDIR}/_ext/1270477542/str.o ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o ${OBJECTDIR}/_ext/1390087560/aes.o ${OBJECTDIR}/_ext/1390087560/aria.o ${OBJECTDIR}/_ext/1390087560/asn1.o ${OBJECTDIR}/_ext/1390087560/base64.o ${OBJECTDIR}/_ext/1390087560/camellia.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o ${OBJECTDIR}/_ext/1390087560/des.o ${OBJECTDIR}/_ext/1390087560/des3.o ${OBJECTDIR}/_ext/1390087560/dh.o ${OBJECTDIR}/_ext/1390087560/dsa.o ${OBJECTDIR}/_ext/1390087560/ec.o ${OBJECTDIR}/_ext/1390087560/ec_curves.o ${OBJECTDIR}/_ext/1390087560/ecdh.o ${OBJECTDIR}/_ext/1390087560/ecdsa.o ${OBJECTDIR}/_ext/1390087560/hmac.o ${OBJECTDIR}/_ext/1390087560/idea.o ${OBJECTDIR}/_ext/1390087560/md2.o ${OBJECTDIR}/_ext/1390087560/md4.o ${OBJECTDIR}/_ext/1390087560/md5.o ${OBJECTDIR}/_ext/1390087560/mpi.o ${OBJECTDIR}/_ext/1390087560/oid.o ${OBJECTDIR}/_ext/1390087560/pem.o ${OBJECTDIR}/_ext/1390087560/pkcs5.o ${OBJECTDIR}/_ext/1390087560/rc4.o ${OBJECTDIR}/_ext/1390087560/rc6.o ${OBJECTDIR}/_ext/1390087560/ripemd128.o ${OBJECTDIR}/_ext/1390087560/ripemd160.o ${OBJECTDIR}/_ext/1390087560/rsa.o ${OBJECTDIR}/_ext/1390087560/seed.o ${OBJECTDIR}/_ext/1390087560/sha1.o ${OBJECTDIR}/_ext/1390087560/sha224.o ${OBJECTDIR}/_ext/1390087560/sha256.o ${OBJECTDIR}/_ext/1390087560/sha384.o ${OBJECTDIR}/_ext/1390087560/sha512.o ${OBJECTDIR}/_ext/1390087560/sha512_224.o ${OBJECTDIR}/_ext/1390087560/sha512_256.o ${OBJECTDIR}/_ext/1390087560/tiger.o ${OBJECTDIR}/_ext/1390087560/whirlpool.o ${OBJECTDIR}/_ext/1390087560/x509.o ${OBJECTDIR}/_ext/1390087560/yarrow.o ${OBJECTDIR}/_ext/1058722139/ssl_common.o ${OBJECTDIR}/_ext/1058722139/tls.o ${OBJECTDIR}/_ext/1058722139/tls_cache.o ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o ${OBJECTDIR}/_ext/1058722139/tls_client.o ${OBJECTDIR}/_ext/1058722139/tls_common.o ${OBJECTDIR}/_ext/1058722139/tls_io.o ${OBJECTDIR}/_ext/1058722139/tls_misc.o ${OBJECTDIR}/_ext/1058722139/tls_record.o ${OBJECTDIR}/_ext/1058722139/tls_server.o ${OBJECTDIR}/_ext/1043526636/bsd_socket.o ${OBJECTDIR}/_ext/1043526636/ethernet.o ${OBJECTDIR}/_ext/1043526636/ip.o ${OBJECTDIR}/_ext/1043526636/net.o ${OBJECTDIR}/_ext/1043526636/net_mem.o ${OBJECTDIR}/_ext/1043526636/nic.o ${OBJECTDIR}/_ext/1043526636/ping.o ${OBJECTDIR}/_ext/1043526636/raw_socket.o ${OBJECTDIR}/_ext/1043526636/socket.o ${OBJECTDIR}/_ext/1043526636/tcp.o ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o ${OBJECTDIR}/_ext/1043526636/tcp_misc.o ${OBJECTDIR}/_ext/1043526636/tcp_timer.o ${OBJECTDIR}/_ext/1043526636/udp.o ${OBJECTDIR}/_ext/1043504026/dhcp_client.o ${OBJECTDIR}/_ext/1043504026/dhcp_common.o ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o ${OBJECTDIR}/_ext/1906001428/dns_cache.o ${OBJECTDIR}/_ext/1906001428/dns_client.o ${OBJECTDIR}/_ext/1906001428/dns_common.o ${OBJECTDIR}/_ext/1906001428/dns_debug.o ${OBJECTDIR}/_ext/236961974/dp83848.o ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o ${OBJECTDIR}/_ext/1043372803/http_server.o ${OBJECTDIR}/_ext/1043372803/http_server_auth.o ${OBJECTDIR}/_ext/1043372803/http_server_misc.o ${OBJECTDIR}/_ext/1043372803/mime.o ${OBJECTDIR}/_ext/1043372803/ssi.o ${OBJECTDIR}/_ext/1043346854/arp.o ${OBJECTDIR}/_ext/1043346854/auto_ip.o ${OBJECTDIR}/_ext/1043346854/icmp.o ${OBJECTDIR}/_ext/1043346854/igmp.o ${OBJECTDIR}/_ext/1043346854/ipv4.o ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o ${OBJECTDIR}/_ext/1043239407/mdns_client.o ${OBJECTDIR}/_ext/1043239407/mdns_common.o ${OBJECTDIR}/_ext/1043239407/mdns_responder.o ${OBJECTDIR}/_ext/159451891/nbns_client.o ${OBJECTDIR}/_ext/159451891/nbns_common.o ${OBJECTDIR}/_ext/159451891/nbns_responder.o ${OBJECTDIR}/_ext/1043051829/smtp_client.o ${OBJECTDIR}/_ext/1043050868/sntp_client.o ${OBJECTDIR}/_ext/1333908079/chargen.o ${OBJECTDIR}/_ext/1333908079/daytime.o ${OBJECTDIR}/_ext/1333908079/discard.o ${OBJECTDIR}/_ext/1333908079/echo.o ${OBJECTDIR}/_ext/1653734595/port.o ${OBJECTDIR}/_ext/1653734595/port_asm.o ${OBJECTDIR}/_ext/563807591/croutine.o ${OBJECTDIR}/_ext/563807591/event_groups.o ${OBJECTDIR}/_ext/563807591/list.o ${OBJECTDIR}/_ext/563807591/queue.o ${OBJECTDIR}/_ext/563807591/tasks.o ${OBJECTDIR}/_ext/563807591/timers.o ${OBJECTDIR}/_ext/1209349994/heap_3.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/sprintf.o ${OBJECTDIR}/_ext/1360937237/strtok_r.o ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o ${OBJECTDIR}/_ext/1360937237/res.o ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o ${OBJECTDIR}/_ext/1360937237/SPIFlash.o ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o ${OBJECTDIR}/_ext/1360937237/VM204.o ${OBJECTDIR}/_ext/1360937237/analog.o ${OBJECTDIR}/_ext/1360937237/discovery.o ${OBJECTDIR}/_ext/1360937237/inputs.o ${OBJECTDIR}/_ext/1360937237/relays.o ${OBJECTDIR}/_ext/1360937237/cJSON.o

# Source Files
SOURCEFILES=../common/date_time.c ../common/endian.c ../common/path.c ../common/resource_manager.c ../common/str.c ../common/os_port_freertos.c ../cyclone_crypto/aes.c ../cyclone_crypto/aria.c ../cyclone_crypto/asn1.c ../cyclone_crypto/base64.c ../cyclone_crypto/camellia.c ../cyclone_crypto/cipher_mode_cbc.c ../cyclone_crypto/cipher_mode_ccm.c ../cyclone_crypto/cipher_mode_cfb.c ../cyclone_crypto/cipher_mode_ctr.c ../cyclone_crypto/cipher_mode_ecb.c ../cyclone_crypto/cipher_mode_gcm.c ../cyclone_crypto/cipher_mode_ofb.c ../cyclone_crypto/des.c ../cyclone_crypto/des3.c ../cyclone_crypto/dh.c ../cyclone_crypto/dsa.c ../cyclone_crypto/ec.c ../cyclone_crypto/ec_curves.c ../cyclone_crypto/ecdh.c ../cyclone_crypto/ecdsa.c ../cyclone_crypto/hmac.c ../cyclone_crypto/idea.c ../cyclone_crypto/md2.c ../cyclone_crypto/md4.c ../cyclone_crypto/md5.c ../cyclone_crypto/mpi.c ../cyclone_crypto/oid.c ../cyclone_crypto/pem.c ../cyclone_crypto/pkcs5.c ../cyclone_crypto/rc4.c ../cyclone_crypto/rc6.c ../cyclone_crypto/ripemd128.c ../cyclone_crypto/ripemd160.c ../cyclone_crypto/rsa.c ../cyclone_crypto/seed.c ../cyclone_crypto/sha1.c ../cyclone_crypto/sha224.c ../cyclone_crypto/sha256.c ../cyclone_crypto/sha384.c ../cyclone_crypto/sha512.c ../cyclone_crypto/sha512_224.c ../cyclone_crypto/sha512_256.c ../cyclone_crypto/tiger.c ../cyclone_crypto/whirlpool.c ../cyclone_crypto/x509.c ../cyclone_crypto/yarrow.c ../cyclone_ssl/ssl_common.c ../cyclone_ssl/tls.c ../cyclone_ssl/tls_cache.c ../cyclone_ssl/tls_cipher_suites.c ../cyclone_ssl/tls_client.c ../cyclone_ssl/tls_common.c ../cyclone_ssl/tls_io.c ../cyclone_ssl/tls_misc.c ../cyclone_ssl/tls_record.c ../cyclone_ssl/tls_server.c ../cyclone_tcp/core/bsd_socket.c ../cyclone_tcp/core/ethernet.c ../cyclone_tcp/core/ip.c ../cyclone_tcp/core/net.c ../cyclone_tcp/core/net_mem.c ../cyclone_tcp/core/nic.c ../cyclone_tcp/core/ping.c ../cyclone_tcp/core/raw_socket.c ../cyclone_tcp/core/socket.c ../cyclone_tcp/core/tcp.c ../cyclone_tcp/core/tcp_fsm.c ../cyclone_tcp/core/tcp_misc.c ../cyclone_tcp/core/tcp_timer.c ../cyclone_tcp/core/udp.c ../cyclone_tcp/dhcp/dhcp_client.c ../cyclone_tcp/dhcp/dhcp_common.c ../cyclone_tcp/dhcp/dhcp_debug.c ../cyclone_tcp/dns/dns_cache.c ../cyclone_tcp/dns/dns_client.c ../cyclone_tcp/dns/dns_common.c ../cyclone_tcp/dns/dns_debug.c ../cyclone_tcp/drivers/dp83848.c ../cyclone_tcp/drivers/pic32mx_eth.c ../cyclone_tcp/http/http_server.c ../cyclone_tcp/http/http_server_auth.c ../cyclone_tcp/http/http_server_misc.c ../cyclone_tcp/http/mime.c ../cyclone_tcp/http/ssi.c ../cyclone_tcp/ipv4/arp.c ../cyclone_tcp/ipv4/auto_ip.c ../cyclone_tcp/ipv4/icmp.c ../cyclone_tcp/ipv4/igmp.c ../cyclone_tcp/ipv4/ipv4.c ../cyclone_tcp/ipv4/ipv4_frag.c ../cyclone_tcp/mdns/mdns_client.c ../cyclone_tcp/mdns/mdns_common.c ../cyclone_tcp/mdns/mdns_responder.c ../cyclone_tcp/netbios/nbns_client.c ../cyclone_tcp/netbios/nbns_common.c ../cyclone_tcp/netbios/nbns_responder.c ../cyclone_tcp/smtp/smtp_client.c ../cyclone_tcp/sntp/sntp_client.c ../cyclone_tcp/std_services/chargen.c ../cyclone_tcp/std_services/daytime.c ../cyclone_tcp/std_services/discard.c ../cyclone_tcp/std_services/echo.c ../common/freertos/portable/mplab/pic32mx/port.c ../common/freertos/portable/mplab/pic32mx/port_asm.S ../common/freertos/croutine.c ../common/freertos/event_groups.c ../common/freertos/list.c ../common/freertos/queue.c ../common/freertos/tasks.c ../common/freertos/timers.c ../common/freertos/portable/memmang/heap_3.c ../src/main.c ../src/debug.c ../src/sprintf.c ../src/strtok_r.c ../src/ext3_irq_wrapper.S ../src/eth_irq_wrapper.S ../src/res.c ../src/ext_int_driver.c ../src/SPIFlash.c ../src/SPIMACEEPROM.c ../src/VM204.c ../src/analog.c ../src/discovery.c ../src/inputs.c ../src/relays.c ../src/cJSON.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC32MX795F512L
ProjectDir="C:\Users\bn\Documents\VM204\VM204.X\mplabx"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"

.build-conf:  .pre ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1653734595/port_asm.o: ../common/freertos/portable/mplab/pic32mx/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1653734595 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port_asm.o.ok ${OBJECTDIR}/_ext/1653734595/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1653734595/port_asm.o.d" "${OBJECTDIR}/_ext/1653734595/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"/cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1653734595/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1653734595/port_asm.o ../common/freertos/portable/mplab/pic32mx/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1653734595/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
	
${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o: ../src/ext3_irq_wrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.ok ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.d" "${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"/cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.d"  -o ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o ../src/ext3_irq_wrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
	
${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o: ../src/eth_irq_wrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.ok ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.d" "${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"/cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.d"  -o ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o ../src/eth_irq_wrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
	
else
${OBJECTDIR}/_ext/1653734595/port_asm.o: ../common/freertos/portable/mplab/pic32mx/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1653734595 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port_asm.o.ok ${OBJECTDIR}/_ext/1653734595/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1653734595/port_asm.o.d" "${OBJECTDIR}/_ext/1653734595/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"/cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1653734595/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1653734595/port_asm.o ../common/freertos/portable/mplab/pic32mx/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1653734595/port_asm.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o: ../src/ext3_irq_wrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.ok ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.d" "${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"/cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.d"  -o ${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o ../src/ext3_irq_wrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/ext3_irq_wrapper.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o: ../src/eth_irq_wrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.ok ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.d" "${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"/cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.d"  -o ${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o ../src/eth_irq_wrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/eth_irq_wrapper.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1270477542/date_time.o: ../common/date_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/date_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/date_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/date_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/date_time.o.d" -o ${OBJECTDIR}/_ext/1270477542/date_time.o ../common/date_time.c   
	
${OBJECTDIR}/_ext/1270477542/endian.o: ../common/endian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/endian.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/endian.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/endian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/endian.o.d" -o ${OBJECTDIR}/_ext/1270477542/endian.o ../common/endian.c   
	
${OBJECTDIR}/_ext/1270477542/path.o: ../common/path.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/path.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/path.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/path.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/path.o.d" -o ${OBJECTDIR}/_ext/1270477542/path.o ../common/path.c   
	
${OBJECTDIR}/_ext/1270477542/resource_manager.o: ../common/resource_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/resource_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/resource_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/resource_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/resource_manager.o.d" -o ${OBJECTDIR}/_ext/1270477542/resource_manager.o ../common/resource_manager.c   
	
${OBJECTDIR}/_ext/1270477542/str.o: ../common/str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/str.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/str.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/str.o.d" -o ${OBJECTDIR}/_ext/1270477542/str.o ../common/str.c   
	
${OBJECTDIR}/_ext/1270477542/os_port_freertos.o: ../common/os_port_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/os_port_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/os_port_freertos.o.d" -o ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o ../common/os_port_freertos.c   
	
${OBJECTDIR}/_ext/1390087560/aes.o: ../cyclone_crypto/aes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/aes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/aes.o.d" -o ${OBJECTDIR}/_ext/1390087560/aes.o ../cyclone_crypto/aes.c   
	
${OBJECTDIR}/_ext/1390087560/aria.o: ../cyclone_crypto/aria.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aria.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aria.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/aria.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/aria.o.d" -o ${OBJECTDIR}/_ext/1390087560/aria.o ../cyclone_crypto/aria.c   
	
${OBJECTDIR}/_ext/1390087560/asn1.o: ../cyclone_crypto/asn1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/asn1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/asn1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/asn1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/asn1.o.d" -o ${OBJECTDIR}/_ext/1390087560/asn1.o ../cyclone_crypto/asn1.c   
	
${OBJECTDIR}/_ext/1390087560/base64.o: ../cyclone_crypto/base64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/base64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/base64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/base64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/base64.o.d" -o ${OBJECTDIR}/_ext/1390087560/base64.o ../cyclone_crypto/base64.c   
	
${OBJECTDIR}/_ext/1390087560/camellia.o: ../cyclone_crypto/camellia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/camellia.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/camellia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/camellia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/camellia.o.d" -o ${OBJECTDIR}/_ext/1390087560/camellia.o ../cyclone_crypto/camellia.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o: ../cyclone_crypto/cipher_mode_cbc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o ../cyclone_crypto/cipher_mode_cbc.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o: ../cyclone_crypto/cipher_mode_ccm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o ../cyclone_crypto/cipher_mode_ccm.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o: ../cyclone_crypto/cipher_mode_cfb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o ../cyclone_crypto/cipher_mode_cfb.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o: ../cyclone_crypto/cipher_mode_ctr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o ../cyclone_crypto/cipher_mode_ctr.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o: ../cyclone_crypto/cipher_mode_ecb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o ../cyclone_crypto/cipher_mode_ecb.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o: ../cyclone_crypto/cipher_mode_gcm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o ../cyclone_crypto/cipher_mode_gcm.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o: ../cyclone_crypto/cipher_mode_ofb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o ../cyclone_crypto/cipher_mode_ofb.c   
	
${OBJECTDIR}/_ext/1390087560/des.o: ../cyclone_crypto/des.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/des.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/des.o.d" -o ${OBJECTDIR}/_ext/1390087560/des.o ../cyclone_crypto/des.c   
	
${OBJECTDIR}/_ext/1390087560/des3.o: ../cyclone_crypto/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/des3.o.d" -o ${OBJECTDIR}/_ext/1390087560/des3.o ../cyclone_crypto/des3.c   
	
${OBJECTDIR}/_ext/1390087560/dh.o: ../cyclone_crypto/dh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/dh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/dh.o.d" -o ${OBJECTDIR}/_ext/1390087560/dh.o ../cyclone_crypto/dh.c   
	
${OBJECTDIR}/_ext/1390087560/dsa.o: ../cyclone_crypto/dsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/dsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/dsa.o.d" -o ${OBJECTDIR}/_ext/1390087560/dsa.o ../cyclone_crypto/dsa.c   
	
${OBJECTDIR}/_ext/1390087560/ec.o: ../cyclone_crypto/ec.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ec.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ec.o.d" -o ${OBJECTDIR}/_ext/1390087560/ec.o ../cyclone_crypto/ec.c   
	
${OBJECTDIR}/_ext/1390087560/ec_curves.o: ../cyclone_crypto/ec_curves.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec_curves.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec_curves.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ec_curves.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ec_curves.o.d" -o ${OBJECTDIR}/_ext/1390087560/ec_curves.o ../cyclone_crypto/ec_curves.c   
	
${OBJECTDIR}/_ext/1390087560/ecdh.o: ../cyclone_crypto/ecdh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ecdh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ecdh.o.d" -o ${OBJECTDIR}/_ext/1390087560/ecdh.o ../cyclone_crypto/ecdh.c   
	
${OBJECTDIR}/_ext/1390087560/ecdsa.o: ../cyclone_crypto/ecdsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ecdsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ecdsa.o.d" -o ${OBJECTDIR}/_ext/1390087560/ecdsa.o ../cyclone_crypto/ecdsa.c   
	
${OBJECTDIR}/_ext/1390087560/hmac.o: ../cyclone_crypto/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/hmac.o.d" -o ${OBJECTDIR}/_ext/1390087560/hmac.o ../cyclone_crypto/hmac.c   
	
${OBJECTDIR}/_ext/1390087560/idea.o: ../cyclone_crypto/idea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/idea.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/idea.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/idea.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/idea.o.d" -o ${OBJECTDIR}/_ext/1390087560/idea.o ../cyclone_crypto/idea.c   
	
${OBJECTDIR}/_ext/1390087560/md2.o: ../cyclone_crypto/md2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/md2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/md2.o.d" -o ${OBJECTDIR}/_ext/1390087560/md2.o ../cyclone_crypto/md2.c   
	
${OBJECTDIR}/_ext/1390087560/md4.o: ../cyclone_crypto/md4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/md4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/md4.o.d" -o ${OBJECTDIR}/_ext/1390087560/md4.o ../cyclone_crypto/md4.c   
	
${OBJECTDIR}/_ext/1390087560/md5.o: ../cyclone_crypto/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/md5.o.d" -o ${OBJECTDIR}/_ext/1390087560/md5.o ../cyclone_crypto/md5.c   
	
${OBJECTDIR}/_ext/1390087560/mpi.o: ../cyclone_crypto/mpi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/mpi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/mpi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/mpi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/mpi.o.d" -o ${OBJECTDIR}/_ext/1390087560/mpi.o ../cyclone_crypto/mpi.c   
	
${OBJECTDIR}/_ext/1390087560/oid.o: ../cyclone_crypto/oid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/oid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/oid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/oid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/oid.o.d" -o ${OBJECTDIR}/_ext/1390087560/oid.o ../cyclone_crypto/oid.c   
	
${OBJECTDIR}/_ext/1390087560/pem.o: ../cyclone_crypto/pem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/pem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/pem.o.d" -o ${OBJECTDIR}/_ext/1390087560/pem.o ../cyclone_crypto/pem.c   
	
${OBJECTDIR}/_ext/1390087560/pkcs5.o: ../cyclone_crypto/pkcs5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pkcs5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pkcs5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/pkcs5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/pkcs5.o.d" -o ${OBJECTDIR}/_ext/1390087560/pkcs5.o ../cyclone_crypto/pkcs5.c   
	
${OBJECTDIR}/_ext/1390087560/rc4.o: ../cyclone_crypto/rc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/rc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/rc4.o.d" -o ${OBJECTDIR}/_ext/1390087560/rc4.o ../cyclone_crypto/rc4.c   
	
${OBJECTDIR}/_ext/1390087560/rc6.o: ../cyclone_crypto/rc6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/rc6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/rc6.o.d" -o ${OBJECTDIR}/_ext/1390087560/rc6.o ../cyclone_crypto/rc6.c   
	
${OBJECTDIR}/_ext/1390087560/ripemd128.o: ../cyclone_crypto/ripemd128.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd128.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd128.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ripemd128.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ripemd128.o.d" -o ${OBJECTDIR}/_ext/1390087560/ripemd128.o ../cyclone_crypto/ripemd128.c   
	
${OBJECTDIR}/_ext/1390087560/ripemd160.o: ../cyclone_crypto/ripemd160.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd160.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd160.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ripemd160.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ripemd160.o.d" -o ${OBJECTDIR}/_ext/1390087560/ripemd160.o ../cyclone_crypto/ripemd160.c   
	
${OBJECTDIR}/_ext/1390087560/rsa.o: ../cyclone_crypto/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/rsa.o.d" -o ${OBJECTDIR}/_ext/1390087560/rsa.o ../cyclone_crypto/rsa.c   
	
${OBJECTDIR}/_ext/1390087560/seed.o: ../cyclone_crypto/seed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/seed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/seed.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/seed.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/seed.o.d" -o ${OBJECTDIR}/_ext/1390087560/seed.o ../cyclone_crypto/seed.c   
	
${OBJECTDIR}/_ext/1390087560/sha1.o: ../cyclone_crypto/sha1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha1.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha1.o ../cyclone_crypto/sha1.c   
	
${OBJECTDIR}/_ext/1390087560/sha224.o: ../cyclone_crypto/sha224.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha224.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha224.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha224.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha224.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha224.o ../cyclone_crypto/sha224.c   
	
${OBJECTDIR}/_ext/1390087560/sha256.o: ../cyclone_crypto/sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha256.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha256.o ../cyclone_crypto/sha256.c   
	
${OBJECTDIR}/_ext/1390087560/sha384.o: ../cyclone_crypto/sha384.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha384.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha384.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha384.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha384.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha384.o ../cyclone_crypto/sha384.c   
	
${OBJECTDIR}/_ext/1390087560/sha512.o: ../cyclone_crypto/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha512.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha512.o ../cyclone_crypto/sha512.c   
	
${OBJECTDIR}/_ext/1390087560/sha512_224.o: ../cyclone_crypto/sha512_224.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_224.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_224.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha512_224.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha512_224.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha512_224.o ../cyclone_crypto/sha512_224.c   
	
${OBJECTDIR}/_ext/1390087560/sha512_256.o: ../cyclone_crypto/sha512_256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha512_256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha512_256.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha512_256.o ../cyclone_crypto/sha512_256.c   
	
${OBJECTDIR}/_ext/1390087560/tiger.o: ../cyclone_crypto/tiger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/tiger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/tiger.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/tiger.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/tiger.o.d" -o ${OBJECTDIR}/_ext/1390087560/tiger.o ../cyclone_crypto/tiger.c   
	
${OBJECTDIR}/_ext/1390087560/whirlpool.o: ../cyclone_crypto/whirlpool.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/whirlpool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/whirlpool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/whirlpool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/whirlpool.o.d" -o ${OBJECTDIR}/_ext/1390087560/whirlpool.o ../cyclone_crypto/whirlpool.c   
	
${OBJECTDIR}/_ext/1390087560/x509.o: ../cyclone_crypto/x509.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/x509.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/x509.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/x509.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/x509.o.d" -o ${OBJECTDIR}/_ext/1390087560/x509.o ../cyclone_crypto/x509.c   
	
${OBJECTDIR}/_ext/1390087560/yarrow.o: ../cyclone_crypto/yarrow.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/yarrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/yarrow.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/yarrow.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/yarrow.o.d" -o ${OBJECTDIR}/_ext/1390087560/yarrow.o ../cyclone_crypto/yarrow.c   
	
${OBJECTDIR}/_ext/1058722139/ssl_common.o: ../cyclone_ssl/ssl_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/ssl_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/ssl_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/ssl_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/ssl_common.o.d" -o ${OBJECTDIR}/_ext/1058722139/ssl_common.o ../cyclone_ssl/ssl_common.c   
	
${OBJECTDIR}/_ext/1058722139/tls.o: ../cyclone_ssl/tls.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls.o ../cyclone_ssl/tls.c   
	
${OBJECTDIR}/_ext/1058722139/tls_cache.o: ../cyclone_ssl/tls_cache.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cache.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_cache.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_cache.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_cache.o ../cyclone_ssl/tls_cache.c   
	
${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o: ../cyclone_ssl/tls_cipher_suites.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o ../cyclone_ssl/tls_cipher_suites.c   
	
${OBJECTDIR}/_ext/1058722139/tls_client.o: ../cyclone_ssl/tls_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_client.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_client.o ../cyclone_ssl/tls_client.c   
	
${OBJECTDIR}/_ext/1058722139/tls_common.o: ../cyclone_ssl/tls_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_common.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_common.o ../cyclone_ssl/tls_common.c   
	
${OBJECTDIR}/_ext/1058722139/tls_io.o: ../cyclone_ssl/tls_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_io.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_io.o ../cyclone_ssl/tls_io.c   
	
${OBJECTDIR}/_ext/1058722139/tls_misc.o: ../cyclone_ssl/tls_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_misc.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_misc.o ../cyclone_ssl/tls_misc.c   
	
${OBJECTDIR}/_ext/1058722139/tls_record.o: ../cyclone_ssl/tls_record.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_record.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_record.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_record.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_record.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_record.o ../cyclone_ssl/tls_record.c   
	
${OBJECTDIR}/_ext/1058722139/tls_server.o: ../cyclone_ssl/tls_server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_server.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_server.o ../cyclone_ssl/tls_server.c   
	
${OBJECTDIR}/_ext/1043526636/bsd_socket.o: ../cyclone_tcp/core/bsd_socket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/bsd_socket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/bsd_socket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/bsd_socket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/bsd_socket.o.d" -o ${OBJECTDIR}/_ext/1043526636/bsd_socket.o ../cyclone_tcp/core/bsd_socket.c   
	
${OBJECTDIR}/_ext/1043526636/ethernet.o: ../cyclone_tcp/core/ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ethernet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/ethernet.o.d" -o ${OBJECTDIR}/_ext/1043526636/ethernet.o ../cyclone_tcp/core/ethernet.c   
	
${OBJECTDIR}/_ext/1043526636/ip.o: ../cyclone_tcp/core/ip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ip.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ip.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/ip.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/ip.o.d" -o ${OBJECTDIR}/_ext/1043526636/ip.o ../cyclone_tcp/core/ip.c   
	
${OBJECTDIR}/_ext/1043526636/net.o: ../cyclone_tcp/core/net.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/net.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/net.o.d" -o ${OBJECTDIR}/_ext/1043526636/net.o ../cyclone_tcp/core/net.c   
	
${OBJECTDIR}/_ext/1043526636/net_mem.o: ../cyclone_tcp/core/net_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/net_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/net_mem.o.d" -o ${OBJECTDIR}/_ext/1043526636/net_mem.o ../cyclone_tcp/core/net_mem.c   
	
${OBJECTDIR}/_ext/1043526636/nic.o: ../cyclone_tcp/core/nic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/nic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/nic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/nic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/nic.o.d" -o ${OBJECTDIR}/_ext/1043526636/nic.o ../cyclone_tcp/core/nic.c   
	
${OBJECTDIR}/_ext/1043526636/ping.o: ../cyclone_tcp/core/ping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/ping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/ping.o.d" -o ${OBJECTDIR}/_ext/1043526636/ping.o ../cyclone_tcp/core/ping.c   
	
${OBJECTDIR}/_ext/1043526636/raw_socket.o: ../cyclone_tcp/core/raw_socket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/raw_socket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/raw_socket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/raw_socket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/raw_socket.o.d" -o ${OBJECTDIR}/_ext/1043526636/raw_socket.o ../cyclone_tcp/core/raw_socket.c   
	
${OBJECTDIR}/_ext/1043526636/socket.o: ../cyclone_tcp/core/socket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/socket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/socket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/socket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/socket.o.d" -o ${OBJECTDIR}/_ext/1043526636/socket.o ../cyclone_tcp/core/socket.c   
	
${OBJECTDIR}/_ext/1043526636/tcp.o: ../cyclone_tcp/core/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp.o ../cyclone_tcp/core/tcp.c   
	
${OBJECTDIR}/_ext/1043526636/tcp_fsm.o: ../cyclone_tcp/core/tcp_fsm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp_fsm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp_fsm.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o ../cyclone_tcp/core/tcp_fsm.c   
	
${OBJECTDIR}/_ext/1043526636/tcp_misc.o: ../cyclone_tcp/core/tcp_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp_misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp_misc.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp_misc.o ../cyclone_tcp/core/tcp_misc.c   
	
${OBJECTDIR}/_ext/1043526636/tcp_timer.o: ../cyclone_tcp/core/tcp_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp_timer.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp_timer.o ../cyclone_tcp/core/tcp_timer.c   
	
${OBJECTDIR}/_ext/1043526636/udp.o: ../cyclone_tcp/core/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/udp.o.d" -o ${OBJECTDIR}/_ext/1043526636/udp.o ../cyclone_tcp/core/udp.c   
	
${OBJECTDIR}/_ext/1043504026/dhcp_client.o: ../cyclone_tcp/dhcp/dhcp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043504026 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043504026/dhcp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043504026/dhcp_client.o.d" -o ${OBJECTDIR}/_ext/1043504026/dhcp_client.o ../cyclone_tcp/dhcp/dhcp_client.c   
	
${OBJECTDIR}/_ext/1043504026/dhcp_common.o: ../cyclone_tcp/dhcp/dhcp_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043504026 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043504026/dhcp_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043504026/dhcp_common.o.d" -o ${OBJECTDIR}/_ext/1043504026/dhcp_common.o ../cyclone_tcp/dhcp/dhcp_common.c   
	
${OBJECTDIR}/_ext/1043504026/dhcp_debug.o: ../cyclone_tcp/dhcp/dhcp_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043504026 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043504026/dhcp_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043504026/dhcp_debug.o.d" -o ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o ../cyclone_tcp/dhcp/dhcp_debug.c   
	
${OBJECTDIR}/_ext/1906001428/dns_cache.o: ../cyclone_tcp/dns/dns_cache.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_cache.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_cache.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_cache.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_cache.o ../cyclone_tcp/dns/dns_cache.c   
	
${OBJECTDIR}/_ext/1906001428/dns_client.o: ../cyclone_tcp/dns/dns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_client.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_client.o ../cyclone_tcp/dns/dns_client.c   
	
${OBJECTDIR}/_ext/1906001428/dns_common.o: ../cyclone_tcp/dns/dns_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_common.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_common.o ../cyclone_tcp/dns/dns_common.c   
	
${OBJECTDIR}/_ext/1906001428/dns_debug.o: ../cyclone_tcp/dns/dns_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_debug.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_debug.o ../cyclone_tcp/dns/dns_debug.c   
	
${OBJECTDIR}/_ext/236961974/dp83848.o: ../cyclone_tcp/drivers/dp83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/236961974 
	@${RM} ${OBJECTDIR}/_ext/236961974/dp83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/236961974/dp83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/236961974/dp83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/236961974/dp83848.o.d" -o ${OBJECTDIR}/_ext/236961974/dp83848.o ../cyclone_tcp/drivers/dp83848.c   
	
${OBJECTDIR}/_ext/236961974/pic32mx_eth.o: ../cyclone_tcp/drivers/pic32mx_eth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/236961974 
	@${RM} ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o.d 
	@${RM} ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/236961974/pic32mx_eth.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/236961974/pic32mx_eth.o.d" -o ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o ../cyclone_tcp/drivers/pic32mx_eth.c   
	
${OBJECTDIR}/_ext/1043372803/http_server.o: ../cyclone_tcp/http/http_server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/http_server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/http_server.o.d" -o ${OBJECTDIR}/_ext/1043372803/http_server.o ../cyclone_tcp/http/http_server.c   
	
${OBJECTDIR}/_ext/1043372803/http_server_auth.o: ../cyclone_tcp/http/http_server_auth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_auth.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_auth.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/http_server_auth.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/http_server_auth.o.d" -o ${OBJECTDIR}/_ext/1043372803/http_server_auth.o ../cyclone_tcp/http/http_server_auth.c   
	
${OBJECTDIR}/_ext/1043372803/http_server_misc.o: ../cyclone_tcp/http/http_server_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/http_server_misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/http_server_misc.o.d" -o ${OBJECTDIR}/_ext/1043372803/http_server_misc.o ../cyclone_tcp/http/http_server_misc.c   
	
${OBJECTDIR}/_ext/1043372803/mime.o: ../cyclone_tcp/http/mime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/mime.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/mime.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/mime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/mime.o.d" -o ${OBJECTDIR}/_ext/1043372803/mime.o ../cyclone_tcp/http/mime.c   
	
${OBJECTDIR}/_ext/1043372803/ssi.o: ../cyclone_tcp/http/ssi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/ssi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/ssi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/ssi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/ssi.o.d" -o ${OBJECTDIR}/_ext/1043372803/ssi.o ../cyclone_tcp/http/ssi.c   
	
${OBJECTDIR}/_ext/1043346854/arp.o: ../cyclone_tcp/ipv4/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/arp.o.d" -o ${OBJECTDIR}/_ext/1043346854/arp.o ../cyclone_tcp/ipv4/arp.c   
	
${OBJECTDIR}/_ext/1043346854/auto_ip.o: ../cyclone_tcp/ipv4/auto_ip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/auto_ip.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/auto_ip.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/auto_ip.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/auto_ip.o.d" -o ${OBJECTDIR}/_ext/1043346854/auto_ip.o ../cyclone_tcp/ipv4/auto_ip.c   
	
${OBJECTDIR}/_ext/1043346854/icmp.o: ../cyclone_tcp/ipv4/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/icmp.o.d" -o ${OBJECTDIR}/_ext/1043346854/icmp.o ../cyclone_tcp/ipv4/icmp.c   
	
${OBJECTDIR}/_ext/1043346854/igmp.o: ../cyclone_tcp/ipv4/igmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/igmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/igmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/igmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/igmp.o.d" -o ${OBJECTDIR}/_ext/1043346854/igmp.o ../cyclone_tcp/ipv4/igmp.c   
	
${OBJECTDIR}/_ext/1043346854/ipv4.o: ../cyclone_tcp/ipv4/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/ipv4.o.d" -o ${OBJECTDIR}/_ext/1043346854/ipv4.o ../cyclone_tcp/ipv4/ipv4.c   
	
${OBJECTDIR}/_ext/1043346854/ipv4_frag.o: ../cyclone_tcp/ipv4/ipv4_frag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/ipv4_frag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/ipv4_frag.o.d" -o ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o ../cyclone_tcp/ipv4/ipv4_frag.c   
	
${OBJECTDIR}/_ext/1043239407/mdns_client.o: ../cyclone_tcp/mdns/mdns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043239407 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043239407/mdns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043239407/mdns_client.o.d" -o ${OBJECTDIR}/_ext/1043239407/mdns_client.o ../cyclone_tcp/mdns/mdns_client.c   
	
${OBJECTDIR}/_ext/1043239407/mdns_common.o: ../cyclone_tcp/mdns/mdns_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043239407 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043239407/mdns_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043239407/mdns_common.o.d" -o ${OBJECTDIR}/_ext/1043239407/mdns_common.o ../cyclone_tcp/mdns/mdns_common.c   
	
${OBJECTDIR}/_ext/1043239407/mdns_responder.o: ../cyclone_tcp/mdns/mdns_responder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043239407 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_responder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_responder.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043239407/mdns_responder.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043239407/mdns_responder.o.d" -o ${OBJECTDIR}/_ext/1043239407/mdns_responder.o ../cyclone_tcp/mdns/mdns_responder.c   
	
${OBJECTDIR}/_ext/159451891/nbns_client.o: ../cyclone_tcp/netbios/nbns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159451891 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159451891/nbns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/159451891/nbns_client.o.d" -o ${OBJECTDIR}/_ext/159451891/nbns_client.o ../cyclone_tcp/netbios/nbns_client.c   
	
${OBJECTDIR}/_ext/159451891/nbns_common.o: ../cyclone_tcp/netbios/nbns_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159451891 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159451891/nbns_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/159451891/nbns_common.o.d" -o ${OBJECTDIR}/_ext/159451891/nbns_common.o ../cyclone_tcp/netbios/nbns_common.c   
	
${OBJECTDIR}/_ext/159451891/nbns_responder.o: ../cyclone_tcp/netbios/nbns_responder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159451891 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_responder.o.d 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_responder.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159451891/nbns_responder.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/159451891/nbns_responder.o.d" -o ${OBJECTDIR}/_ext/159451891/nbns_responder.o ../cyclone_tcp/netbios/nbns_responder.c   
	
${OBJECTDIR}/_ext/1043051829/smtp_client.o: ../cyclone_tcp/smtp/smtp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043051829 
	@${RM} ${OBJECTDIR}/_ext/1043051829/smtp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043051829/smtp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043051829/smtp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043051829/smtp_client.o.d" -o ${OBJECTDIR}/_ext/1043051829/smtp_client.o ../cyclone_tcp/smtp/smtp_client.c   
	
${OBJECTDIR}/_ext/1043050868/sntp_client.o: ../cyclone_tcp/sntp/sntp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043050868 
	@${RM} ${OBJECTDIR}/_ext/1043050868/sntp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043050868/sntp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043050868/sntp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043050868/sntp_client.o.d" -o ${OBJECTDIR}/_ext/1043050868/sntp_client.o ../cyclone_tcp/sntp/sntp_client.c   
	
${OBJECTDIR}/_ext/1333908079/chargen.o: ../cyclone_tcp/std_services/chargen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/chargen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/chargen.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/chargen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/chargen.o.d" -o ${OBJECTDIR}/_ext/1333908079/chargen.o ../cyclone_tcp/std_services/chargen.c   
	
${OBJECTDIR}/_ext/1333908079/daytime.o: ../cyclone_tcp/std_services/daytime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/daytime.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/daytime.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/daytime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/daytime.o.d" -o ${OBJECTDIR}/_ext/1333908079/daytime.o ../cyclone_tcp/std_services/daytime.c   
	
${OBJECTDIR}/_ext/1333908079/discard.o: ../cyclone_tcp/std_services/discard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/discard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/discard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/discard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/discard.o.d" -o ${OBJECTDIR}/_ext/1333908079/discard.o ../cyclone_tcp/std_services/discard.c   
	
${OBJECTDIR}/_ext/1333908079/echo.o: ../cyclone_tcp/std_services/echo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/echo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/echo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/echo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/echo.o.d" -o ${OBJECTDIR}/_ext/1333908079/echo.o ../cyclone_tcp/std_services/echo.c   
	
${OBJECTDIR}/_ext/1653734595/port.o: ../common/freertos/portable/mplab/pic32mx/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1653734595 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1653734595/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1653734595/port.o.d" -o ${OBJECTDIR}/_ext/1653734595/port.o ../common/freertos/portable/mplab/pic32mx/port.c   
	
${OBJECTDIR}/_ext/563807591/croutine.o: ../common/freertos/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/croutine.o.d" -o ${OBJECTDIR}/_ext/563807591/croutine.o ../common/freertos/croutine.c   
	
${OBJECTDIR}/_ext/563807591/event_groups.o: ../common/freertos/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/event_groups.o.d" -o ${OBJECTDIR}/_ext/563807591/event_groups.o ../common/freertos/event_groups.c   
	
${OBJECTDIR}/_ext/563807591/list.o: ../common/freertos/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/list.o.d" -o ${OBJECTDIR}/_ext/563807591/list.o ../common/freertos/list.c   
	
${OBJECTDIR}/_ext/563807591/queue.o: ../common/freertos/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/queue.o.d" -o ${OBJECTDIR}/_ext/563807591/queue.o ../common/freertos/queue.c   
	
${OBJECTDIR}/_ext/563807591/tasks.o: ../common/freertos/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/tasks.o.d" -o ${OBJECTDIR}/_ext/563807591/tasks.o ../common/freertos/tasks.c   
	
${OBJECTDIR}/_ext/563807591/timers.o: ../common/freertos/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/timers.o.d" -o ${OBJECTDIR}/_ext/563807591/timers.o ../common/freertos/timers.c   
	
${OBJECTDIR}/_ext/1209349994/heap_3.o: ../common/freertos/portable/memmang/heap_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209349994 
	@${RM} ${OBJECTDIR}/_ext/1209349994/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209349994/heap_3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209349994/heap_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1209349994/heap_3.o.d" -o ${OBJECTDIR}/_ext/1209349994/heap_3.o ../common/freertos/portable/memmang/heap_3.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c   
	
${OBJECTDIR}/_ext/1360937237/sprintf.o: ../src/sprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sprintf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sprintf.o.d" -o ${OBJECTDIR}/_ext/1360937237/sprintf.o ../src/sprintf.c   
	
${OBJECTDIR}/_ext/1360937237/strtok_r.o: ../src/strtok_r.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/strtok_r.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/strtok_r.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/strtok_r.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/strtok_r.o.d" -o ${OBJECTDIR}/_ext/1360937237/strtok_r.o ../src/strtok_r.c   
	
${OBJECTDIR}/_ext/1360937237/res.o: ../src/res.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/res.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/res.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/res.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/res.o.d" -o ${OBJECTDIR}/_ext/1360937237/res.o ../src/res.c   
	
${OBJECTDIR}/_ext/1360937237/ext_int_driver.o: ../src/ext_int_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ext_int_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ext_int_driver.o.d" -o ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o ../src/ext_int_driver.c   
	
${OBJECTDIR}/_ext/1360937237/SPIFlash.o: ../src/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/SPIFlash.o.d" -o ${OBJECTDIR}/_ext/1360937237/SPIFlash.o ../src/SPIFlash.c   
	
${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o: ../src/SPIMACEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o.d" -o ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o ../src/SPIMACEEPROM.c   
	
${OBJECTDIR}/_ext/1360937237/VM204.o: ../src/VM204.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VM204.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VM204.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VM204.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/VM204.o.d" -o ${OBJECTDIR}/_ext/1360937237/VM204.o ../src/VM204.c   
	
${OBJECTDIR}/_ext/1360937237/analog.o: ../src/analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/analog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/analog.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/analog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/analog.o.d" -o ${OBJECTDIR}/_ext/1360937237/analog.o ../src/analog.c   
	
${OBJECTDIR}/_ext/1360937237/discovery.o: ../src/discovery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/discovery.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/discovery.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/discovery.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/discovery.o.d" -o ${OBJECTDIR}/_ext/1360937237/discovery.o ../src/discovery.c   
	
${OBJECTDIR}/_ext/1360937237/inputs.o: ../src/inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/inputs.o.d" -o ${OBJECTDIR}/_ext/1360937237/inputs.o ../src/inputs.c   
	
${OBJECTDIR}/_ext/1360937237/relays.o: ../src/relays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/relays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/relays.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/relays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/relays.o.d" -o ${OBJECTDIR}/_ext/1360937237/relays.o ../src/relays.c   
	
${OBJECTDIR}/_ext/1360937237/cJSON.o: ../src/cJSON.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cJSON.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cJSON.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/cJSON.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/cJSON.o.d" -o ${OBJECTDIR}/_ext/1360937237/cJSON.o ../src/cJSON.c   
	
else
${OBJECTDIR}/_ext/1270477542/date_time.o: ../common/date_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/date_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/date_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/date_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/date_time.o.d" -o ${OBJECTDIR}/_ext/1270477542/date_time.o ../common/date_time.c   
	
${OBJECTDIR}/_ext/1270477542/endian.o: ../common/endian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/endian.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/endian.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/endian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/endian.o.d" -o ${OBJECTDIR}/_ext/1270477542/endian.o ../common/endian.c   
	
${OBJECTDIR}/_ext/1270477542/path.o: ../common/path.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/path.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/path.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/path.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/path.o.d" -o ${OBJECTDIR}/_ext/1270477542/path.o ../common/path.c   
	
${OBJECTDIR}/_ext/1270477542/resource_manager.o: ../common/resource_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/resource_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/resource_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/resource_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/resource_manager.o.d" -o ${OBJECTDIR}/_ext/1270477542/resource_manager.o ../common/resource_manager.c   
	
${OBJECTDIR}/_ext/1270477542/str.o: ../common/str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/str.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/str.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/str.o.d" -o ${OBJECTDIR}/_ext/1270477542/str.o ../common/str.c   
	
${OBJECTDIR}/_ext/1270477542/os_port_freertos.o: ../common/os_port_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1270477542 
	@${RM} ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1270477542/os_port_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1270477542/os_port_freertos.o.d" -o ${OBJECTDIR}/_ext/1270477542/os_port_freertos.o ../common/os_port_freertos.c   
	
${OBJECTDIR}/_ext/1390087560/aes.o: ../cyclone_crypto/aes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/aes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/aes.o.d" -o ${OBJECTDIR}/_ext/1390087560/aes.o ../cyclone_crypto/aes.c   
	
${OBJECTDIR}/_ext/1390087560/aria.o: ../cyclone_crypto/aria.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aria.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/aria.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/aria.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/aria.o.d" -o ${OBJECTDIR}/_ext/1390087560/aria.o ../cyclone_crypto/aria.c   
	
${OBJECTDIR}/_ext/1390087560/asn1.o: ../cyclone_crypto/asn1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/asn1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/asn1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/asn1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/asn1.o.d" -o ${OBJECTDIR}/_ext/1390087560/asn1.o ../cyclone_crypto/asn1.c   
	
${OBJECTDIR}/_ext/1390087560/base64.o: ../cyclone_crypto/base64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/base64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/base64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/base64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/base64.o.d" -o ${OBJECTDIR}/_ext/1390087560/base64.o ../cyclone_crypto/base64.c   
	
${OBJECTDIR}/_ext/1390087560/camellia.o: ../cyclone_crypto/camellia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/camellia.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/camellia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/camellia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/camellia.o.d" -o ${OBJECTDIR}/_ext/1390087560/camellia.o ../cyclone_crypto/camellia.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o: ../cyclone_crypto/cipher_mode_cbc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cbc.o ../cyclone_crypto/cipher_mode_cbc.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o: ../cyclone_crypto/cipher_mode_ccm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ccm.o ../cyclone_crypto/cipher_mode_ccm.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o: ../cyclone_crypto/cipher_mode_cfb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_cfb.o ../cyclone_crypto/cipher_mode_cfb.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o: ../cyclone_crypto/cipher_mode_ctr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ctr.o ../cyclone_crypto/cipher_mode_ctr.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o: ../cyclone_crypto/cipher_mode_ecb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ecb.o ../cyclone_crypto/cipher_mode_ecb.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o: ../cyclone_crypto/cipher_mode_gcm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_gcm.o ../cyclone_crypto/cipher_mode_gcm.c   
	
${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o: ../cyclone_crypto/cipher_mode_ofb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o.d" -o ${OBJECTDIR}/_ext/1390087560/cipher_mode_ofb.o ../cyclone_crypto/cipher_mode_ofb.c   
	
${OBJECTDIR}/_ext/1390087560/des.o: ../cyclone_crypto/des.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/des.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/des.o.d" -o ${OBJECTDIR}/_ext/1390087560/des.o ../cyclone_crypto/des.c   
	
${OBJECTDIR}/_ext/1390087560/des3.o: ../cyclone_crypto/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/des3.o.d" -o ${OBJECTDIR}/_ext/1390087560/des3.o ../cyclone_crypto/des3.c   
	
${OBJECTDIR}/_ext/1390087560/dh.o: ../cyclone_crypto/dh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/dh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/dh.o.d" -o ${OBJECTDIR}/_ext/1390087560/dh.o ../cyclone_crypto/dh.c   
	
${OBJECTDIR}/_ext/1390087560/dsa.o: ../cyclone_crypto/dsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/dsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/dsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/dsa.o.d" -o ${OBJECTDIR}/_ext/1390087560/dsa.o ../cyclone_crypto/dsa.c   
	
${OBJECTDIR}/_ext/1390087560/ec.o: ../cyclone_crypto/ec.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ec.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ec.o.d" -o ${OBJECTDIR}/_ext/1390087560/ec.o ../cyclone_crypto/ec.c   
	
${OBJECTDIR}/_ext/1390087560/ec_curves.o: ../cyclone_crypto/ec_curves.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec_curves.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ec_curves.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ec_curves.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ec_curves.o.d" -o ${OBJECTDIR}/_ext/1390087560/ec_curves.o ../cyclone_crypto/ec_curves.c   
	
${OBJECTDIR}/_ext/1390087560/ecdh.o: ../cyclone_crypto/ecdh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ecdh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ecdh.o.d" -o ${OBJECTDIR}/_ext/1390087560/ecdh.o ../cyclone_crypto/ecdh.c   
	
${OBJECTDIR}/_ext/1390087560/ecdsa.o: ../cyclone_crypto/ecdsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ecdsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ecdsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ecdsa.o.d" -o ${OBJECTDIR}/_ext/1390087560/ecdsa.o ../cyclone_crypto/ecdsa.c   
	
${OBJECTDIR}/_ext/1390087560/hmac.o: ../cyclone_crypto/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/hmac.o.d" -o ${OBJECTDIR}/_ext/1390087560/hmac.o ../cyclone_crypto/hmac.c   
	
${OBJECTDIR}/_ext/1390087560/idea.o: ../cyclone_crypto/idea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/idea.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/idea.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/idea.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/idea.o.d" -o ${OBJECTDIR}/_ext/1390087560/idea.o ../cyclone_crypto/idea.c   
	
${OBJECTDIR}/_ext/1390087560/md2.o: ../cyclone_crypto/md2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/md2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/md2.o.d" -o ${OBJECTDIR}/_ext/1390087560/md2.o ../cyclone_crypto/md2.c   
	
${OBJECTDIR}/_ext/1390087560/md4.o: ../cyclone_crypto/md4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/md4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/md4.o.d" -o ${OBJECTDIR}/_ext/1390087560/md4.o ../cyclone_crypto/md4.c   
	
${OBJECTDIR}/_ext/1390087560/md5.o: ../cyclone_crypto/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/md5.o.d" -o ${OBJECTDIR}/_ext/1390087560/md5.o ../cyclone_crypto/md5.c   
	
${OBJECTDIR}/_ext/1390087560/mpi.o: ../cyclone_crypto/mpi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/mpi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/mpi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/mpi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/mpi.o.d" -o ${OBJECTDIR}/_ext/1390087560/mpi.o ../cyclone_crypto/mpi.c   
	
${OBJECTDIR}/_ext/1390087560/oid.o: ../cyclone_crypto/oid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/oid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/oid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/oid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/oid.o.d" -o ${OBJECTDIR}/_ext/1390087560/oid.o ../cyclone_crypto/oid.c   
	
${OBJECTDIR}/_ext/1390087560/pem.o: ../cyclone_crypto/pem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/pem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/pem.o.d" -o ${OBJECTDIR}/_ext/1390087560/pem.o ../cyclone_crypto/pem.c   
	
${OBJECTDIR}/_ext/1390087560/pkcs5.o: ../cyclone_crypto/pkcs5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pkcs5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/pkcs5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/pkcs5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/pkcs5.o.d" -o ${OBJECTDIR}/_ext/1390087560/pkcs5.o ../cyclone_crypto/pkcs5.c   
	
${OBJECTDIR}/_ext/1390087560/rc4.o: ../cyclone_crypto/rc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/rc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/rc4.o.d" -o ${OBJECTDIR}/_ext/1390087560/rc4.o ../cyclone_crypto/rc4.c   
	
${OBJECTDIR}/_ext/1390087560/rc6.o: ../cyclone_crypto/rc6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rc6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/rc6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/rc6.o.d" -o ${OBJECTDIR}/_ext/1390087560/rc6.o ../cyclone_crypto/rc6.c   
	
${OBJECTDIR}/_ext/1390087560/ripemd128.o: ../cyclone_crypto/ripemd128.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd128.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd128.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ripemd128.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ripemd128.o.d" -o ${OBJECTDIR}/_ext/1390087560/ripemd128.o ../cyclone_crypto/ripemd128.c   
	
${OBJECTDIR}/_ext/1390087560/ripemd160.o: ../cyclone_crypto/ripemd160.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd160.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/ripemd160.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/ripemd160.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/ripemd160.o.d" -o ${OBJECTDIR}/_ext/1390087560/ripemd160.o ../cyclone_crypto/ripemd160.c   
	
${OBJECTDIR}/_ext/1390087560/rsa.o: ../cyclone_crypto/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/rsa.o.d" -o ${OBJECTDIR}/_ext/1390087560/rsa.o ../cyclone_crypto/rsa.c   
	
${OBJECTDIR}/_ext/1390087560/seed.o: ../cyclone_crypto/seed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/seed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/seed.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/seed.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/seed.o.d" -o ${OBJECTDIR}/_ext/1390087560/seed.o ../cyclone_crypto/seed.c   
	
${OBJECTDIR}/_ext/1390087560/sha1.o: ../cyclone_crypto/sha1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha1.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha1.o ../cyclone_crypto/sha1.c   
	
${OBJECTDIR}/_ext/1390087560/sha224.o: ../cyclone_crypto/sha224.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha224.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha224.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha224.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha224.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha224.o ../cyclone_crypto/sha224.c   
	
${OBJECTDIR}/_ext/1390087560/sha256.o: ../cyclone_crypto/sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha256.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha256.o ../cyclone_crypto/sha256.c   
	
${OBJECTDIR}/_ext/1390087560/sha384.o: ../cyclone_crypto/sha384.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha384.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha384.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha384.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha384.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha384.o ../cyclone_crypto/sha384.c   
	
${OBJECTDIR}/_ext/1390087560/sha512.o: ../cyclone_crypto/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha512.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha512.o ../cyclone_crypto/sha512.c   
	
${OBJECTDIR}/_ext/1390087560/sha512_224.o: ../cyclone_crypto/sha512_224.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_224.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_224.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha512_224.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha512_224.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha512_224.o ../cyclone_crypto/sha512_224.c   
	
${OBJECTDIR}/_ext/1390087560/sha512_256.o: ../cyclone_crypto/sha512_256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/sha512_256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/sha512_256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/sha512_256.o.d" -o ${OBJECTDIR}/_ext/1390087560/sha512_256.o ../cyclone_crypto/sha512_256.c   
	
${OBJECTDIR}/_ext/1390087560/tiger.o: ../cyclone_crypto/tiger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/tiger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/tiger.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/tiger.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/tiger.o.d" -o ${OBJECTDIR}/_ext/1390087560/tiger.o ../cyclone_crypto/tiger.c   
	
${OBJECTDIR}/_ext/1390087560/whirlpool.o: ../cyclone_crypto/whirlpool.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/whirlpool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/whirlpool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/whirlpool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/whirlpool.o.d" -o ${OBJECTDIR}/_ext/1390087560/whirlpool.o ../cyclone_crypto/whirlpool.c   
	
${OBJECTDIR}/_ext/1390087560/x509.o: ../cyclone_crypto/x509.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/x509.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/x509.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/x509.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/x509.o.d" -o ${OBJECTDIR}/_ext/1390087560/x509.o ../cyclone_crypto/x509.c   
	
${OBJECTDIR}/_ext/1390087560/yarrow.o: ../cyclone_crypto/yarrow.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1390087560 
	@${RM} ${OBJECTDIR}/_ext/1390087560/yarrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1390087560/yarrow.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1390087560/yarrow.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1390087560/yarrow.o.d" -o ${OBJECTDIR}/_ext/1390087560/yarrow.o ../cyclone_crypto/yarrow.c   
	
${OBJECTDIR}/_ext/1058722139/ssl_common.o: ../cyclone_ssl/ssl_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/ssl_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/ssl_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/ssl_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/ssl_common.o.d" -o ${OBJECTDIR}/_ext/1058722139/ssl_common.o ../cyclone_ssl/ssl_common.c   
	
${OBJECTDIR}/_ext/1058722139/tls.o: ../cyclone_ssl/tls.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls.o ../cyclone_ssl/tls.c   
	
${OBJECTDIR}/_ext/1058722139/tls_cache.o: ../cyclone_ssl/tls_cache.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cache.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_cache.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_cache.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_cache.o ../cyclone_ssl/tls_cache.c   
	
${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o: ../cyclone_ssl/tls_cipher_suites.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_cipher_suites.o ../cyclone_ssl/tls_cipher_suites.c   
	
${OBJECTDIR}/_ext/1058722139/tls_client.o: ../cyclone_ssl/tls_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_client.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_client.o ../cyclone_ssl/tls_client.c   
	
${OBJECTDIR}/_ext/1058722139/tls_common.o: ../cyclone_ssl/tls_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_common.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_common.o ../cyclone_ssl/tls_common.c   
	
${OBJECTDIR}/_ext/1058722139/tls_io.o: ../cyclone_ssl/tls_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_io.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_io.o ../cyclone_ssl/tls_io.c   
	
${OBJECTDIR}/_ext/1058722139/tls_misc.o: ../cyclone_ssl/tls_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_misc.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_misc.o ../cyclone_ssl/tls_misc.c   
	
${OBJECTDIR}/_ext/1058722139/tls_record.o: ../cyclone_ssl/tls_record.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_record.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_record.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_record.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_record.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_record.o ../cyclone_ssl/tls_record.c   
	
${OBJECTDIR}/_ext/1058722139/tls_server.o: ../cyclone_ssl/tls_server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1058722139 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058722139/tls_server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058722139/tls_server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1058722139/tls_server.o.d" -o ${OBJECTDIR}/_ext/1058722139/tls_server.o ../cyclone_ssl/tls_server.c   
	
${OBJECTDIR}/_ext/1043526636/bsd_socket.o: ../cyclone_tcp/core/bsd_socket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/bsd_socket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/bsd_socket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/bsd_socket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/bsd_socket.o.d" -o ${OBJECTDIR}/_ext/1043526636/bsd_socket.o ../cyclone_tcp/core/bsd_socket.c   
	
${OBJECTDIR}/_ext/1043526636/ethernet.o: ../cyclone_tcp/core/ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ethernet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/ethernet.o.d" -o ${OBJECTDIR}/_ext/1043526636/ethernet.o ../cyclone_tcp/core/ethernet.c   
	
${OBJECTDIR}/_ext/1043526636/ip.o: ../cyclone_tcp/core/ip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ip.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ip.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/ip.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/ip.o.d" -o ${OBJECTDIR}/_ext/1043526636/ip.o ../cyclone_tcp/core/ip.c   
	
${OBJECTDIR}/_ext/1043526636/net.o: ../cyclone_tcp/core/net.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/net.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/net.o.d" -o ${OBJECTDIR}/_ext/1043526636/net.o ../cyclone_tcp/core/net.c   
	
${OBJECTDIR}/_ext/1043526636/net_mem.o: ../cyclone_tcp/core/net_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/net_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/net_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/net_mem.o.d" -o ${OBJECTDIR}/_ext/1043526636/net_mem.o ../cyclone_tcp/core/net_mem.c   
	
${OBJECTDIR}/_ext/1043526636/nic.o: ../cyclone_tcp/core/nic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/nic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/nic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/nic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/nic.o.d" -o ${OBJECTDIR}/_ext/1043526636/nic.o ../cyclone_tcp/core/nic.c   
	
${OBJECTDIR}/_ext/1043526636/ping.o: ../cyclone_tcp/core/ping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/ping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/ping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/ping.o.d" -o ${OBJECTDIR}/_ext/1043526636/ping.o ../cyclone_tcp/core/ping.c   
	
${OBJECTDIR}/_ext/1043526636/raw_socket.o: ../cyclone_tcp/core/raw_socket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/raw_socket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/raw_socket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/raw_socket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/raw_socket.o.d" -o ${OBJECTDIR}/_ext/1043526636/raw_socket.o ../cyclone_tcp/core/raw_socket.c   
	
${OBJECTDIR}/_ext/1043526636/socket.o: ../cyclone_tcp/core/socket.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/socket.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/socket.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/socket.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/socket.o.d" -o ${OBJECTDIR}/_ext/1043526636/socket.o ../cyclone_tcp/core/socket.c   
	
${OBJECTDIR}/_ext/1043526636/tcp.o: ../cyclone_tcp/core/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp.o ../cyclone_tcp/core/tcp.c   
	
${OBJECTDIR}/_ext/1043526636/tcp_fsm.o: ../cyclone_tcp/core/tcp_fsm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp_fsm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp_fsm.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp_fsm.o ../cyclone_tcp/core/tcp_fsm.c   
	
${OBJECTDIR}/_ext/1043526636/tcp_misc.o: ../cyclone_tcp/core/tcp_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp_misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp_misc.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp_misc.o ../cyclone_tcp/core/tcp_misc.c   
	
${OBJECTDIR}/_ext/1043526636/tcp_timer.o: ../cyclone_tcp/core/tcp_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/tcp_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/tcp_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/tcp_timer.o.d" -o ${OBJECTDIR}/_ext/1043526636/tcp_timer.o ../cyclone_tcp/core/tcp_timer.c   
	
${OBJECTDIR}/_ext/1043526636/udp.o: ../cyclone_tcp/core/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043526636 
	@${RM} ${OBJECTDIR}/_ext/1043526636/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043526636/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043526636/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043526636/udp.o.d" -o ${OBJECTDIR}/_ext/1043526636/udp.o ../cyclone_tcp/core/udp.c   
	
${OBJECTDIR}/_ext/1043504026/dhcp_client.o: ../cyclone_tcp/dhcp/dhcp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043504026 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043504026/dhcp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043504026/dhcp_client.o.d" -o ${OBJECTDIR}/_ext/1043504026/dhcp_client.o ../cyclone_tcp/dhcp/dhcp_client.c   
	
${OBJECTDIR}/_ext/1043504026/dhcp_common.o: ../cyclone_tcp/dhcp/dhcp_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043504026 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043504026/dhcp_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043504026/dhcp_common.o.d" -o ${OBJECTDIR}/_ext/1043504026/dhcp_common.o ../cyclone_tcp/dhcp/dhcp_common.c   
	
${OBJECTDIR}/_ext/1043504026/dhcp_debug.o: ../cyclone_tcp/dhcp/dhcp_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043504026 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043504026/dhcp_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043504026/dhcp_debug.o.d" -o ${OBJECTDIR}/_ext/1043504026/dhcp_debug.o ../cyclone_tcp/dhcp/dhcp_debug.c   
	
${OBJECTDIR}/_ext/1906001428/dns_cache.o: ../cyclone_tcp/dns/dns_cache.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_cache.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_cache.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_cache.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_cache.o ../cyclone_tcp/dns/dns_cache.c   
	
${OBJECTDIR}/_ext/1906001428/dns_client.o: ../cyclone_tcp/dns/dns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_client.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_client.o ../cyclone_tcp/dns/dns_client.c   
	
${OBJECTDIR}/_ext/1906001428/dns_common.o: ../cyclone_tcp/dns/dns_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_common.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_common.o ../cyclone_tcp/dns/dns_common.c   
	
${OBJECTDIR}/_ext/1906001428/dns_debug.o: ../cyclone_tcp/dns/dns_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1906001428 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1906001428/dns_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1906001428/dns_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1906001428/dns_debug.o.d" -o ${OBJECTDIR}/_ext/1906001428/dns_debug.o ../cyclone_tcp/dns/dns_debug.c   
	
${OBJECTDIR}/_ext/236961974/dp83848.o: ../cyclone_tcp/drivers/dp83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/236961974 
	@${RM} ${OBJECTDIR}/_ext/236961974/dp83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/236961974/dp83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/236961974/dp83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/236961974/dp83848.o.d" -o ${OBJECTDIR}/_ext/236961974/dp83848.o ../cyclone_tcp/drivers/dp83848.c   
	
${OBJECTDIR}/_ext/236961974/pic32mx_eth.o: ../cyclone_tcp/drivers/pic32mx_eth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/236961974 
	@${RM} ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o.d 
	@${RM} ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/236961974/pic32mx_eth.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/236961974/pic32mx_eth.o.d" -o ${OBJECTDIR}/_ext/236961974/pic32mx_eth.o ../cyclone_tcp/drivers/pic32mx_eth.c   
	
${OBJECTDIR}/_ext/1043372803/http_server.o: ../cyclone_tcp/http/http_server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/http_server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/http_server.o.d" -o ${OBJECTDIR}/_ext/1043372803/http_server.o ../cyclone_tcp/http/http_server.c   
	
${OBJECTDIR}/_ext/1043372803/http_server_auth.o: ../cyclone_tcp/http/http_server_auth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_auth.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_auth.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/http_server_auth.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/http_server_auth.o.d" -o ${OBJECTDIR}/_ext/1043372803/http_server_auth.o ../cyclone_tcp/http/http_server_auth.c   
	
${OBJECTDIR}/_ext/1043372803/http_server_misc.o: ../cyclone_tcp/http/http_server_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/http_server_misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/http_server_misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/http_server_misc.o.d" -o ${OBJECTDIR}/_ext/1043372803/http_server_misc.o ../cyclone_tcp/http/http_server_misc.c   
	
${OBJECTDIR}/_ext/1043372803/mime.o: ../cyclone_tcp/http/mime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/mime.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/mime.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/mime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/mime.o.d" -o ${OBJECTDIR}/_ext/1043372803/mime.o ../cyclone_tcp/http/mime.c   
	
${OBJECTDIR}/_ext/1043372803/ssi.o: ../cyclone_tcp/http/ssi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043372803 
	@${RM} ${OBJECTDIR}/_ext/1043372803/ssi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043372803/ssi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043372803/ssi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043372803/ssi.o.d" -o ${OBJECTDIR}/_ext/1043372803/ssi.o ../cyclone_tcp/http/ssi.c   
	
${OBJECTDIR}/_ext/1043346854/arp.o: ../cyclone_tcp/ipv4/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/arp.o.d" -o ${OBJECTDIR}/_ext/1043346854/arp.o ../cyclone_tcp/ipv4/arp.c   
	
${OBJECTDIR}/_ext/1043346854/auto_ip.o: ../cyclone_tcp/ipv4/auto_ip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/auto_ip.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/auto_ip.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/auto_ip.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/auto_ip.o.d" -o ${OBJECTDIR}/_ext/1043346854/auto_ip.o ../cyclone_tcp/ipv4/auto_ip.c   
	
${OBJECTDIR}/_ext/1043346854/icmp.o: ../cyclone_tcp/ipv4/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/icmp.o.d" -o ${OBJECTDIR}/_ext/1043346854/icmp.o ../cyclone_tcp/ipv4/icmp.c   
	
${OBJECTDIR}/_ext/1043346854/igmp.o: ../cyclone_tcp/ipv4/igmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/igmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/igmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/igmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/igmp.o.d" -o ${OBJECTDIR}/_ext/1043346854/igmp.o ../cyclone_tcp/ipv4/igmp.c   
	
${OBJECTDIR}/_ext/1043346854/ipv4.o: ../cyclone_tcp/ipv4/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/ipv4.o.d" -o ${OBJECTDIR}/_ext/1043346854/ipv4.o ../cyclone_tcp/ipv4/ipv4.c   
	
${OBJECTDIR}/_ext/1043346854/ipv4_frag.o: ../cyclone_tcp/ipv4/ipv4_frag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043346854 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043346854/ipv4_frag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043346854/ipv4_frag.o.d" -o ${OBJECTDIR}/_ext/1043346854/ipv4_frag.o ../cyclone_tcp/ipv4/ipv4_frag.c   
	
${OBJECTDIR}/_ext/1043239407/mdns_client.o: ../cyclone_tcp/mdns/mdns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043239407 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043239407/mdns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043239407/mdns_client.o.d" -o ${OBJECTDIR}/_ext/1043239407/mdns_client.o ../cyclone_tcp/mdns/mdns_client.c   
	
${OBJECTDIR}/_ext/1043239407/mdns_common.o: ../cyclone_tcp/mdns/mdns_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043239407 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043239407/mdns_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043239407/mdns_common.o.d" -o ${OBJECTDIR}/_ext/1043239407/mdns_common.o ../cyclone_tcp/mdns/mdns_common.c   
	
${OBJECTDIR}/_ext/1043239407/mdns_responder.o: ../cyclone_tcp/mdns/mdns_responder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043239407 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_responder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043239407/mdns_responder.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043239407/mdns_responder.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043239407/mdns_responder.o.d" -o ${OBJECTDIR}/_ext/1043239407/mdns_responder.o ../cyclone_tcp/mdns/mdns_responder.c   
	
${OBJECTDIR}/_ext/159451891/nbns_client.o: ../cyclone_tcp/netbios/nbns_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159451891 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159451891/nbns_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/159451891/nbns_client.o.d" -o ${OBJECTDIR}/_ext/159451891/nbns_client.o ../cyclone_tcp/netbios/nbns_client.c   
	
${OBJECTDIR}/_ext/159451891/nbns_common.o: ../cyclone_tcp/netbios/nbns_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159451891 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159451891/nbns_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/159451891/nbns_common.o.d" -o ${OBJECTDIR}/_ext/159451891/nbns_common.o ../cyclone_tcp/netbios/nbns_common.c   
	
${OBJECTDIR}/_ext/159451891/nbns_responder.o: ../cyclone_tcp/netbios/nbns_responder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159451891 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_responder.o.d 
	@${RM} ${OBJECTDIR}/_ext/159451891/nbns_responder.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159451891/nbns_responder.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/159451891/nbns_responder.o.d" -o ${OBJECTDIR}/_ext/159451891/nbns_responder.o ../cyclone_tcp/netbios/nbns_responder.c   
	
${OBJECTDIR}/_ext/1043051829/smtp_client.o: ../cyclone_tcp/smtp/smtp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043051829 
	@${RM} ${OBJECTDIR}/_ext/1043051829/smtp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043051829/smtp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043051829/smtp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043051829/smtp_client.o.d" -o ${OBJECTDIR}/_ext/1043051829/smtp_client.o ../cyclone_tcp/smtp/smtp_client.c   
	
${OBJECTDIR}/_ext/1043050868/sntp_client.o: ../cyclone_tcp/sntp/sntp_client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1043050868 
	@${RM} ${OBJECTDIR}/_ext/1043050868/sntp_client.o.d 
	@${RM} ${OBJECTDIR}/_ext/1043050868/sntp_client.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1043050868/sntp_client.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1043050868/sntp_client.o.d" -o ${OBJECTDIR}/_ext/1043050868/sntp_client.o ../cyclone_tcp/sntp/sntp_client.c   
	
${OBJECTDIR}/_ext/1333908079/chargen.o: ../cyclone_tcp/std_services/chargen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/chargen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/chargen.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/chargen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/chargen.o.d" -o ${OBJECTDIR}/_ext/1333908079/chargen.o ../cyclone_tcp/std_services/chargen.c   
	
${OBJECTDIR}/_ext/1333908079/daytime.o: ../cyclone_tcp/std_services/daytime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/daytime.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/daytime.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/daytime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/daytime.o.d" -o ${OBJECTDIR}/_ext/1333908079/daytime.o ../cyclone_tcp/std_services/daytime.c   
	
${OBJECTDIR}/_ext/1333908079/discard.o: ../cyclone_tcp/std_services/discard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/discard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/discard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/discard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/discard.o.d" -o ${OBJECTDIR}/_ext/1333908079/discard.o ../cyclone_tcp/std_services/discard.c   
	
${OBJECTDIR}/_ext/1333908079/echo.o: ../cyclone_tcp/std_services/echo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1333908079 
	@${RM} ${OBJECTDIR}/_ext/1333908079/echo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1333908079/echo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1333908079/echo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1333908079/echo.o.d" -o ${OBJECTDIR}/_ext/1333908079/echo.o ../cyclone_tcp/std_services/echo.c   
	
${OBJECTDIR}/_ext/1653734595/port.o: ../common/freertos/portable/mplab/pic32mx/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1653734595 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1653734595/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1653734595/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1653734595/port.o.d" -o ${OBJECTDIR}/_ext/1653734595/port.o ../common/freertos/portable/mplab/pic32mx/port.c   
	
${OBJECTDIR}/_ext/563807591/croutine.o: ../common/freertos/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/croutine.o.d" -o ${OBJECTDIR}/_ext/563807591/croutine.o ../common/freertos/croutine.c   
	
${OBJECTDIR}/_ext/563807591/event_groups.o: ../common/freertos/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/event_groups.o.d" -o ${OBJECTDIR}/_ext/563807591/event_groups.o ../common/freertos/event_groups.c   
	
${OBJECTDIR}/_ext/563807591/list.o: ../common/freertos/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/list.o.d" -o ${OBJECTDIR}/_ext/563807591/list.o ../common/freertos/list.c   
	
${OBJECTDIR}/_ext/563807591/queue.o: ../common/freertos/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/queue.o.d" -o ${OBJECTDIR}/_ext/563807591/queue.o ../common/freertos/queue.c   
	
${OBJECTDIR}/_ext/563807591/tasks.o: ../common/freertos/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/tasks.o.d" -o ${OBJECTDIR}/_ext/563807591/tasks.o ../common/freertos/tasks.c   
	
${OBJECTDIR}/_ext/563807591/timers.o: ../common/freertos/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/563807591 
	@${RM} ${OBJECTDIR}/_ext/563807591/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/563807591/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/563807591/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/563807591/timers.o.d" -o ${OBJECTDIR}/_ext/563807591/timers.o ../common/freertos/timers.c   
	
${OBJECTDIR}/_ext/1209349994/heap_3.o: ../common/freertos/portable/memmang/heap_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1209349994 
	@${RM} ${OBJECTDIR}/_ext/1209349994/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209349994/heap_3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209349994/heap_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1209349994/heap_3.o.d" -o ${OBJECTDIR}/_ext/1209349994/heap_3.o ../common/freertos/portable/memmang/heap_3.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c   
	
${OBJECTDIR}/_ext/1360937237/sprintf.o: ../src/sprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sprintf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sprintf.o.d" -o ${OBJECTDIR}/_ext/1360937237/sprintf.o ../src/sprintf.c   
	
${OBJECTDIR}/_ext/1360937237/strtok_r.o: ../src/strtok_r.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/strtok_r.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/strtok_r.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/strtok_r.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/strtok_r.o.d" -o ${OBJECTDIR}/_ext/1360937237/strtok_r.o ../src/strtok_r.c   
	
${OBJECTDIR}/_ext/1360937237/res.o: ../src/res.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/res.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/res.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/res.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/res.o.d" -o ${OBJECTDIR}/_ext/1360937237/res.o ../src/res.c   
	
${OBJECTDIR}/_ext/1360937237/ext_int_driver.o: ../src/ext_int_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ext_int_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ext_int_driver.o.d" -o ${OBJECTDIR}/_ext/1360937237/ext_int_driver.o ../src/ext_int_driver.c   
	
${OBJECTDIR}/_ext/1360937237/SPIFlash.o: ../src/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/SPIFlash.o.d" -o ${OBJECTDIR}/_ext/1360937237/SPIFlash.o ../src/SPIFlash.c   
	
${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o: ../src/SPIMACEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o.d" -o ${OBJECTDIR}/_ext/1360937237/SPIMACEEPROM.o ../src/SPIMACEEPROM.c   
	
${OBJECTDIR}/_ext/1360937237/VM204.o: ../src/VM204.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VM204.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/VM204.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/VM204.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/VM204.o.d" -o ${OBJECTDIR}/_ext/1360937237/VM204.o ../src/VM204.c   
	
${OBJECTDIR}/_ext/1360937237/analog.o: ../src/analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/analog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/analog.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/analog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/analog.o.d" -o ${OBJECTDIR}/_ext/1360937237/analog.o ../src/analog.c   
	
${OBJECTDIR}/_ext/1360937237/discovery.o: ../src/discovery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/discovery.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/discovery.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/discovery.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/discovery.o.d" -o ${OBJECTDIR}/_ext/1360937237/discovery.o ../src/discovery.c   
	
${OBJECTDIR}/_ext/1360937237/inputs.o: ../src/inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/inputs.o.d" -o ${OBJECTDIR}/_ext/1360937237/inputs.o ../src/inputs.c   
	
${OBJECTDIR}/_ext/1360937237/relays.o: ../src/relays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/relays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/relays.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/relays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/relays.o.d" -o ${OBJECTDIR}/_ext/1360937237/relays.o ../src/relays.c   
	
${OBJECTDIR}/_ext/1360937237/cJSON.o: ../src/cJSON.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cJSON.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/cJSON.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/cJSON.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DUSE_PIC32_ETH_STARTER_KIT -I"../src" -I"../common/microchip/devices/pic32" -I"../common/microchip/boards/common" -I"../common/microchip/boards/pic32_eth_starter_kit" -I"../common/freertos/include" -I"../common/freertos/portable/mplab/pic32mx" -I"../common" -I"../cyclone_tcp" -I"../cyclone_ssl" -I"../cyclone_crypto" -MMD -MF "${OBJECTDIR}/_ext/1360937237/cJSON.o.d" -o ${OBJECTDIR}/_ext/1360937237/cJSON.o ../src/cJSON.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=81920,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=81920,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/mplabx.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [..\utils\ResourceCompiler\bin\rc.exe ${ProjectDir}\..\resources\ ${ProjectDir}\..\src\res.c]"
	@..\utils\ResourceCompiler\bin\rc.exe ${ProjectDir}\..\resources\ ${ProjectDir}\..\src\res.c
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
