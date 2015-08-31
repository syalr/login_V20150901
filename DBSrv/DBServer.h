#ifndef _AGENTSERVER_H_INCLUDED_
#define _AGENTSERVER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "DBFactory.h"
#include "DBConnectDir.h"

using namespace std;

class DBServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	DBServer(void);
	
	~DBServer(void);

	BOOL Init();
	
	void StartServerSideListen();
	
	BOOL MaintainConnection();
	
	BOOL Update( DWORD dwDeltaTick );
	
	BOOL SendToLineServer( BYTE * pMsg, WORD wSize);
	
	ServerSession * GetLineServerSession() const;
	
private:
	BOOL m_bShutdown;
	
	IOCPServer * m_pIOCPServer;
	
	ServerSession * m_pLineServer;
};

extern DBServer * g_DBServer;

#endif // _AGENTSERVER_H_INCLUDED_
