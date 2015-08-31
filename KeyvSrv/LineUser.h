#ifndef _LINE_USER_H_INCLUDED_
#define _LINE_USER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>

class LineUser
{
public:
	LineUser();
	~LineUser();

	void SetHashKey( DWORD dwKey ) { m_dwKey = dwKey; }
	DWORD GetHashKey() { return m_dwKey; }
	
	void SetRootID( DWORD dwRootID ) { m_dwRootID = dwRootID; }
	DWORD GetRootID() { return m_dwRootID; }
	
	void SetMD( BYTE * _md5 );
	BOOL IsSameMD( BYTE * _md5 );
	
private:
	DWORD  m_dwKey;
	DWORD  m_dwRootID;
	BYTE   m_byMD5[CODE_KEY_LEN + 1];
};

#endif // _LINE_USER_H_INCLUDED_