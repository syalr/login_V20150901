#include "LoginServerSession.h"
#include "PacketHandler.h"
#include <Public.h>
#include "JsonPreLogin.h"

LoginServerSession::LoginServerSession()
{
	m_userCount = 0;
}

LoginServerSession::~LoginServerSession()
{
}

void LoginServerSession::Init()
{
	ServerSession::Init();
}

void LoginServerSession::Release()
{
	ServerSession::Release();
}

void LoginServerSession::Update()
{
	ServerSession::Update();
}

void LoginServerSession::OnRecv(BYTE * pMsg, WORD wSize)
{
	printf("[LoginServerSession::OnRecv]\n");
	
	char json_msgs[1024] = {0};
	MSG_BASE_FORWARD bMsg; 
	memcpy(json_msgs, pMsg + sizeof(bMsg), wSize - sizeof(bMsg)); 
	
	JsonParser js_pid;
	js_pid.ParseJson(json_msgs);
	
	MSG_PRELOGIN_REQ x;
	DWORD pid = js_pid.GetProtocol();
	
	printf("[LoginServerSession::OnRecv pid = %d] \n ", pid);
	if (pid != 0) 
	{
		memcpy( pMsg, &pid, sizeof(pid) );
		
		g_PacketHandler.ParsePacket_LJ( 
				(ServerSession*)this, 
				(MSG_BASE*) pMsg, 
				wSize);
	}
}

void LoginServerSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	printf("[LoginServer]: LoginServerSession::OnConnect\n");
	ServerSession::OnConnect( bSuccess, dwNetworkIndex );
	if ( bSuccess ) {
		printf("[LoginServerSession::OnConnect] success.\n");
		printf("Send Server Type.\n");
		ServerSession::SendServerType();
	}
	else {
		printf("[LoginServer]: LoginServerSession::OnConnect Fail\n");
	}
}

void LoginServerSession::OnDisconnect()
{
	printf("[LoginServerSession::OnDisconnect]\n");
	ServerSession::OnDisconnect();
}
	
void LoginServerSession::OnLogString( char * pszLog)
{
	
}
