//NetEngineDummy.cpp

#include "NetEngineDummy.h"


NetEngineDummy::NetEngineDummy( GameEngine* engine ) : NetEngine( engine )
{

}
NetEngineDummy::~NetEngineDummy()
{

}



void NetEngineDummy::SetAddress( uint64_t address )
{

}
uint64_t NetEngineDummy::GetAddress()
{
    return 0;
}
int NetEngineDummy::GetType()
{
    return NET_TYPE_DUMMY;
}
unsigned int NetEngineDummy::GetNumPacketsInInbox()
{
    return 0;
}
bool NetEngineDummy::GetIsServer()
{
    return false;
}
void NetEngineDummy::Send( Packet* packet )
{

}
Packet* NetEngineDummy::GetFirstPacketFromInbox()
{
    return NULL;
}
vector<Packet*>* NetEngineDummy::GetInbox()
{
    return NULL;
}
bool NetEngineDummy::InboxEmpty()
{
    return false;
}



void NetEngineDummy::Connect( uint64_t target )
{

}
void NetEngineDummy::Disconnect()
{

}
bool NetEngineDummy::GetIsConnected()
{
    return false;
}


void NetEngineDummy::ConfigureAsServer()
{

}
vector<uint64_t> NetEngineDummy::GetClientAddresses()
{
    vector<uint64_t> clients;
    return clients;
}

void NetEngineDummy::Update()
{
    
}