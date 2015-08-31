#ifndef _HANDLER_FROMLINESERVER_H_INCLUDED_
#define _HANDLER_FROMLINESERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL(p)	static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL(p)	VOID Handler_FromLineServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromLineServer
{
public:
	Handler_FromLineServer(void);
	~Handler_FromLineServer(void);

	HANDLER_DECL( PreLogin_REQ );
};


#endif
