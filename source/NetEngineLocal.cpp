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
void NetEngineLocal::Send( Packet* packet, long long int target )
{
    for( unsigned int i = 0; i < netNodes.size(); i++ )
    {
        if( netNodes[i]->GetAddress() == target )
        {
            netNodes[i]->GetInbox()->push_back( packet );
        }
    }
}
void NetEngineLocal::SetTarget( long long int target )
{
    this->target = target;
}
void NetEngineLocal::SetAddress( long long int address )
{
    this->address = address;
}
void NetEngineLocal::Send( Packet* packet )
{
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
        inbox.pop_back();
        return tmp;
    }
    return NULL;
}
bool NetEngineLocal::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return false;
    }
    return true;
}
bool NetEngineLocal::InboxFull()
{
    return false;
}
unsigned int NetEngineLocal::NumPacketsInInbox()
{
    return inbox.size();
}
long long int NetEngineLocal::GetAddress()
{
    return address;
}
vector<Packet*>* NetEngineLocal::GetInbox()
{
    return &inbox;
}