//NetEngine.cpp

#include "NetEngine.h"
#include "GameEngine.h"

Packet::Packet()
{
    data = NULL;
}

Packet::~Packet()
{
    free( data );
}

void Packet::FixData()
{
    void* tmp;
    tmp = malloc( dataLength );
    memcpy( tmp, data, dataLength );
    data = tmp;
}


NetEngine::NetEngine( GameEngine* engine )
{
	this->engine = engine;
}
NetEngine::~NetEngine()
{

}