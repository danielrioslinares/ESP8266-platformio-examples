// src/main.h

/* Libraries */

// Wi-Fi access
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "HTTPSRedirect.h"
#include "DebugMacros.h"

/* Definitions */

// Key-Value structure
typedef struct {
    String key;
    String val;
}KeyPair;
