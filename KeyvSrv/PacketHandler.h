#ifndef _PACKET_HANDLER_H_INCLUDED_
#define _PACKET_HANDLER_H_INCLUDED_

#include <Common.h>
#include <Network.h>
#include <Utility.h>
using namespace A;

#include "ServerSession.h"

typedef VOID (*fnHandler)( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );

class PacketHandler
{
public:
	PacketHandler(void);
	~PacketHandler(void);

public:
	BOOL RegisterHandler();
	void Register_LK();
	void Register_KD();
	
	BOOL AddHandler_LK( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_KD( WORD category, WORD protocol, fnHandler fnHandler);

	void ParsePacket_LK( ServerSession * pUserSession, MSG_BASE * pMsg, WORD wSize );
	void ParsePacket_KD( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );

private:
	struct FUNC_LK : public BASE_FUNC
	{
		fnHandler	m_fnHandler;
	};

	struct FUNC_KD : public BASE_FUNC
	{
		fnHandler	m_fnHandler;
	};

	FunctionMap	*	m_pFuncMap_LK; // Line --> Login
	FunctionMap	*	m_pFuncMap_KD; // Line --> DB
};

extern PacketHandler g_PacketHandler;

#endif
