#include "LoginServer.h"

NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

NetworkObject * CreateClientSideAcceptedObject();
VOID DestroyClientSideAcceptedObject( NetworkObject * pNetworkObject );
VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject );

LoginServer * g_pLoginServer = NULL;

LoginServer::LoginServer(void)
{
	m_bShutdown		= FALSE;
	m_pIOCPServer 	= NULL;
	
	// Keyv Server
	m_pKeyvServer   = NULL;
	
	// UserKey
	memset( m_pUserSession, 0x0, PORT_MAX);
	
	// Overtime Table
	m_lsOvertimeTable.clear();
}

LoginServer::~LoginServer(void)
{
	if ( m_pIOCPServer ) {
		delete m_pIOCPServer;
	}
}

BOOL LoginServer::Init()
{
	//m_lsOvertimeTable.reserve(999);
	
	LoginFactory::Instance()->Init();
	
	m_pIOCPServer = new IOCPServer;
	
	SYNCHANDLER_DESC desc[2];
	
	desc[0].dwSyncHandlerKey			= SERVER_SYNCHANDLER;
	desc[0].dwMaxAcceptSession			= 9;
	desc[0].dwMaxConnectSession			= 9;
	desc[0].dwSendBufferSize			= 2000000;
	desc[0].dwRecvBufferSize		 	= 2000000;
	desc[0].dwTimeOut					= 0;
	desc[0].dwNumberOfAcceptThreads		= 1; // Accept
	desc[0].dwNumberOfIoThreads			= 8;
	desc[0].dwNumberOfConnectThreads	= 0; // Login Server don't Active connect.
	desc[0].dwMaxPacketSize				= 60000; //4096
	desc[0].fnCreateAcceptedObject		= CreateServerSideAcceptedObject;
	desc[0].fnDestroyAcceptedObject		= DestroyServerSideAcceptedObject;
	desc[0].fnDestroyConnectedObject	= DestroyServerSideConnectedObject;

	desc[1].dwSyncHandlerKey 			= CLIENT_SYNCHANDLER;
	desc[1].dwMaxAcceptSession			= 700;
	desc[1].dwMaxConnectSession			= 0;
	desc[1].dwSendBufferSize			= 1024 * 60; //60000
	desc[1].dwRecvBufferSize			= 1024 * 60; //60000
	desc[1].dwTimeOut					= 0;
	desc[1].dwNumberOfAcceptThreads		= 1; // Accept
	desc[1].dwNumberOfIoThreads			= 8;
	desc[1].dwNumberOfConnectThreads	= 0; // Connect
	desc[1].dwMaxPacketSize				= 1024 * 10;	//4096
	desc[1].fnCreateAcceptedObject		= CreateClientSideAcceptedObject;
	desc[1].fnDestroyAcceptedObject		= DestroyClientSideAcceptedObject;
	desc[1].fnDestroyConnectedObject	= DestroyClientSideConnectedObject;

	if ( !m_pIOCPServer->Init(desc, 2) ) {
		return FALSE;
	}
	
	//g_UserManager.InitUserSize( MAX_PLAYER_NUM ); // 1000
	
	StartServerSideListen();
	StartClientSideListen();
	
	m_pKeyvServer = LoginFactory::Instance()->AllocKeyvSession();
	if ( m_pKeyvServer == NULL) {
		printf("[LoginFactory::Instance()->AllocLineServerSession] fail\n");
		return FALSE;
	}
	
	return TRUE;	
}

void LoginServer::StartServerSideListen() 
{
	if( !m_pIOCPServer->IsListening( SERVER_SYNCHANDLER) )
	{
		if ( !m_pIOCPServer->StartListen(SERVER_SYNCHANDLER, "127.0.0.1", 7010) ) // Login Port 7010
		{
			return;
		}
	}
}

void LoginServer::StartClientSideListen()
{
	if ( !m_pIOCPServer->IsListening( CLIENT_SYNCHANDLER) ) 
	{
		if ( !m_pIOCPServer->StartListen(CLIENT_SYNCHANDLER, "", 1234) ) // Clinet Port 1234
		{
			return;
		}
	}
}

BOOL LoginServer::MaintainConnection()
{
	if ( m_bShutdown ) {
		return TRUE;
	}
}

BOOL LoginServer::Update( DWORD dwDeltaTick )
{
	if(m_pIOCPServer)
	{
		m_pIOCPServer->Update();
	}

	//MaintainConnection();
	WORD wIndex = 0;
	
	for (int i = 0; i< m_lsOvertimeTable.size(); ++i)
	{
		wIndex = m_lsOvertimeTable.front();
		if ( m_pUserSession[wIndex] )
		{
			if ( m_pUserSession[wIndex]->Update( dwDeltaTick ) )
			{
				m_pUserSession[wIndex]->Release();
				m_lsOvertimeTable.pop_front();
			}
		}
	}
	return TRUE;
}

BOOL LoginServer::SendToAllServer( BYTE * pMsg, WORD wSize)
{
	printf("[LoginServer::SendToLineServer]\n");
	
	if ( m_pKeyvServer ) {
		return m_pKeyvServer->Send( pMsg, wSize );
	}
	return FALSE;
}

ServerSession * LoginServer::GetKeyvSession() const
{
	return m_pKeyvServer;
}

// User Server;
BOOL LoginServer::SendToUserServer( BYTE * pMsg, WORD wSize )
{
	MSG_BASE_FORWARD * pBase = (MSG_BASE_FORWARD *) pMsg;
	
	WORD wIndex = pBase->m_wParameter;
	if ( wIndex == 0 ) {
		return FALSE;	
	}
	
	UserSession * pSession = m_pUserSession[wIndex];
	if ( pSession != NULL ) {
		WORD sendSize =  wSize - sizeof(MSG_BASE_FORWARD);
		BYTE * sendMsg = (BYTE *) ( pBase + sizeof(MSG_BASE_FORWARD) );
		pSession->Send(sendMsg, sendSize);
	}
}

BOOL LoginServer::SetUserSession(WORD wIndex, UserSession * pSession)
{
	if ( wIndex == 0 ) {
		return FALSE;
	}
	
	m_pUserSession[wIndex] = pSession;
	return TRUE;
}

///////////////////////////////////////////////////////////////
// 服务器端
NetworkObject * CreateServerSideAcceptedObject()
{
	printf("[LoginServer::CreateServerSideAcceptedObject]: Alloc TempServerSession.\n");
	TempServerSession * obj = LoginFactory::Instance()->AllocTempServerSession();
	if ( obj == NULL) {
		printf("\nLoginFactory::Instance()->AllocTempServerSession() Fail.\n");
		return NULL;
	}
	return (NetworkObject *)(obj);
}

VOID DestroyServerSideAcceptedObject( NetworkObject *pObjs )
{	
	printf("[LoginServer::DestroyServerSideAcceptedObject] Function\n");
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject )
{
	printf("[LoginServer::DestroyServerSideConnectedObject]: Not Used.\n");
}

// 客户端
NetworkObject * CreateClientSideAcceptedObject() {
	printf("[LoginServer::CreateClientSideAcceptedObject]: Alloc TempUserSession.\n");
	
	UserSession * obj = LoginFactory::Instance()->AllocUserSession();
	if ( obj == NULL) {
		printf("\nLoginFactory::Instance()->AllocTempUserSession() Fail.\n");
		return NULL;
	}
	
	WORD PortKey = obj->GetPort();
	if ( !g_pLoginServer->SetUserSession(PortKey, obj) )
	{
		LoginFactory::Instance()->FreeUserSession( obj );
		return NULL;
	}
	
	return (NetworkObject *)(obj);
}

VOID DestroyClientSideAcceptedObject( NetworkObject * pObjs ) {
	printf("[LoginServer::DestroyClientSideAcceptedObject]: Function\n");
	UserSession * pSession = (UserSession *)pObjs;
	pSession->Release();
}

VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject ) {
	printf("[LoginServer::DestroyClientSideConnectedObject]: Not Used.\n");
}
