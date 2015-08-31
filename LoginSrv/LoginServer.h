#ifndef _LOGINSERVER_H_INCLUDED_
#define _LOGINSERVER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "LoginFactory.h"

using namespace std;

class LoginServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	LoginServer(void);
	~LoginServer(void);
	
	BOOL Init();
	
	// Start Listen;
	void StartServerSideListen();
	void StartClientSideListen();
	
	BOOL MaintainConnection();
	BOOL Update( DWORD dwDeltaTick );
	
	// Keyv Server;
	BOOL SendToKeyvServer( BYTE * pMsg, WORD wSize);
	ServerSession * GetKeyvSession() const;
	
	// User Server;
	BOOL SendToUserServer( BYTE * pMsg, WORD wSize );
	BOOL SetUserSession(WORD wIndex, UserSession * pSession);
	
private:
	BOOL m_bShutdown;
	
	// Main Server;
	IOCPServer *m_pIOCPServer;

	// Keyv Server;
	ServerSession *m_pKeyvServer;
	
	// UserKey = Key;  maxsize = 0xFFFF+1;
	UserSession * m_pUserSession[PORT_MAX + 1];
};

extern LoginServer * g_pLoginServer;

#endif // _AGENTSERVER_H_INCLUDED_
