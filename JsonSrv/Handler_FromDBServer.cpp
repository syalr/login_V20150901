#include "Handler_FromDBServer.h"


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
	
}


HANDLER_IMPL( PreLogin_NAK )
{
	printf(">> PreLogin_NAK\n");
}
