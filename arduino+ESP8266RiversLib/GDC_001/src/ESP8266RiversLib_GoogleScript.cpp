// ESP8266RiversLib_GoogleScript.cpp

#include "ESP8266RiversLib_GoogleScript.h"


/* Enable/disable debug */

void GoogleScript::enableDebug(void) {
	_dbg = true;
}
void GoogleScript::disableDebug(void) {
	_dbg = false;
}
//****************************************************************************//

/* Constructors */
GoogleScript::GoogleScript(String script_id, String host_domain, IPAddress host_ip, int host_port, String sha1_fingerprint) {
	_script_id = script_id;
	Init();
	_host_domain = host_domain;
	_host_ip = host_ip;
	_host_port = host_port;
	_sha1_fingerprint = sha1_fingerprint;
}

GoogleScript::GoogleScript(String script_id) {
	_script_id = script_id;
	Init();
}

GoogleScript::~GoogleScript() {}

void GoogleScript::Init(void) {

	// Internal information
	_client_httpsRedirect = nullptr;
	_allowInsecureConnection = false;
	_connection_attempts = 5;

	// Host information
	_host_domain = "script.google.com";
	_host_ip = IPAddress(172,217,11,14);
	_host_port = 443;
	_sha1_fingerprint = "09 B9 78 F9 84 34 DF 65 D9 92 CE BE B1 CC 95 41 77 CF 88 C4";

	// Debug mode enabled by default
	_dbg = true;
}
//****************************************************************************//


/* Establish connection */

// GoogleScript::send_parameters( GoogleScript_Parameter* p, int pN )
//
//	@argument p : pointer for an structure array type GoogleScript_Parameter
//
//	@argument pN : length of the p array
//
//	@description : main parameter sender routine
//
String GoogleScript::send_data(GoogleScript_Parameter *p, int pN) {

	if(_dbg) Serial.println("The process of sending data to Google has started");

	// Create client
	if(_dbg) Serial.println("   -> HTTPS redirectioning");
	_client_httpsRedirect = new HTTPSRedirect(_host_port);
	_client_httpsRedirect->setPrintResponseBody(false);
	_client_httpsRedirect->setContentTypeHeader("application/json");

	// Insecure connection? (TODO secure)
	char tmp[_sha1_fingerprint.length()+1];
	_sha1_fingerprint.toCharArray(tmp, _sha1_fingerprint.length() + 1);
	if ( !_client_httpsRedirect->setFingerprint(tmp) ) { // Certificate mis-match
		if(_dbg) Serial.println("      -> SHA1 fingerprint certificate mis-match");
		if (_allowInsecureConnection) { // If it's enabled go insecure
		if(_dbg) Serial.println("      -> WARNING: certificate mis-match has been ignored, going insecure");
			_client_httpsRedirect->setInsecure();
		} else {
			if(_dbg) Serial.println("      -> Certificate mis-match, request hasn't been sent");
			if(_dbg) Serial.println("      -> Exiting");
			return "";
		}
	}

	// Try to reach to the server
	if(_dbg) Serial.print("      -> Connecting to server");
	bool connected = false;
	for ( int i = 0 ; i < _connection_attempts ; i++ ) {
		if ( _client_httpsRedirect->connect(_host_ip, _host_port) ) {
			connected = true;
			break;
		}
		if(_dbg) Serial.print(".");
	}
	if(_dbg) Serial.println("");
	if (!connected) {
		if(_dbg) Serial.println("      -> Server unreachable, increase the number of attempts or check your");
		if(_dbg) Serial.println("         connection");
		if(_dbg) Serial.println("      -> Exiting...");
		return "";
	}

	// Construct the URL request
	String url = "/macros/s/" + _script_id + "/exec?";
	for ( int i = 0 ; i < pN ; i++ ) {
		url += p[i].parameter + "=" + p[i].value + "&";
	}
	//url = url.substr(0, url.size()-1); // delete the last &


	// Send actual data
	char tmp2[_host_domain.length()+1];
	_host_domain.toCharArray(tmp2, _host_domain.length() + 1);
	if(_dbg) Serial.println("      -> Data sent to the server");
	_client_httpsRedirect->GET(url, tmp2);

	// Get response
	if(_dbg) Serial.println("      -> Waiting for response from the server");
	String response = _client_httpsRedirect->getResponseBody();

	// Close connection
	if(_dbg) Serial.println("      -> Response received");
	if(_dbg) Serial.println("      -> Exiting...");
	delete _client_httpsRedirect; _client_httpsRedirect = nullptr;

	// Return response
	return response;

}
//****************************************************************************//
