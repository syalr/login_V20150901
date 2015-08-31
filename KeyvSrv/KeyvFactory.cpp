#include "KeyvFactory.h"

KeyvFactory::KeyvFactory()
{
	m_pLoginServerSessionPool 	= NULL;
	m_pDBServerSessionPool 		= NULL;
}

KeyvFactory::~KeyvFactory()
{
	if (m_pLoginServerSessionPool) 	delete m_pLoginServerSessionPool;
	if (m_pDBServerSessionPool) 	delete m_pDBServerSessionPool;
}

void KeyvFactory::Init()
{
	m_pLoginServerSessionPool 	= new MemoryFactory<LoginServerSession>;
	m_pDBServerSessionPool 		= new MemoryFactory<DBServerSession>;
	
	m_pLoginServerSessionPool->Initialize(1,1);
	m_pDBServerSessionPool->Initialize(1,1);
}

LoginServerSession * KeyvFactory::AllocLoginServerSession() {
	assert(m_pDBServerSessionPool == NULL);
	return m_pLoginServerSessionPool->Alloc();
}
void KeyvFactory::FreeLoginServerSession(LoginServerSession * pServerSession) {
	return m_pLoginServerSessionPool->Free(pServerSession);
}

DBServerSession * KeyvFactory::AllocDBServerSession() {
	assert(m_pDBServerSessionPool == NULL);
	return m_pDBServerSessionPool->Alloc();
}
void KeyvFactory::FreeDBServerSession(DBServerSession * pServerSession) {
	return m_pDBServerSessionPool->Free(pServerSession);
}
