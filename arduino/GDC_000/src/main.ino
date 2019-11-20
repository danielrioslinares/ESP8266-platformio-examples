// main.ino

#include "main.h"


// Wi-Fi access
const char* ssid = ""; // ADD YOUR ACTUAL SSID
const char* password = ""; // ADD YOUR ACTUAL PASSWORD

// Google Drive access
const IPAddress host_ip = IPAddress(172,217,11,14); // BUG if you use the other method with host_url it crashes randomly
const char* host_url = "script.google.com";
const int port = 443;
String script_google_id = ""; // ADD YOUR ACTUAL Google ID

// Security SHA1 fingerprint obtained from POSIX with the following command:
// openssl s_client -connect script.google.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout -in /dev/stdin | sed 's/:/ /g')
const char* sha1_fingerprint = "09 B9 78 F9 84 34 DF 65 D9 92 CE BE B1 CC 95 41 77 CF 88 C4";

// WiFiClientSecure (TLS connection)
WiFiClientSecure client;


// setup()
//
//  @description : program entry point
//
void setup() {

	/* Set insecure because the fingerprint is denied by Google :( */
	client.setInsecure(); //client.setFingerprint(sha1_fingerprint);

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

}
//****************************************************************************//


// send_data( kv, lenght(kv) )
//
//  @description : actual program loop
//
bool send_data(KeyPair *key_vals, int N) {

	// Host connection
	Serial.print("Connecting to host "); Serial.println(host_url);

	if (!client.connect(host_ip, port)) {
	  	Serial.println("   -> Connection failed");
	    Serial.println("   -> Exiting...");
		return false;
	}

	// URL request
	String url = "/macros/s/" + script_google_id + "/exec?";

	Serial.println("   -> Requesting URL...");
	Serial.println("   -> + Fetching the following data");

	for ( int i = 0 ; i < N - 1 ; i++ ) {
  	Serial.print("      | "); Serial.print(key_vals[i].key); Serial.print(" = "); Serial.print(key_vals[i].val); Serial.println("");
    	url += key_vals[i].key + "=" + key_vals[i].val + "&";
	}
	Serial.print("      | "); Serial.print(key_vals[N-1].key); Serial.print(" = "); Serial.print(key_vals[N-1].val); Serial.println("");
	url += key_vals[N-1].key + "=" + key_vals[N-1].val;

	// Send data
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
		"Host: " + host_url + "\r\n" +
		"User-Agent: BuildFailureDetectorESP8266\r\n" +
  		"Connection: close\r\n\r\n");

	// Close connection
	Serial.println("   -> Request sent");
	Serial.println("   -> Exiting...");
	client.stop();

}
//****************************************************************************//


// loop()
//
//  @description : actual program loop
//
void loop() {

	KeyPair key_vals[4] = {
		{"variableOne","100"},
		{"variableTwo","200"},
		{"variableThr","300"},
		{"variableFou","400"}
	};

	send_data(key_vals, 4);

	delay(5000);
}
//****************************************************************************//
