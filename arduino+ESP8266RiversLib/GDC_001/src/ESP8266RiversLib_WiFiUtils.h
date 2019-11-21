// ESP8266RiversLib_WiFiUtils.h

#pragma once
#include <ESP8266WiFi.h>

/* Structures */
typedef struct {
    String ssid;
    String password;
} WiFiStation_Parameter;
//****************************************************************************//

/* Functions */
bool connect_to_WiFi(WiFiStation_Parameter);
bool connect_to_WiFi(WiFiStation_Parameter, bool);
//****************************************************************************//
