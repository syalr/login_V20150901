#include "LineFactory.h"

LineFactory::LineFactory()
{
	m_pLineUserPool 	= NULL;
	
	//m_pTempServerSessionPool 	= NULL;
	m_pLoginServerSessionPool 	= NULL;
	m_pDBServerSessionPool 		= NULL;
}

LineFactory::~LineFactory()
{
	if (m_pLineUserPool) 			delete m_pLineUserPool;
	
	//if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
	if (m_pLoginServerSessionPool) 	delete m_pLoginServerSessionPool;
	if (m_pDBServerSessionPool) 	delete m_pDBServerSessionPool;
}

void LineFactory::Init()
{
	m_pLineUserPool 			= new MemoryFactory<LineUser>;
	
	//m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	m_pLoginServerSessionPool 	= new MemoryFactory<LoginServerSession>;
	m_pDBServerSessionPool 		= new MemoryFactory<DBServerSession>;
	
	m_pLineUserPool->Initialize(4098,1);
	//m_pTempServerSessionPool->Initialize(5,1);
	m_pLoginServerSessionPool->Initialize(1,1);
	m_pDBServerSessionPool->Initialize(1,1);
}

LineUser * LineFactory::AllocLineUser() {
	if (m_pLineUserPool == NULL) {
		return NULL;
	}
	return m_pLineUserPool->Alloc();
}
void LineFactory::FreeLineUser(LineUser * pUser) {
	return m_pLineUserPool->Free(pUser);
}

//TempServerSession * LineFactory::AllocTempServerSession() {
//	if (m_pTempServerSessionPool == NULL) {
//		return NULL;
//	}
//	return m_pTempServerSessionPool->Alloc();
//}

//void LineFactory::FreeTempServerSession(TempServerSession * pServerSession) {
//	return m_pTempServerSessionPool->Free(pServerSession);
//}

LoginServerSession * LineFactory::AllocLoginServerSession() {
	if (m_pLoginServerSessionPool == NULL) {
		return NULL;
	}
	return m_pLoginServerSessionPool->Alloc();
}

void LineFactory::FreeLoginServerSession(LoginServerSession * pServerSession) {
	return m_pLoginServerSessionPool->Free(pServerSession);
}

DBServerSession * LineFactory::AllocDBServerSession() {
	if (m_pDBServerSessionPool == NULL) {
		return NULL;
	}
	return m_pDBServerSessionPool->Alloc();
}

void LineFactory::FreeDBServerSession(DBServerSession * pServerSession) {
	return m_pDBServerSessionPool->Free(pServerSession);
}

