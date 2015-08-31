#include "TempServerSession.h"
#include "DBServer.h"

TempServerSession::TempServerSession()
{
	m_bFirst = TRUE;
}

TempServerSession::~TempServerSession()
{
	
}

void TempServerSession::Clear()
{
	m_bFirst = TRUE;
	ServerSession::Clear();
}

void TempServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	assert( m_bFirst == TRUE);
	m_bFirst = FALSE;
	
	printf("Enter TempServerSession::OnRecv.\n");
	
	MSG_SERVER_TYPE * pRecvMsg = (MSG_SERVER_TYPE *)pMsg;
	if ( pRecvMsg->m_byServerType == LINE_SERVER ) 
	{
		printf("2.Turn to Game_SERVER\n");
		ServerSession * Obj = g_DBServer->GetLineServerSession();
		if ( Obj == NULL) {
			printf("\ng_DBServer->GetGameServerSession Fail.\n");
			return;
		}
		
		Session * pSession = this->m_pSession;
		if ( pSession != NULL ) {
			m_pSession->UnbindNetworkObject();
			pSession->BindNetworkObject(Obj);
		}
	}

	printf("\n >>>> Free TempServerSesion <<<< \n");
	DBFactory::Instance()->FreeTempServerSession(this);

}

void TempServerSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{

}

void TempServerSession::OnLogString( char * pszLog)
{
	
}
