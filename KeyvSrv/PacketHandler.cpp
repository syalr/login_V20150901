#include "PacketHandler.h"

#include "Handler_FromDBServer.h"
#include "Handler_FromLoginServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_LK = new FunctionMap;
	m_pFuncMap_KD = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_LK);
	SAFE_DELETE(m_pFuncMap_KD);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_LK();
	Register_KD();
	return TRUE;
}

void PacketHandler::Register_LK()
{	
	AddHandler_LK( Login_Protocol, PreLogin_REQ, Handler_FromLoginServer::OnPreLogin_REQ );	// 预登陆
}

void PacketHandler::Register_KD()
{
	AddHandler_KD( Login_Protocol, PreLogin_ANC, Handler_FromDBServer::OnPreLogin_ANC );
	AddHandler_KD( Login_Protocol, PreLogin_NAK, Handler_FromDBServer::OnPreLogin_NAK );
}

BOOL PacketHandler::AddHandler_LK( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_LK * pFuncInfo	= new FUNC_LK;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return m_pFuncMap_LK->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_KD( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_KD * pFuncInfo	= new FUNC_KD;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return m_pFuncMap_KD->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_LK( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert( NULL != pMsg );
	FUNC_LK * pFuncInfo = (FUNC_LK *)m_pFuncMap_LK->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	if ( pFuncInfo == NULL ) {
		printf("[PacketHandler::ParsePacket_LK] Error\n");
		return;
	}
	
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );
}

VOID PacketHandler::ParsePacket_KD( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert( NULL != pMsg );
	FUNC_KD * pFuncInfo = (FUNC_KD *)m_pFuncMap_KD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	if ( pFuncInfo == NULL ) {
		printf("[PacketHandler::ParsePacket_KD] Error\n");
		return;
	}
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );}
