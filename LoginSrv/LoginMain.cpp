#include "LoginServer.h"


int main(int argc, char ** argv) 
{
	g_pLoginServer = new LoginServer;
	assert(g_pLoginServer);
	
	if( !g_pLoginServer->Init() ) {
		return 0;
	}
	
	DWORD dwTicket = 0;
	int nShutdown  = 1;
	
	while( nShutdown ) {
		usleep(20);

		dwTicket = Session::GetTickCount();
		
		if ( !g_pLoginServer->Update( dwTicket ) ) {
			break;
		}
	}

	SAFE_DELETE(g_pLoginServer);

	return 0;
}




