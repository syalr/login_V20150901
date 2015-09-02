#ifndef _JSON_PRELOGIN_H_INCLUDED_
#define _JSON_PRELOGIN_H_INCLUDED_

class JsonPreLogin
{
	enum
	{
		eUNKNOWN 		= 0x01,
		eACCESSID		= 0x02,
		eUSERNAME 		= 0x04,
		ePASSWORD 		= 0x08,
		eSSHKEY 		= 0x0F,
		eGAMEID 		= 0x10,
		ePROTOCOL 		= 0x20,
	};

public:

	JsonPreLogin();
	~JsonPreLogin();

	int ParseJson( const char * pInput );
	
	MSG_PRELOGIN_REQ * GetMsg(MSG_PRELOGIN_REQ * pMsg); 
	
private:

	MSG_PRELOGIN_REQ msg;
	
	// ...
	DWORD   dwStatus;
};



#endif // _JSON_STRING_H_INCLUDED_