//NetEngineLocal.cpp

#include "NetEngineLocal.h"


//======== global Variables ==========
vector<NetEngineLocal*> netNodes;
//====================================



NetEngineLocal::NetEngineLocal()
{
    netNodes.push_back(this);
}
void NetEngineLocal::Init()
{

}
void NetEngineLocal::Send( Packet* packet, uint64_t target )
{
    packet->FixData();

    for( unsigned int i = 0; i < netNodes.size(); i++ )
    {
        if( netNodes[i]->GetAddress() == target )
        {
            netNodes[i]->GetInbox()->push_back( packet );
        }
    }
}
void NetEngineLocal::SetTarget( uint64_t target )
{
    this->target = target;
}
void NetEngineLocal::SetAddress( uint64_t address )
{
    this->address = address;
}
void NetEngineLocal::Send( Packet* packet )
{
    packet->FixData();
    
    for( unsigned int i = 0; i < netNodes.size(); i++ )
    {
        if( netNodes[i]->GetAddress() == target )
        {
            netNodes[i]->GetInbox()->push_back( packet );
        }
    }
}
Packet* NetEngineLocal::GetFirstPacketFromInbox()
{
    if( inbox.size() > 0 )
    {
        Packet* tmp = inbox[0];
        inbox.erase( inbox.begin() );
        return tmp;
    }
    return NULL;
}
bool NetEngineLocal::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return true;
    }
    return false;
}
bool NetEngineLocal::InboxFull()
{
    return false;
}
unsigned int NetEngineLocal::GetNumPacketsInInbox()
{
    return inbox.size();
}
uint64_t NetEngineLocal::GetAddress()
{
    return address;
}
vector<Packet*>* NetEngineLocal::GetInbox()
{
    return &inbox;
}
int NetEngineLocal::GetType()
{
    return NET_TYPE_LOCAL_BUFFER;
}