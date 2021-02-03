//NetEngineLinuxSockets.cpp

#include "NetEngineLinuxSockets.h"


NetEngineLinuxSockets::NetEngineLinuxSockets()
{
    netNodes.push_back(this);
}
void NetEngineLinuxSockets::Init()
{

}
void NetEngineLinuxSockets::Send( Packet* packet, uint64_t target )
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
void NetEngineLinuxSockets::SetTarget( uint64_t target )
{
    this->target = target;
}
void NetEngineLinuxSockets::SetAddress( uint64_t address )
{
    this->address = address;
}
void NetEngineLinuxSockets::Send( Packet* packet )
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
Packet* NetEngineLinuxSockets::GetFirstPacketFromInbox()
{
    if( inbox.size() > 0 )
    {
        Packet* tmp = inbox[0];
        inbox.erase( inbox.begin() );
        return tmp;
    }
    return NULL;
}
bool NetEngineLinuxSockets::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return true;
    }
    return false;
}
bool NetEngineLinuxSockets::InboxFull()
{
    return false;
}
unsigned int NetEngineLinuxSockets::GetNumPacketsInInbox()
{
    return inbox.size();
}
uint64_t NetEngineLinuxSockets::GetAddress()
{
    return address;
}
vector<Packet*>* NetEngineLinuxSockets::GetInbox()
{
    return &inbox;
}
int NetEngineLinuxSockets::GetType()
{
    return NET_TYPE_LINUX_SOCKETS;
}