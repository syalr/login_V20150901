#include "KeyvSession.h"
#include "LoginServer.h"

KeyvSession::KeyvSession()
{
}

KeyvSession::~KeyvSession()
{
}

void KeyvSession::Init()
{
}

void KeyvSession::Release()
{
}

void KeyvSession::OnRecv(BYTE * pMsg, WORD wSize)
{
	g_pLoginServer->SendToUserServer(pMsg, wSize);
}

void KeyvSession::OnLogString( char * pszLog)
{
	
}


