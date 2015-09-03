#ifndef _JSON_PRELOGINANC_H_INCLUDED_
#define _JSON_PRELOGINANC_H_INCLUDED_

class Json_PreLoginANC
{
	enum
	{
		eUNKNOWN 		= 0x01,
		eUSERID			= 0x02,
		eUSERNAME 		= 0x04,
		ePASSWORD 		= 0x08,
		eSSHKEY 		= 0x0F,
		eGAMEID 		= 0x10,
		ePROTOCOL 		= 0x20,
	};

public:

	Json_PreLoginANC();
	~Json_PreLoginANC();

	void SetMsg(MSG_PRELOGIN_ANC * pMsg); 
	WORD GetJson(char * szJson, WORD wSize );
	
private:
	MSG_PRELOGIN_ANC msg;
};



#endif // _JSON_STRING_H_INCLUDED_