﻿#include "Handler_FromLoginServer.h"
#include "JsonServer.h"
#include "Json_PreLoginREQ.h"

Handler_FromLoginServer::Handler_FromLoginServer() 
{
}

Handler_FromLoginServer::~Handler_FromLoginServer() 
{
}

HANDLER_IMPL( PreLogin_REQ )
{
	printf(">> Handler_FromLoginServer::PreLogin_REQ \n");
	printf(">> [ %s ] \n", pMsg );
	
	char json_msgs[1024] = {0};
	MSG_BASE_FORWARD bMsg; 
	memcpy(json_msgs, ((BYTE*)pMsg) + sizeof(bMsg), wSize - sizeof(bMsg));
	
	Json_PreLoginREQ js_prologin;
	js_prologin.ParseJson( ( char* ) json_msgs);
	
	MSG_PRELOGIN_REQ sendDB;
	if ( js_prologin.GetMsg(&sendDB) != NULL ) {
		g_pJsonServer->SendToDBServer( (BYTE*) &sendDB, sizeof(sendDB) );
	}
}
