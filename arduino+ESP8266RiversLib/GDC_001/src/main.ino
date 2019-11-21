// main.ino

#include "main.h"


// Wi-Fi access
WiFiStation_Parameter station = {"Livebox-64E3", "FVs4eP2K"}; // ADD YOUR ACTUAL SSID & PASSWORD

// Google script handler
GoogleScript google_script_client = GoogleScript("AKfycbz7iP3cAibGrDE1wnrOLAxVIsxtLqwYAPvGNY5w6ZGYRcU3E7Kq"); // ADD YOUR ACTUAL Google script ID

// setup()
//
//  @description : program entry point
//
void setup() {

	/* Serial connection */
	Serial.begin(115200); Serial.flush(); Serial.println("");

	/* Wi-Fi connection */
	connect_to_WiFi(station);

}
//****************************************************************************//


// loop()
//
//  @description : actual program loop
//
void loop() {

	GoogleScript_Parameter parameters[4] = {
		{"variableOne", "14321"},
		{"variableTwo", "132511"},
		{"variableThr", "13231"},
		{"variableFou", "11321"}
	};

	google_script_client.send_data(parameters, 4);

	delay(5000);
}
//****************************************************************************//
