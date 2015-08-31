#include "LoginServerSession.h"

#include "PacketHandler.h"

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

void LoginServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[LoginServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_AL function.\n");
	//g_PacketHandler.ParsePacket_AL( this, (MSG_BASE *)pMsg, wSize);
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
	else
		printf("[LoginServer]: LoginServerSession::OnConnect Fail\n");
}

void LoginServerSession::OnDisconnect()
{
	printf("[LoginServerSession::OnDisconnect]\n");
	ServerSession::OnDisconnect();
}
	
void LoginServerSession::OnLogString( char * pszLog)
{
	
}

// @{ Save its after Login; }
/*
void LoginServerSession::AddUser(LoginUser * pNewUser)
{
	LoginUser * pUser = m_hashUser->GetData( pNewUser->GetHashKey() );
	
	assert( !pUser );
	
	m_hashUser->Add(pNewUser, pNewUser->GetHashKey() );
}

LoginUser * LoginServerSession::FindUser(DWORD dwKey)
{
	return m_hashUser->GetData( dwKey );
}

void LoginServerSession::RemoveUser(DWORD dwKey)
{
	LoginUser * pUser = m_hashUser->GetData( dwKey );
	if ( pUser ) 
	{
		m_hashUser->Remove( dwKey );
	}
}
*/