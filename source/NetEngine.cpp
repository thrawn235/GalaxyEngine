//NetEngine.cpp

#include "NetEngine.h"
#include "GameEngine.h"

Packet::Packet()
{
    data = NULL;
    dataLength = 0;
    sender = 0;
    type = 0;
}

Packet::~Packet()
{
    free( data );
}

void Packet::FixData()
{
	if( data != NULL )
	{
	    void* tmp;
	    tmp = malloc( dataLength );
	    memcpy( tmp, data, dataLength );
	    data = tmp;
	}
}


NetEngine::NetEngine( GameEngine* engine )
{
	this->engine = engine;
}
NetEngine::~NetEngine()
{

}