#include "Handler_FromLineServer.h"
#include "DBFactory.h"
#include "LoginServerQuery.h"
#include <Public.h>

Handler_FromLineServer::Handler_FromLineServer() 
{
	
}

Handler_FromLineServer::~Handler_FromLineServer() 
{
	
}

HANDLER_IMPL( PreLogin_REQ )
{
	printf("Step1: <3> LD_Login_REQ\n");
	
#if 0
	// 传入消息包 包含: m_pNetObj, m_byUsername, m_byPassword
	MSG_LD_LOGIN_REQ * pRecvMsg = (MSG_LD_LOGIN_REQ *)pMsg;
		
	TCHAR szQueryBuff[1024];
	snprintf(szQueryBuff, sizeof(szQueryBuff), "call g_Login_Select(\'%s\',\'%s\')", pRecvMsg->m_byUsername, pRecvMsg->m_byPassword);
	printf("\nQuery: username = %s, password = %s\n", pRecvMsg->m_byUsername, pRecvMsg->m_byPassword);
	Query_Login_update * pQuery = Query_Login_update::ALLOC();
	
	if (NULL != pQuery) 
	{
		pQuery->SetQuery( szQueryBuff );
		Obj_db_passport.QueryDirect( pQuery );
		
		int iSize = pQuery->vctRes.size();
		if (iSize == 1) 
		{
			// DB返回应答给 Login
			MSG_LD_LOGIN_ANC msg2;
			msg2.m_dwParameter = pRecvMsg->m_dwParameter; // UserKey
						
			msg2.m_uiRootID = pQuery->vctRes[0].m_uiRootID;
			msg2.m_pNetObj = pRecvMsg->m_pNetObj;
			
			// 生成一个5位的随机值
			char szRandom[11] = {0};
			if ( is_support_drng() ) {
				// 支持随机数
				GetRandom(szRandom);				
			}
			else {
				// 不支持随机数
				GetRandom_C(szRandom);			
			}
			printf("Random = %s\n", szRandom);
			
			// MD5加密			
			string tmpStr(szRandom);
			string outMD5 = MD5(tmpStr).toString() ;	
			sprintf( (char *)msg2.m_byUserKey, "%s", outMD5.c_str() );
			printf("outMD5 = %s, m_byUserKey = %s\n", outMD5.c_str(), msg2.m_byUserKey);
			//BYTE m_byUserKey[CODE_KEY_LEN + 1]; // 33
			pServerSession->Send( (BYTE*)&msg2, sizeof(msg2) );
		}
		
		Query_Login_update::FREE( pQuery );
		pQuery = NULL;		
	}
	
#endif

}
