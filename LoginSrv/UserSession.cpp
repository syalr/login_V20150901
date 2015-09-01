#include "UserSession.h"
#include "LoginServer.h"
#include "LoginFactory.h"

UserSession::UserSession()
: m_bFirst(TRUE)
{	
	m_eUserType = UT_TEMP_USER;
}

UserSession::~UserSession()
{
}

BOOL UserSession::SendPacket(BYTE *pMsg, WORD wSize)
{
	return Send( (BYTE *)pMsg, wSize );
}

WORD UserSession::GetUserKey() const
{
	return m_wUserKey;
}

void  UserSession::SetUserKey(WORD dwKey)
{
	m_wUserKey = dwKey;
}


/************ protected *************/
void UserSession::Init()
{
	m_wUserKey 		= 0;
	m_byHasRecv   	= 0;
	m_bFirst 		= TRUE;
	m_dwOvertime    = 0;
}

BOOL UserSession::Update( DWORD dwDeltaTick )
{
	if ( m_dwOvertime > dwDeltaTick ) {
		m_dwOvertime -= dwDeltaTick;
		return TRUE;
	}
	return FALSE;
}

void UserSession::Release()
{
	m_bFirst = TRUE;
	
	m_byHasRecv = 0;
	
	// 释放连接
	this->OnDisconnect();
	
	// 释放服务器
	LoginFactory::Instance()->FreeUserSession(this);
	
	g_pLoginServer->SetUserSession( this->m_wUserKey, NULL); 
}

void UserSession::OnAccept( DWORD dwNetworkIndex )
{

}

void UserSession::OnDisconnect()
{
	NetworkObject::OnDisconnect();
}

void UserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf(">>>> [TempUserSession::OnRecv]\n");
	
	// Connected warning.
	if ( m_bFirst == FALSE ) {
		this->Release();
		return;
	}
	
	// Connected warning.
	BYTE msgPlus[1024] = {0};
	
	if ( this->m_byHasRecv == 0 ) 
	{
		m_bFirst = FALSE;
		
		// Alloc Port 
		WORD PortKey = this->GetPort();
		if ( PortKey != 0 )
		{
			MSG_ENTERSERVER_SYN * recvMsg = (MSG_ENTERSERVER_SYN *)pMsg;
			
			if ( wSize < (sizeof(MSG_BASE) + 1) ) {
				this->Release();
				return;
			}
			
			memcpy(msgPlus, &m_wUserKey, sizeof(m_wUserKey));
			memcpy(msgPlus + sizeof(m_wUserKey), pMsg, wSize);
			g_pLoginServer->SendToAllServer(msgPlus, wSize + sizeof(m_wUserKey));
		}
	}
	
	// Connected warning.
	if ( this->m_byHasRecv > REQUEST_SAFETY ) {
		this->Release();
		return;
	}
	
	this->m_byHasRecv++;
}

void UserSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	
}

void UserSession::OnLogString( char * pszLog)
{
	
}
