// ESP8266RiversLib_WiFiUtils.cpp

#include "ESP8266RiversLib_WiFiUtils.h"


/* Functions */

// connect_to_WiFi( WiFiStation_Parameter station, bool dbg )
//
//  @description : connects to WiFi creating the characteristical debug
//		information of ESP8266RiversLib
//
bool connect_to_WiFi(WiFiStation_Parameter station, bool dbg) {

	// Get SSID and password
	String ssid = station.ssid;
	String password = station.password;

	// Connect
	if(dbg) Serial.print("Connecting to Wi-Fi station "); Serial.print(ssid);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
	  	delay(500);
	   	if(dbg) Serial.print(".");
	}
	if(dbg) Serial.println("");
	if(dbg) Serial.print("   -> Successfully connected! IP address: ");
	if(dbg) Serial.println(WiFi.localIP());
}


// connect_to_WiFi( WiFiStation_Parameter station )
//
//  @description : connects to WiFi creating the characteristical debug
//		information of ESP8266RiversLib, debug enabled by default
//
bool connect_to_WiFi(WiFiStation_Parameter station) {

	connect_to_WiFi(station, true);
}
//****************************************************************************//
