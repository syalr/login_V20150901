#ifndef _SENDBUFFER_H_INCLUDED_
#define _SENDBUFFER_H_INCLUDED_

#include <Utility.h>
#include <Network.h>

//=============================================================================================================================
/// 
//	send  GQCS completion Completion(int).
//=============================================================================================================================
class SendBuffer
{
public:
	SendBuffer()			{ m_pQueue = NULL; }
	virtual ~SendBuffer()	{ if( m_pQueue ) delete m_pQueue; }

	inline void Create( int nBufferSize, DWORD dwExtraBuffeSize ) {
		if( m_pQueue ) delete m_pQueue;
		m_pQueue = new CircuitQueue<BYTE>;
		m_pQueue->Create( nBufferSize, dwExtraBuffeSize );
		m_bComplete = TRUE; }
	inline void Clear() { m_pQueue->Clear(); m_bComplete = TRUE; }

	inline void Completion( int nBytesSend ) { 	m_pQueue->Dequeue( NULL, nBytesSend ); m_bComplete = TRUE; }

	//  GetSendParam m_bComplete = FALSE .
	inline BOOL	GetSendParam( BYTE **ppSendPtr, int &nLength ) 
	{
		if( !IsReadyToSend() ) 
		{ 
			nLength = 0; 
			return FALSE; 
		}
		*ppSendPtr	= m_pQueue->GetReadPtr();
		nLength		= m_pQueue->GetReadableLen();
		m_bComplete = FALSE;
		return TRUE; 
	}

	inline BOOL Write( tagPACKET_HEADER *pHeader, BYTE *pMsg )	{
		if( !m_pQueue->Enqueue( (BYTE*)pHeader, sizeof(PACKET_HEADER) ) )	return FALSE;
		if( !m_pQueue->Enqueue( pMsg, pHeader->size ) )						return FALSE;
		return TRUE; }

	inline BOOL Write( BYTE *pMsg, WORD wSize ) {
		if( !m_pQueue->Enqueue( pMsg, wSize ) ) return FALSE;
		return TRUE; }

	inline DWORD GetLength() { return m_pQueue->GetLength(); }

	inline BOOL			IsReadyToSend() { return ( m_bComplete && m_pQueue->GetLength() > 0 ) ? TRUE : FALSE; }

private:
	BOOL				m_bComplete;
	CircuitQueue<BYTE>	*m_pQueue;
};

#endif