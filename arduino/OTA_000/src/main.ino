// main.ino

#include "main.h"


// Wi-Fi access
const char* ssid = ""; // ADD YOUR ACTUAL SSID
const char* password = ""; // ADD YOUR ACTUAL PASSWORD


// setup()
//
//	@description : program entry point
//
void setup() {

	/* Pin I/O mode */
	pinMode(2, OUTPUT);

	/* Serial connection */
	Serial.begin(115200);
	Serial.flush();
	Serial.println("");

	/* Wi-Fi connection */
	Serial.print("Connecting to Wi-Fi station "); Serial.print(ssid);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
	  	delay(500);
	    Serial.print(".");
	}
	Serial.println("");
	Serial.print("   -> Successfully connected! IP address: ");
	Serial.println(WiFi.localIP());

	/* OTA (Over-The_air) firmware update */

	// Port defaults to 8266
	ArduinoOTA.setPort(8266);

	// Hostname defaults to esp8266-[ChipID]
	ArduinoOTA.setHostname("IoT Arduino OTA");

	// MD5 "chocolate" password hash
	ArduinoOTA.setPasswordHash("c378985d629e99a4e86213db0cd5e70d");

	// DEBUG (header, body and footer)
	ArduinoOTA.onStart([]() {
		Serial.println("Firmware update started (via OTA)");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("   -> Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onEnd([]() {
		Serial.println("   -> Completed successfully!");
		Serial.println("Exiting...");
	});
	ArduinoOTA.onError([](ota_error_t e) {
		Serial.print("   -> Fatal error: ");
		switch (e) {
			case OTA_AUTH_ERROR:
				Serial.println("Authentication Failed!");
				break;
			case OTA_BEGIN_ERROR:
				Serial.println("Begin Failed!");
				break;
			case OTA_CONNECT_ERROR:
				Serial.println("Connection Failed!");
				break;
			case OTA_RECEIVE_ERROR:
				Serial.println("Reception Failed!");
				break;
			case OTA_END_ERROR:
				Serial.println("End Failed!");
				break;
		}
	});

	// Begin OTA service
	ArduinoOTA.begin();
	Serial.println("OTA ready!");
	Serial.println("   -> IP address: " + WiFi.localIP());

}
//****************************************************************************//


// loop()
//
//	@description : actual program loop
//
void loop() {

	ArduinoOTA.handle();
	digitalWrite(2, LOW);
	delay(1000);
	digitalWrite(2, HIGH);
	delay(1000);

}
//****************************************************************************//
