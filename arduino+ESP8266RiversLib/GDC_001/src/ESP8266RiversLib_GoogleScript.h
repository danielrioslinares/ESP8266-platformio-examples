// ESP8266RiversLib_GoogleScript.h

#pragma once
#include "HTTPSRedirect.h"
#include "DebugMacros.h"

/* Structures */
typedef struct {
    String parameter;
    String value;
} GoogleScript_Parameter;
//****************************************************************************//


/* Class definition */
class GoogleScript {

	/* Private */
	private:

		// Debug mode enabled
		bool _dbg;

		// HTTPS TLS connection (redirect)
		HTTPSRedirect* _client_httpsRedirect;
		bool _allowInsecureConnection;

		// General connection settings
		String _script_id;
		String _fingerprint;
		String _host_domain;
		IPAddress _host_ip;
		int _host_port;
		String _sha1_fingerprint;
		int _connection_attempts;

		// Private methods
		void Init(void);

	public:
		/* Enable/disable debug */
		void disableDebug(void);
		void enableDebug(void);

		/* Constructors */
		~GoogleScript();
		GoogleScript(String);
		GoogleScript(String, String, IPAddress, int, String);

		/* Establish connection */
		String send_data(GoogleScript_Parameter*, int);

};
//****************************************************************************//
