#ifndef _SERVERSESSION_H_INCLUDED_
#define _SERVERSESSION_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

class ServerSession : public NetworkObject
{
public:
	ServerSession();
	virtual ~ServerSession();

	virtual void    Init();
	virtual void	Clear();
	virtual void    Update();
	virtual void    Release();
	
	virtual void	OnAccept( DWORD dwNetworkIndex );
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void	OnDisconnect();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	
	virtual void	OnLogString( char * pszLog);

	virtual eSERVER_TYPE	GetServerType() {	return DB_SERVER; }
	
	DWORD GetSessionIndex() {	return m_dwSessionIndex; }
	void  SetSessionIndex( DWORD dwIdx) { m_dwSessionIndex = dwIdx; }
	
	void SendServerType();
	void SetAddr( char * pszIP, WORD wPort );
	void TryToConnect(); 
	
	inline std::string & GetConnnectIP() 	{ return m_strConnectIP; }
	inline WORD  	   & GetConnnectPort() 	{ return m_wConnectPort; }
	inline BOOL IsConnected()	   	{ return m_bConnection; }
	inline void SetForConnect(BOOL bForConnect)	{ m_bForConnect = bForConnect; }
	inline bool IsForConnect() { return m_bForConnect; }
	
public:
	DWORD m_dwSessionIndex;
	std::string m_strConnectIP;
	WORD  m_wConnectPort;
	BOOL  m_bForConnect;
	DWORD m_dwLastHeartbeatTime;
	DWORD m_bConnection;
};

#endif // _AGENTPLAYER_H_INCLUDED_
