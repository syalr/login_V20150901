#ifndef _LINESERVERSESSION_H_INCLUDED_
#define _LINESERVERSESSION_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "ServerSession.h"

class LineServerSession : public ServerSession
{
public:

	LineServerSession();
	virtual ~LineServerSession();
	
	eSERVER_TYPE    GetServerType() { return LINE_SERVER; }
	
	virtual void    Init();
	
protected:

	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnDisconnect();
	virtual void	OnLogString( char * pszLog);
	
};

#endif // _LOGINSERVERSESSION_H_INCLUDED_
