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
	BOOL SendToAllServer( BYTE * pMsg, WORD wSize);
	ServerSession * GetKeyvSession() const;
	
	// User Server;
	BOOL SendToClient( BYTE * pMsg, WORD wSize );
	BOOL SetUserSession( WORD wIndex, UserSession * pSession );
	BOOL OvertimeClear( DWORD dwDeltaTick );
	
private:
	BOOL m_bShutdown;
	
	// Main Server;
	IOCPServer *m_pIOCPServer;

	// Keyv Server;
	ServerSession *m_pKeyvServer;
	
	// UserKey = Key;  maxsize = 0xFFFF+1;
	UserSession * m_pUserSession[PORT_MAX + 1];
	
	// Overtime Process;
	DWORD m_dwMaxOvertime;
	std::list<WORD> m_lsOvertimeTable;
};

extern LoginServer * g_pLoginServer;

#endif // _AGENTSERVER_H_INCLUDED_
