#include "DBFactory.h"

DBFactory::DBFactory()
{
	m_pTempServerSessionPool = NULL;	
	m_pLineServerSessionPool = NULL;
}

DBFactory::~DBFactory()
{
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
	if (m_pLineServerSessionPool) 	delete m_pLineServerSessionPool;
}

void DBFactory::Init()
{
	m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	m_pLineServerSessionPool 	= new MemoryFactory<LineServerSession>; 
	m_pTempServerSessionPool->Initialize(1,1);
	m_pLineServerSessionPool->Initialize(1,1); // ???
}

TempServerSession * DBFactory::AllocTempServerSession() 
{
	assert ( m_pTempServerSessionPool );
	TempServerSession * pSession = m_pTempServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
	return pSession;
}
void DBFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}

LineServerSession * DBFactory::AllocLineServerSession() {
	assert ( m_pLineServerSessionPool );
	if (m_pLineServerSessionPool == NULL) {
		return NULL;
	}
	return m_pLineServerSessionPool->Alloc();	
}
void DBFactory::FreeLineServerSession(LineServerSession * pServerSession) {
	return m_pLineServerSessionPool->Free(pServerSession);
}

