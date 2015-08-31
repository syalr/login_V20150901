#include "LineServer.h"

int main(int argc, char ** argv) 
{
	g_LineServer = new LineServer;
	g_LineServer->Init();
	
	while(true) {
		Sleep(100);
		g_LineServer->Update(0);
	}
	
	return 0;
}