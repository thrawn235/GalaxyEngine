//NetEngineWinSocketsUDP.cpp

#include "NetEngineWinSocketsUDP.h"
#include "GameEngine.h"


NetEngineWinSocketsUDP::NetEngineWinSocketsUDP( GameEngine* engine ) : NetEngine( engine )
{
    port = 1234;
    isConnected = false;
    isServer = false;
    receiveBuffer = malloc( NET_BUFFER_SIZE );

    engine->debug->PrintString( "initializing winsocks...\n" );
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        engine->debug->PrintString( "could noot initialize WSA!\n" );
    }

    engine->debug->PrintString( "creating UDP socket...\n" );
    socketDescriptor = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    if( socketDescriptor == INVALID_SOCKET )
    {
        engine->debug->PrintString( "could not create socket!\n" );
    }
    u_long iMode = 1; //non blocking
    ioctlsocket(socketDescriptor, FIONBIO, &iMode);
}
NetEngineWinSocketsUDP::~NetEngineWinSocketsUDP()
{
    engine->debug->PrintString( "closing socket...\n" );

    closesocket( socketDescriptor );
}



void NetEngineWinSocketsUDP::SetAddress( uint64_t address )
{
    //
    this->address = address;
}
uint64_t NetEngineWinSocketsUDP::GetAddress()
{
    //
    return address;
}
int NetEngineWinSocketsUDP::GetType()
{
    //
    return NET_TYPE_LINUX_SOCKETS_UDP;
}
unsigned int NetEngineWinSocketsUDP::GetNumPacketsInInbox()
{
    //
    return inbox.size();
}
bool NetEngineWinSocketsUDP::GetIsServer()
{
    //
    return isServer;
}
void NetEngineWinSocketsUDP::Send( Packet* packet )
{
    engine->debug->PrintString( "sending " );

    int dataLength = 0;
    void* data = SerializePacketData( packet, &dataLength );

    engine->debug->PrintString( "%i bytes...\n", dataLength );

    if( isServer )
    {
        //the server sends packages to all clients
        for( unsigned int i = 0; i < incomingAddresses.size(); i++ )
        {
            if( sendto( socketDescriptor, (char*)data, dataLength, 0, (struct sockaddr*) &incomingAddresses[i], sizeof( peerAddress ) ) == -1 )
            {
                engine->debug->PrintString( "error sending data!\n" );
            }
        }  
    }
    else
    {
        //the client only sends packets to the server (peerAddress)
        if( sendto( socketDescriptor, (char*)data, dataLength, 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) ) == -1 )
        {
            engine->debug->PrintString( "error sending data!\n" );
        }
    }
}
Packet* NetEngineWinSocketsUDP::GetFirstPacketFromInbox()
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
vector<Packet*>* NetEngineWinSocketsUDP::GetInbox()
{
    //
    return &inbox;
}
bool NetEngineWinSocketsUDP::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return true;
    }
    return false;
}



void NetEngineWinSocketsUDP::InitClient()
{
    //
    //nothing to do
}
void NetEngineWinSocketsUDP::Connect( uint64_t target )
{
    this->target = target;

    memset( &peerAddress, 0, sizeof( peerAddress ) );
    peerAddress.sin_family = AF_INET;
    peerAddress.sin_port = htons( port );
    peerAddress.sin_addr.s_addr = target;

    if( !isConnected )
    {
        //if a client is not connected yet it sends a join request to the server (peerAddress)
        SendJoinRequest();
    }
}
void NetEngineWinSocketsUDP::Disconnect()
{
    if( isConnected )
    {
        SendDisconnectRequest();
        closesocket( socketDescriptor );
        isConnected = false;
    }
}
bool NetEngineWinSocketsUDP::GetIsConnected()
{
    //
    return isConnected;
}


void NetEngineWinSocketsUDP::InitServer()
{
    isServer = true;

    memset( &myAddress, 0, sizeof( myAddress ) );
    myAddress.sin_family = AF_INET;
    myAddress.sin_port = htons( port );
    myAddress.sin_addr.s_addr = htonl( INADDR_ANY );

    if( bind( socketDescriptor, (struct sockaddr*)&myAddress, sizeof( myAddress ) ) == -1 )
    {
        engine->debug->PrintString( "error binding socket!\n" );
    }
}
vector<uint64_t> NetEngineWinSocketsUDP::GetClientAddresses()
{
    vector<uint64_t> clients;

    for( unsigned int i = 0; i < incomingAddresses.size(); i++ )
    {    
        clients.push_back( incomingAddresses[i].sin_addr.s_addr );
    }

    return clients;
}


void* NetEngineWinSocketsUDP::SerializePacketData( Packet* packet, int* dataLength )
{
    void* data = malloc( sizeof( Packet ) + packet->dataLength );
    memcpy( data, packet, sizeof( Packet ) );
    memcpy( (char*)data + sizeof( Packet ), packet->data, packet->dataLength );
    *dataLength = sizeof( Packet ) + packet->dataLength;
    return data;
}
Packet* NetEngineWinSocketsUDP::DeSerializePacketData( void* data, int dataLength )
{
    Packet* packet = new Packet;
    memcpy( packet, data, sizeof( Packet ) );
    packet->data = malloc( packet->dataLength );
    memcpy( packet->data, (char*)data + sizeof( Packet), packet->dataLength );
    return packet;
}


void NetEngineWinSocketsUDP::SendJoinRequest()
{
    engine->debug->PrintString( "sending join request...\n" );

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_JOIN_REQUEST;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    sendto( socketDescriptor, (char*)&joinPacket, sizeof( Packet ), 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) );

    engine->debug->PrintString( "sending %i bytes...\n", dataLength );
}
void NetEngineWinSocketsUDP::SendDisconnectRequest()
{
    engine->debug->PrintString( "sending disconnect request...\n" );

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_DISCONNECT_REQUEST;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    sendto( socketDescriptor, (char*)&joinPacket, sizeof( Packet ), 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) );

    engine->debug->PrintString( "   sending %i bytes\n", dataLength );
}

void NetEngineWinSocketsUDP::SendJoinAck()
{
    engine->debug->PrintString( "sending join acknolagement...\n" );

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_JOIN_ACK;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    sendto( socketDescriptor, (char*)&joinPacket, sizeof( Packet ), 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) );

    engine->debug->PrintString( "   sending %i bytes\n", dataLength );
}
void NetEngineWinSocketsUDP::ReceivePackets()
{
    engine->debug->PrintString( "   checking socket for data...\n" );

    int receiveLength = 0;
    int c = sizeof( struct sockaddr_in );
    while( ( receiveLength = recvfrom( socketDescriptor, (char*)receiveBuffer, NET_BUFFER_SIZE, 0, (struct sockaddr *)&peerAddress, (socklen_t*)&c ) ) != -1 )
    {
        //check all packages in the ip stack

        //char str[INET_ADDRSTRLEN];
        //inet_ntop(AF_INET, &(peerAddress.sin_addr), str, INET_ADDRSTRLEN);
        //engine->debug->PrintString( "received %i bytes from %s\n", receiveLength, str );
        
        Packet* receivePacket = DeSerializePacketData( receiveBuffer, receiveLength );

        if( receivePacket->type == NET_PACKET_TYPE_JOIN_REQUEST )
        {
            //if the package is a join request
            //add the sender address to the incomingÁddresses (clients) list (ist its not already in there)
            //and immediatly send a join_Ack back to the sender
            engine->debug->PrintString( "join request\n" );
            
            bool alreadyInList = false;
            for( unsigned int i = 0; i < incomingAddresses.size(); i++ )
            {
                if( (int)incomingAddresses[i].sin_addr.s_addr == (int)peerAddress.sin_addr.s_addr )
                {
                    alreadyInList = true;
                    break;
                }
            }
            if( !alreadyInList )
            {
                incomingAddresses.push_back( peerAddress );
                SendJoinAck();
            }
        }
        else if( receivePacket->type == NET_PACKET_TYPE_JOIN_ACK && !isServer )
        {
            //if a join ack is beeing received connected to server is set to true
            //and the client does not send join requests any more
            engine->debug->PrintString( "   received join ack\n" );
            isConnected = true;
        }
        else if( receivePacket->type == NET_PACKET_TYPE_DISCONNECT_REQUEST && !isServer )
        {
            engine->debug->PrintString( "   received disconnect request\n" );

            for( unsigned int i = 0; i < incomingAddresses.size(); i++ )
            {
                if( (int)incomingAddresses[i].sin_addr.s_addr == (int)peerAddress.sin_addr.s_addr )
                {
                    incomingAddresses.erase( incomingAddresses.begin() + i );
                    break;
                }
            }
        }
        else
        {
            //the packet has nothing to do with the implementation
            //so its put in the inbox for the gameclient to grab it.
            engine->debug->PrintString( "   received regular game packet - adding to inbox...\n" );
            
            inbox.push_back( receivePacket );
        }
    }
}
void NetEngineWinSocketsUDP::Update()
{
    ReceivePackets();
}