//NetEngineLocal.cpp

#include "NetEngineLocal.h"

NetEngineLocal::NetEngineLocal( vector<NetCommand>* localNetBuffer ) : NetEngine( localNetBuffer )
{
	this->localNetBuffer = localNetBuffer;
}
void NetEngineLocal::SetTarget( string target )
{
	
}
void NetEngineLocal::SendCommand( NetCommand* command )
{
	
}