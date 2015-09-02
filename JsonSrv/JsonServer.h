#ifndef _KEYVSERVER_H_INCLUDED_
#define _KEYVSERVER_H_INCLUDED_

#include <Common.h>
#include <Utility.h>
#include <Network.h>
#include <Public.h>
#include "JsonFactory.h"

using namespace std;

class JsonServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	JsonServer(void);
	~JsonServer(void);
	
	// 初始化
	BOOL Init();
	
	// 连接
	BOOL ConnectToServer( ServerSession * pSession, char * pszIP, WORD wPort );
	
	// 连接其他服务器
	BOOL MaintainConnection();
	
	// 更新帧
	BOOL Update( DWORD dwDeltaTick );
	
	// 释放
	//void Release();
		
	// 释放	
	BOOL SendToLoginServer( BYTE * pMsg, WORD wSize );
	BOOL SendToDBServer( BYTE * pMsg, WORD wSize );
	
private:
	BOOL m_bShutdown;
	
	IOCPServer * m_pIOCPServer;
	
	// DB and Login
	ServerSession * m_pDBServerSession;
	ServerSession * m_pLoginServerSession;
};

extern JsonServer * g_pJsonServer;

#endif // _LINE_SERVER_H_INCLUDED_