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
	
#if 0	
	MSG_LD_LOGIN_ANC * pRecvMsg = (MSG_LD_LOGIN_ANC *) pMsg;

	// 分配用户,保存信息，下次正式登陆时需要对比(主要验证 m_byUserKey )
	LoginUser * pLoginUser = LoginFactory::Instance()->AllocLoginUser();
	
	if ( pLoginUser != NULL ) {
		AgentServerSession * pSession = (AgentServerSession *) pRecvMsg->m_pNetObj;
		if ( pSession != NULL ) {
			pLoginUser->SetRootID(pRecvMsg->m_uiRootID);
			
			printf("m_byUserKey = %s\n", pRecvMsg->m_byUserKey);			
			pLoginUser->SetMD(pRecvMsg->m_byUserKey);
			
			LoginUserManager::Instance()->PUSH(pLoginUser); // 根据RootID来查找LoginUser，组成一个map
			
			// 返回给本地 Agent 消息包
			MSG_AL_PRELOGIN_ANC msg2;
			msg2.m_dwParameter 	= pRecvMsg->m_dwParameter; // dwUserID
			msg2.m_uiRootID 	= pRecvMsg->m_uiRootID;
			memcpy( msg2.m_byUserKey, pRecvMsg->m_byUserKey, CODE_KEY_LEN); // 动态生成的Key值
			
			AgentServerSession * pConnSession = AllocServer::Instance()->POP(); // Login服务器在初始化时读配置文件,然后AllocAgent把IP，Port存进去。
			if ( pConnSession == NULL ) {
				printf("AllocServer::Instance()->POP() Fail\n");
				return;
			}
			
			memcpy( msg2.m_byIP, pConnSession->GetConnnectIP().c_str(), IP_MAX_LEN ); // 32
			msg2.m_dwPort = pConnSession->GetConnnectPort();			
			printf("IP = %s, Port = %d\n", msg2.m_byIP, msg2.m_dwPort);
						
			g_LoginServer->SendToAgentServer( (BYTE *)&msg2, sizeof(MSG_AL_PRELOGIN_ANC) );
						
			// 同时还要把这个LoginUser添加到LoginUserManager中管理
			LoginUserManager::Instance()->PUSH(pLoginUser);
			
			// 发送给远程 Agent 消息包，保存 UserKey 值
			MSG_AL_SAVEUSERKEY_SYN msg1;
			msg1.m_uiRootID = pRecvMsg->m_uiRootID;
			memcpy( msg1.m_byUserKey, pRecvMsg->m_byUserKey, CODE_KEY_LEN); // 动态生成的Key值
			pConnSession->Send( (BYTE *)&msg1, sizeof(msg1) );
		}
	}
#endif	
}


HANDLER_IMPL( PreLogin_NAK )
{
	printf(">> PreLogin_NAK\n");
}
