#include "TempUserSession.h"
#include "LoginServer.h"
#include "LoginFactory.h"

TempUserSession::TempUserSession()
	: m_bFirst(TRUE)
{	
}

TempUserSession::~TempUserSession()
{
}

void TempUserSession::Init()
{
	UserSession::Init();
	m_bFirst = TRUE;
}

void TempUserSession::Release()
{
	UserSession::Release();
	m_bFirst = TRUE;
}

void TempUserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf(">>>> [TempUserSession::OnRecv]\n");
	
	// Connected warning.
	if ( m_bFirst == FALSE ) {
		this->Release();
		return;
	}
	
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
		
		eUSER_TYPE _eType = UT_TEMP_USER; 
		switch( recvMsg->EnterType[0] )
		{
		case 'K':
			{
				_eType = UT_KEYV_USER;
				break;
			}
		default:
			{
				// Connected warning.
				this->Release();
				return;
			}
		}
		
		UserSession * Obj = LoginFactory::Instance()->AllocUserSession();
		if ( Obj != NULL ) {
			return;
		}
		
		Obj->SetUserType( _eType );
		Obj->SetUserKey( PortKey );
		
		if ( !g_pLoginServer->SetUserSession(PortKey, Obj) )
		{
			LoginFactory::Instance()->FreeUserSession(Obj);
			return;
		}
		
		Session * pSession = this->m_pSession;
		if ( pSession != NULL ) {
			LoginFactory::Instance()->FreeUserSession(Obj);
			return;
		}
					
		m_pSession->UnbindNetworkObject();
		pSession->BindNetworkObject(Obj);
	}
}

void TempUserSession::OnLogString( char * pszLog)
{
}
