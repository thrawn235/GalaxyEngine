//NetEngineDosPacketDriverUDP.cpp

#include "NetEngineDosPacketDriverUDP.h"
#include "GameEngine.h"


NetEngineDosPacketDriverUDP::NetEngineDosPacketDriverUDP( GameEngine* engine ) : NetEngine( engine )
{
    port = 1234;
    isConnected = false;
    isServer = false;
    receiveBuffer = malloc( NET_BUFFER_SIZE );

    
}
NetEngineDosPacketDriverUDP::~NetEngineDosPacketDriverUDP()
{
    
}



void NetEngineDosPacketDriverUDP::SetAddress( uint64_t address )
{
    //
    this->address = address;
}
uint64_t NetEngineDosPacketDriverUDP::GetAddress()
{
    //
    return address;
}
int NetEngineDosPacketDriverUDP::GetType()
{
    //
    return NET_TYPE_DOS_PACKET_DRIVER_UDP;
}
unsigned int NetEngineDosPacketDriverUDP::GetNumPacketsInInbox()
{
    //
    return inbox.size();
}
bool NetEngineDosPacketDriverUDP::GetIsServer()
{
    //
    return isServer;
}
void NetEngineDosPacketDriverUDP::Send( Packet* packet )
{
    engine->debug->PrintString( "sending...\n" );
    int dataLength = 0;
    void* data = SerializePacketData( packet, &dataLength );
    
    engine->debug->PrintString( "   %i bytes...\n", dataLength );

    if( isServer )
    {
        //the server sends packages to all clients
        
    }
    else
    {
        //the client only sends packets to the server (peerAddress)
        
    }
}
Packet* NetEngineDosPacketDriverUDP::GetFirstPacketFromInbox()
{
    engine->debug->PrintString( "getting packet from inbox...\n" );
    if( inbox.size() > 0 )
    {
        engine->debug->PrintString( "inbox is NOT empty...\n" );
        Packet* tmp = inbox.back();
        
        engine->debug->PrintString( "Packet: sender:%i type:%i dataLength:%i\n", tmp->sender, (unsigned int)tmp->type, tmp->dataLength );
        
        inbox.pop_back();
        return tmp;
    }
    return NULL;
}
vector<Packet*>* NetEngineDosPacketDriverUDP::GetInbox()
{
    //
    return &inbox;
}
bool NetEngineDosPacketDriverUDP::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return true;
    }
    return false;
}



void NetEngineDosPacketDriverUDP::Connect( uint64_t target )
{
    this->target = target;


    if( !isConnected )
    {
        //if a client is not connected yet it sends a join request to the server (peerAddress)
        SendJoinRequest();
    }
}
void NetEngineDosPacketDriverUDP::Disconnect()
{
    if( isConnected )
    {
        SendDisconnectRequest();
        
        isConnected = false;
    }
}
bool NetEngineDosPacketDriverUDP::GetIsConnected()
{
    //
    return isConnected;
}


void NetEngineDosPacketDriverUDP::ConfigureAsServer()
{
    isServer = true;
    
}
vector<uint64_t> NetEngineDosPacketDriverUDP::GetClientAddresses()
{
    vector<uint64_t> clients;


    return clients;
}


void* NetEngineDosPacketDriverUDP::SerializePacketData( Packet* packet, int* dataLength )
{
    void* data = malloc( sizeof( Packet ) + packet->dataLength );
    memcpy( data, packet, sizeof( Packet ) );
    memcpy( (char*)data + sizeof( Packet ), packet->data, packet->dataLength );
    *dataLength = sizeof( Packet ) + packet->dataLength;
    return data;
}
Packet* NetEngineDosPacketDriverUDP::DeSerializePacketData( void* data, int dataLength )
{
    Packet* packet = new Packet;
    memcpy( packet, data, sizeof( Packet ) );
    packet->data = malloc( packet->dataLength );
    memcpy( packet->data, (char*)data + sizeof( Packet), packet->dataLength );
    return packet;
}


void NetEngineDosPacketDriverUDP::SendJoinRequest()
{
    engine->debug->PrintString( "sending join request...\n" );

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_JOIN_REQUEST;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    
    engine->debug->PrintString( "sending %i bytes...\n", dataLength );
}
void NetEngineDosPacketDriverUDP::SendDisconnectRequest()
{
    engine->debug->PrintString( "sending disconnect request...\n" );

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_DISCONNECT_REQUEST;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    
    engine->debug->PrintString( "   sending %i bytes\n", dataLength );
}

void NetEngineDosPacketDriverUDP::SendJoinAck()
{
    engine->debug->PrintString( "sending join acknolagement...\n" );

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_JOIN_ACK;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    
    engine->debug->PrintString( "   sending %i bytes\n", dataLength );
}
void NetEngineDosPacketDriverUDP::ReceivePackets()
{
    engine->debug->PrintString( "   checking socket for data...\n" );

    
}
void NetEngineDosPacketDriverUDP::Update()
{
    ReceivePackets();
}