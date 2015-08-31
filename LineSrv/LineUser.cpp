#include "LineUser.h"

LineUser::LineUser()
{
	m_dwKey = 0;
	m_dwRootID = 0;
	memset(m_byMD5, 0, CODE_KEY_LEN + 1);
}

LineUser::~LineUser()
{
	
}

void LineUser::SetMD( BYTE * _md5 )
{
	assert( _md5 != NULL );
	
	for ( int i=0; i<CODE_KEY_LEN; ++i )
	{
		m_byMD5[i] = _md5[i];
	}
}

BOOL LineUser::IsSameMD( BYTE * _md5 )
{
	assert( _md5 != NULL );
	
	for ( int i=0; i<CODE_KEY_LEN; ++i )
	{
		if ( _md5[i] != m_byMD5[i] )
		{
			goto GT_FALSE;
		}
	}
	return TRUE;
	
GT_FALSE:
	return FALSE;
}