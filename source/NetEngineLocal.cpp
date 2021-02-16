//NetEngineLocal.cpp

#include "NetEngineLocal.h"
#include "GameEngine.h"

//======== global Variables ==========
vector<NetEngineLocal*> netNodes;
//====================================



NetEngineLocal::NetEngineLocal( GameEngine* engine ) : NetEngine( engine )
{
    isServer = false;
}

void NetEngineLocal::SetAddress( uint64_t address )
{
    this->address = address;
}
uint64_t NetEngineLocal::GetAddress()
{
    return address;
}
int NetEngineLocal::GetType()
{
    return NET_TYPE_LOCAL_BUFFER;
}
unsigned int NetEngineLocal::GetNumPacketsInInbox()
{
    return inbox.size();
}
bool NetEngineLocal::GetIsServer()
{
    return isServer;
}
void NetEngineLocal::Send( Packet* packet )
{
    if( isConnected  || isServer )
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
vector<Packet*>* NetEngineLocal::GetInbox()
{
    return &inbox;
}
bool NetEngineLocal::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return true;
    }
    return false;
}


void NetEngineLocal::InitClient()
{

}
void NetEngineLocal::Connect( uint64_t target )
{
    if( !isConnected )
    {
        this->target = target;

        isConnected = true;
        netNodes.push_back(this);
    }
}
void NetEngineLocal::Disconnect()
{
    for( unsigned int i = 0; i < netNodes.size(); i++ )
    {
        if( netNodes[i] == this )
        {
            netNodes.erase( netNodes.begin() + i );
        }
    }
    isConnected = false;
}
bool NetEngineLocal::GetIsConnected()
{
    return isConnected;
}


void NetEngineLocal::InitServer()
{
    isServer = true;
}
vector<uint64_t> NetEngineLocal::GetClientAddresses()
{
    vector<uint64_t> clients;

    for( unsigned int i = 0; i < netNodes.size(); i++ )
    {
        if( netNodes[i] == this )
        {
            
        }
        else
        {
            clients.push_back( netNodes[i]->GetAddress() );
        }
    }
    return clients;
}


void NetEngineLocal::Update()
{

}