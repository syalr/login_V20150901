#include "LineServerSession.h"
#include "PacketHandler.h"

LineServerSession::LineServerSession()
{	
}

LineServerSession::~LineServerSession()
{
}

void LineServerSession::Init()
{
	
}

void LineServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("call g_PacketHandler.ParsePacket_LD function.\n");
	g_PacketHandler.ParsePacket_LD( this, (MSG_BASE *)pMsg, wSize );
}

void LineServerSession::OnDisconnect()
{
	ServerSession::OnDisconnect();
}

void LineServerSession::OnLogString( char * pszLog )
{
	
}
