#ifndef _AGENT_FACTORY_H_INCLUDED_
#define _AGENT_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>

#include "ServerSession.h"
#include "TempServerSession.h"
#include "LineServerSession.h"

using namespace A;

class DBFactory : public Singleton<DBFactory>
{
	
public:
	DBFactory();
	~DBFactory();

private:
	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool;
	MemoryFactory<LineServerSession>	* m_pLineServerSessionPool; 

public:
	void Init(void);
	void Release(void);

	// Server
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);
	
	LineServerSession * AllocLineServerSession();
	void FreeLineServerSession(LineServerSession * pServerSession);
};

#endif
