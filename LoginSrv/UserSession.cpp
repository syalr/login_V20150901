#include "UserSession.h"
#include "LoginServer.h"
#include "LoginFactory.h"

UserSession::UserSession()
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
	m_wUserKey = 0;
	m_byHasRecv   = 0;
}

void UserSession::Release()
{
	m_eUserType = UT_TEMP_USER;
	
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
	// Connected warning.
	if (this->m_byHasRecv == 0) 
	{
		switch( m_eUserType )
		{
		case UT_KEYV_USER:
			{
				g_pLoginServer->SendToKeyvServer(pMsg, wSize);
				break;
			}
		default:
			{
				// Connected warning.
				this->Release();
				
				break;
			}
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
