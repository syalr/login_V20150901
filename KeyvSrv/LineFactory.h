#ifndef _LINE_FACTORY_H_INCLUDED_
#define _LINE_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>


#include "LoginServerSession.h"
#include "DBServerSession.h"

#include "LineUser.h"

using namespace A;

class LineFactory : public Singleton<LineFactory>
{
	
public:
	LineFactory();
	~LineFactory();

private:
	// LineUser
	MemoryFactory<LineUser> 			* m_pLineUserPool;

	// Server
	//MemoryFactory<TempServerSession>	* m_pTempServerSessionPool;	
	MemoryFactory<LoginServerSession>	* m_pLoginServerSessionPool;
	MemoryFactory<DBServerSession>		* m_pDBServerSessionPool;

public:
	void Init(void);
	void Release(void);

	LineUser * AllocLineUser();
	void FreeLineUser(LineUser * pUser);
	
	// Server
	//TempServerSession * AllocTempServerSession();
	//void FreeTempServerSession(TempServerSession * pServerSession);
	
	LoginServerSession * AllocLoginServerSession();
	void FreeLoginServerSession(LoginServerSession * pServerSession);
	
	DBServerSession * AllocDBServerSession();
	void FreeDBServerSession(DBServerSession * pServerSession);
};

#endif // _LINE_FACTORY_H_INCLUDED_
