//NetEngine.cpp

#include "NetEngine.h"

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