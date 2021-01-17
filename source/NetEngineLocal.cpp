//NetEngineLocal.cpp

#include "NetEngineLocal.h"

NetEngineLocal::NetEngineLocal( NetBuffer* localNetBuffer ) : NetEngine( localNetBuffer )
{
	this->localNetBuffer = localNetBuffer;
}
void NetEngineLocal::SetTarget( string target )
{
	
}
void NetEngineLocal::SendCommand( NetCommand* command )
{
	
}
void NetEngineLocal::SendLayer1( unsigned char out )
{
	if( localNetBuffer->lastIndex > NET_BUFFER_SIZE )
	{
		localNetBuffer->lastIndex = 0;
	}
	localNetBuffer->buffer[localNetBuffer->lastIndex] = out;
	localNetBuffer->lastIndex++;
}
unsigned char NetEngineLocal::ReceiveLayer1()
{
	unsigned char temp;
	temp = localNetBuffer->buffer[localNetBuffer->firstIndex];
	localNetBuffer->firstIndex ++;
	if( localNetBuffer->firstIndex > NET_BUFFER_SIZE )
	{
		localNetBuffer->firstIndex = 0;
	}
	return temp;
}
unsigned int NetEngineLocal::GetLayer1Unread()
{
	return localNetBuffer->lastIndex - localNetBuffer->firstIndex;
}