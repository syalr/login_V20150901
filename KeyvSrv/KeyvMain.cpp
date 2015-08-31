#include "KeyvServer.h"


int main(int argc, char ** argv) 
{
	g_pKeyvServer = new KeyvServer;
	g_pKeyvServer->Init();
	
	while(true) {
		Sleep(100);
		g_pKeyvServer->Update(0);
	}
	
	return 0;
}