// 1-channel LoRa Gateway for ESP8266
// Copyright (c) 2016, 2017, 2018, 2019 Maarten Westenberg version for ESP8266
// Version 6.1.1 E EU868
// Date: 2019-11-06
//
// Based on work done by Thomas Telkamp for Raspberry PI 1ch gateway and many others.
// Contibutions of Dorijan Morelj and Andreas Spies for OLED support.
//
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the MIT License
// which accompanies this distribution, and is available at
// https://opensource.org/licenses/mit-license.php
//
// NO WARRANTY OF ANY KIND IS PROVIDED
//
// Author: Maarten Westenberg (mw12554@hotmail.com)
//
// This file contains a number of compile-time settings that can be set on (=1) or off (=0)
// The disadvantage of compile time is minor compared to the memory gain of not having
// too much code compiled and loaded on your ESP8266.
//
// NOTE: 
// If version if vor ESP32 Halard board, compile with ESP32 setting and board 
// "ESP32 Dev Module" or "Heltec WiFi Lora 32"
// 
// If version is for Comresult or Halard board, compile with "Wemos R1 D1" and choose
// the right _PIN_OUT below. Selecting OLED while that is not connected does not 
// really matter.
// ----------------------------------------------------------------------------------------

#define VERSION "V.6.1.1.E.EU868; 191106c"

// This value of DEBUG determines whether some parts of code get compiled.
// Also this is the initial value of debug parameter. 
// The value can be changed using the admin webserver
// For operational use, set initial DEBUG vaulue 0
#define DEBUG 1


// Debug message will be put on Serial is this one is set.
// If set to 0, no USB Serial prints are done
// Set to 1 it will prinr all user level messages (with correct debug set)
// If set to 2 it will also print interrupt messages (not recommended)
#define _DUSB 1


// Define whether we should do a formatting of SPIFFS when starting the gateway
// This is usually a good idea if the webserver is interrupted halfway a writing
// operation. Also to be used when software is upgraded
// Normally, value 0 is a good default.
#define _SPIFF_FORMAT 0


// Define the frequency band the gateway will listen on. Valid options are
// EU863_870 (Europe), US902_928 (North America) & AU925_928 (Australia), CN470_510 (China).
// See https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html
#define EU863_870 1
 
 
// Define whether to use the old Semtech gateway API, which is still supported by TTN,
// but is more lightweight than the new TTN tcp based protocol.
// NOTE: Only one of the two should be defined! TTN Router project has stopped
//
#define _UDPROUTER 1
//#define _TTNROUTER 1


// The spreading factor is the most important parameter to set for a single channel
// gateway. It specifies the speed/datarate in which the gateway and node communicate.
// As the name says, in principle the single channel gateway listens to one channel/frequency
// and to one spreading factor only.
// This parameters contains the default value of SF, the actual version can be set with
// the webserver and it will be stored in SPIFF
// NOTE: The frequency is set in the loraModem.h file and is default 868.100000 MHz.
#define _SPREADING SF9


// Channel Activity Detection
// This function will scan for valid LoRa headers and determine the Spreading 
// factor accordingly. If set to 1 we will use this function which means the 
// 1-channel gateway will become even more versatile. If set to 0 we will use the
// continuous listen mode.
// Using this function means that we HAVE to use more dio pins on the RFM95/sx1276
// device and also connect enable dio1 to detect this state. 
#define _CAD 1


// Definitions for the admin webserver.
// A_SERVER determines whether or not the admin webpage is included in the sketch.
// Normally, leave it in!
#define A_SERVER 1				// Define local WebServer only if this define is set
#define A_REFRESH 1				// Allow the webserver refresh or not?
#define A_SERVERPORT 80			// Local webserver port (normally 80)
#define A_MAXBUFSIZE 192		// Must be larger than 128, but small enough to work


// Definitions for over the air updates. At the moment we support OTA with IDE
// Make sure that tou have installed Python version 2.7 and have Bonjour in your network.
// Bonjour is included in iTunes (which is free) and OTA is recommended to install 
// the firmware on your router witout having to be really close to the gateway and 
// connect with USB.
#define A_OTA 1


// We support a few pin-out configurations out-of-the-box: HALLARD, COMPRESULT and TTGO ESP32.
// If you use one of these two, just set the parameter to the right value.
// If your pin definitions are different, update the loraModem.h file to reflect these settings.
//	1: HALLARD
//	2: COMRESULT pin out
//	3: ESP32 Wemos pin out
//	4: ESP32 TTGO pinning (should work for 433 and OLED too).
//	5: ESP32 TTGO EU433 MHz with OLED
//	6: Other, define your own in loraModem.h
#define _PIN_OUT 5

// Gather statistics on sensor and Wifi status
// 0= No statistics
// 1= Keep track of messages statistics, number determined by MAX_STAT
// 2= Option 1 + Keep track of messages received PER each SF (default)
// 3= See Option 2, but with extra channel info (Do not use when no Hopping is selected)
#define _STATISTICS 3


// Maximum number of statistics records gathered. 20 is a good maximum (memory intensive)
// For ESP32 maybe 30 could be used as well
#define MAX_STAT 20


// Single channel gateways if they behave strict should only use one frequency 
// channel and one spreading factor. However, the TTN backend replies on RX2 
// timeslot for spreading factors SF9-SF12. 
// Also, the server will respond with SF12 in the RX2 timeslot.
// If the 1ch gateway is working in and for nodes that ONLY transmit and receive on the set
// and agreed frequency and spreading factor. make sure to set STRICT to 1.
// In this case, the frequency and spreading factor for downlink messages is adapted by this
// gateway
// NOTE: If your node has only one frequency enabled and one SF, you must set this to 1
//		in order to receive downlink messages
// NOTE: In all other cases, value 0 works for most gateways with CAD enabled
#define _STRICT_1CH 1


// Allows configuration through WifiManager AP setup. Must be 0 or 1					
#define _WIFIMANAGER 0


// Define the name of the accesspoint if the gateway is in accesspoint mode (is
// getting WiFi SSID and password using WiFiManager)
#define AP_NAME "ESP8266-Gway-Things4U"
#define AP_PASSWD "ttnAutoPw"


// This section defines whether we use the gateway as a repeater
// For his, we use another output channle as the channel (default==0) we are 
// receiving the messages on.
#define _REPEATER 0


// Will we use Mutex or not?
// +SPI is input for SPI, SPO is output for SPI
#define MUTEX 0


// Define if OLED Display is connected to I2C bus. Note that defining an OLED display does not
// impact performance very much, certainly if no OLED is connected. Wrong OLED will not show
// sensible results on display
// OLED==0; No OLED display connected
// OLED==1; 0.9 Oled Screen based on SSD1306
// OLED==2;	1"3 Oled screens for Wemos, 128x64 SH1106
#define OLED 1


// Define whether we want to manage the gateway over UDP (next to management 
// thru webinterface).
// This will allow us to send messages over the UDP connection to manage the gateway 
// and its parameters. Sometimes the gateway is not accesible from remote, 
// in this case we would allow it to use the SERVER UDP connection to receive 
// messages as well.
// NOTE: Be aware that these messages are NOT LoRa and NOT LoRa Gateway spec compliant.
//	However that should not interfere with regular gateway operation but instead offer 
//	functions to set/reset certain parameters from remote.
#define GATEWAYMGT 0


// Do extensive logging
// Use the ESP8266 SPIFS filesystem to do extensive logging.
// We must take care that the filesystem never(!) is full, and for that purpose we
// rather have new records/line of statistics than very old.
// Of course we must store enough records to make the filesystem work
#define STAT_LOG 1

// We will log a list of LoRa nodes that was forwarded using this gateway.
// For eacht node we record:
//	- node Number, or known node name
//	- Last seen 'seconds since 1/1/1970'
//	- SF seen (8-bit integer with SF per bit)
// The initial version _NUMMAX stores max so many nodes:
#define _SEENMAX 100
#define _SEENFILE "/gwayNum.txt"

// Name of he configfile in SPIFFs	filesystem
// In this file we store the configuration and other relevant info that should
// survive a reboot of the gateway		
#define CONFIGFILE "/gwayConfig.txt"

// Set the Server Settings (IMPORTANT)
#define _LOCUDPPORT 1700					// UDP port of gateway! Often 1700 or 1701 is used for upstream comms

// Timing
#define _MSG_INTERVAL 15					// Reset timer in seconds
#define _PULL_INTERVAL 55					// PULL_DATA messages to server to get downstream in milliseconds
#define _STAT_INTERVAL 120					// Send a 'stat' message to server
#define _NTP_INTERVAL 3600					// How often do we want time NTP synchronization
#define _WWW_INTERVAL	60					// Number of seconds before we refresh the WWW page


// MQTT definitions, these settings should be standard for TTN
// and need not changing
#define _TTNSERVER "router.eu.thethings.network"
#define _TTNPORT 1700						// Standard port for TTN


// If you have a second back-end server defined such as Semtech or loriot.io
// your can define _THINGPORT and _THINGSERVER with your own value.
// If not, make sure that you do not define these, which will save CPU time
// Port is UDP port in this program
//
// Default for testing: Switched off
#define _THINGSERVER "your,webserver.com"		// Server URL of the LoRa-udp.js handler
#define _THINGPORT 1700						// Port 1700 is old compatibility


// This defines whether or not we would use the gateway as 
// as sort of backend system which decodes
// 1: _LOCALSERVER is used
// 0: Do not use _LOCALSERVER 
#define _LOCALSERVER 1						// See server definitions for decodes


// Gateway Ident definitions
#define _DESCRIPTION "ESP Gateway"			// Name of the gateway
#define _EMAIL "your@mail.com"				// Owner
#define _PLATFORM "ESP8266"
#define _LAT 52.0
#define _LON 5.0
#define _ALT 1								// Altitude

// ntp
// Please add daylight saving time to NTP_TIMEZONES when desired
#define NTP_TIMESERVER "nl.pool.ntp.org"	// Country and region specific
#define NTP_TIMEZONES	1					// How far is our Timezone from UTC (excl daylight saving/summer time)
#define SECS_IN_HOUR	3600
#define NTP_INTR 0							// Do NTP processing with interrupts or in loop();


// lora sensor code definitions
// Defines whether the gateway will also report sensor/status value on MQTT
// after all, a gateway can be a node to the system as well. Some sensors like GPS can be
// sent to the backend as a parameter, some (like humidity for example) can only be sent
// as a regular sensor value.
// Set its LoRa address and key below in this file, See spec. para 4.3.2
#define GATEWAYNODE 0
#define _CHECK_MIC 0




// Define the correct radio type that you are using
#define CFG_sx1276_radio		
//#define CFG_sx1272_radio


// Serial Port speed
#define _BAUDRATE 115200					// Works for debug messages to serial momitor


// We can put the gateway in such a mode that it will (only) recognize
// nodes that are put in a list of trusted nodes 
// Values:
// 0: Do not use names for trusted Nodes
// 1: Use the nodes as a translation table for hex codes to names (in TLN)
// 2: Same as 1, but is nodes NOT in the nodes list below they are NOT
//		forwarded or counted! (not yet fully implemented)
#define _TRUSTED_NODES 1
#define _TRUSTED_DECODE 1




// For asserting and testing the following defines are used.
//
#if !defined(CFG_noassert)
#define ASSERT(cond) if(!(cond)) gway_failed(__FILE__, __LINE__)
#else
#define ASSERT(cond) /**/
#endif