#include "LoginUserManager.h"

LoginUserManager::LoginUserManager()
{
	//m_mapLoginUser.clear();
}

LoginUserManager::~LoginUserManager()
{
	Release();
}

void LoginUserManager::Release()
{
	m_mapLoginUser.clear();
}

BOOL LoginUserManager::Init()
{
	m_mapLoginUser.clear();
	return TRUE;
}

void LoginUserManager::PUSH(LoginUser * pLoginUser)
{
	MAP_LOGINUSER_ITER it = m_mapLoginUser.find( pLoginUser->GetRootID() );
	if ( it != m_mapLoginUser.end() )
	{
		m_mapLoginUser[ pLoginUser->GetRootID() ] = pLoginUser;
	}
}

LoginUser * LoginUserManager::POP(DWORD dwRootID)
{
	MAP_LOGINUSER_ITER it = m_mapLoginUser.find( dwRootID );
	if ( it != m_mapLoginUser.end() )
	{
		LoginUser * pLoginUser = it->second;
		m_mapLoginUser.erase( it );
		return pLoginUser;
	}
}
