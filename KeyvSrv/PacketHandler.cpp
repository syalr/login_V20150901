#include "PacketHandler.h"

#include "Handler_FromDBServer.h"
#include "Handler_FromLoginServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_LL = new FunctionMap;
	m_pFuncMap_LD = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_LL);
	SAFE_DELETE(m_pFuncMap_LD);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_LL();
	Register_LD();
	return TRUE;
}

void PacketHandler::Register_LL()
{	
	AddHandler_LL( Login_Protocol, PreLogin_REQ, Handler_FromLoginServer::OnPreLogin_REQ );	// 预登陆
}

void PacketHandler::Register_LD()
{
	AddHandler_LD( Login_Protocol, PreLogin_ANC, Handler_FromDBServer::OnPreLogin_ANC );
	AddHandler_LD( Login_Protocol, PreLogin_NAK, Handler_FromDBServer::OnPreLogin_NAK );
}

BOOL PacketHandler::AddHandler_LL( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_LL * pFuncInfo	= new FUNC_LL;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	//printf("category:%d,protocol:%d\n", category, protocol);	
	//printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
	
	return m_pFuncMap_LL->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_LD( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_LD * pFuncInfo	= new FUNC_LD;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_LD->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_LL( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert( NULL != pMsg );
	printf("PacketHandler::ParsePacket_LL \n");
	
	FUNC_LL * pFuncInfo = (FUNC_LL *)m_pFuncMap_LL->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	if ( pFuncInfo == NULL ) {
		printf("[PacketHandler::ParsePacket_LL] Error\n");
		return;
	}
	
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_LD( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert( NULL != pMsg );

	printf("PacketHandler::ParsePacket_LD \n");

	FUNC_LD * pFuncInfo = (FUNC_LD *)m_pFuncMap_LD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	if ( pFuncInfo == NULL ) {
		printf("[PacketHandler::ParsePacket_LD] Error\n");
		return;
	}
	
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}
