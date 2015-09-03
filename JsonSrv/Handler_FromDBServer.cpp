#include "Handler_FromDBServer.h"
#include "JsonServer.h"
#include "MsgBuff.h"
#include "Json_PreLoginANC.h"

Handler_FromDBServer::Handler_FromDBServer() 
{
	
}

Handler_FromDBServer::~Handler_FromDBServer() 
{
	
}

HANDLER_IMPL( PreLogin_ANC )
{
	printf(">> PreLogin_ANC\n");
	
	// MSG_LD_LOGIN_ANC * pRecvMsg = (MSG_LD_LOGIN_ANC *) pMsg;
	Json_PreLoginANC js_prologin;
	js_prologin.SetMsg( ( MSG_PRELOGIN_ANC* )pMsg );
	
	DWORD dwlen = 0;
	char cBuff[256] = {0};
	dwlen = js_prologin.GetJson(cBuff, 256);
	if ( dwlen != 0 ) {
		
		MSG_BASE_FORWARD sendLogin;
		memcpy( &sendLogin, pMsg, sizeof(sendLogin) );
		
		BYTE byBuff[1024] = {0};
		CMsgBuff msgbuff( byBuff, 1024 );
		msgbuff.Write( &sendLogin, sizeof(sendLogin) );
		msgbuff.Write( cBuff, dwlen);
		dwlen = msgbuff.GetWriteLen();
		g_pJsonServer->SendToLoginServer( (BYTE*)&sendLogin, dwlen );
	}
}


HANDLER_IMPL( PreLogin_NAK )
{
	printf(">> PreLogin_NAK\n");
	
	
}
