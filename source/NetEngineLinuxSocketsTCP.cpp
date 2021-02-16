//NetEngineLinuxSocketsTCP.cpp

#include "NetEngineLinuxSocketsTCP.h"
#include "GameEngine.h"


NetEngineLinuxSocketsTCP::NetEngineLinuxSocketsTCP( GameEngine* engine ) : NetEngine( engine ) 
{
    port = 1234;
    isConnected = false;
    isServer = false;
    receiveBuffer = malloc( NET_BUFFER_SIZE );

    engine->debug->PrintString( "creating TCP Socket...\n" );

    socketDescriptor = socket( AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_IP );
    if( socketDescriptor == -1 )
    {
        engine->debug->PrintString( "could not create Socket!\n" );
        engine->Quit();
    }
}
NetEngineLinuxSocketsTCP::~NetEngineLinuxSocketsTCP()
{
    engine->debug->PrintString( "closing socket...\n" );
    close( socketDescriptor );
}

void NetEngineLinuxSocketsTCP::SetAddress( uint64_t address )
{
    //
    this->address = address;
}
uint64_t NetEngineLinuxSocketsTCP::GetAddress()
{
    //
    return address;
}
int NetEngineLinuxSocketsTCP::GetType()
{
    //
    return NET_TYPE_LINUX_SOCKETS_TCP;
}
unsigned int NetEngineLinuxSocketsTCP::GetNumPacketsInInbox()
{
    //
    return inbox.size();
}
bool NetEngineLinuxSocketsTCP::GetIsServer()
{
    //
    return isServer;
}
void NetEngineLinuxSocketsTCP::Send( Packet* packet )
{
    engine->debug->PrintString( "sending...\n" );
    int dataLength = 0;
    void* data = SerializePacketData( packet, &dataLength );
    engine->debug->PrintString( "   %i bytes\n", dataLength );
    
    if( isServer )
    {
        for( unsigned int i = 0; i < incomingDescriptors.size(); i++ )
        {
            if ( send( incomingDescriptors[i], data, dataLength, 0 ) == -1 )
            {
                engine->debug->PrintString( "error sending data\n" );
            }
        }
    }
    else
    {
        engine->debug->PrintString( "client sending...\n" );
        if ( send( socketDescriptor, data, dataLength, 0 ) == -1 )
        {
            engine->debug->PrintString( "error sending data\n" );
        }
    } 
}
Packet* NetEngineLinuxSocketsTCP::GetFirstPacketFromInbox()
{
    if( inbox.size() > 0 )
    {
        Packet* tmp = inbox[0];
        inbox.erase( inbox.begin() );
        return tmp;
    }
    return NULL;
}
vector<Packet*>* NetEngineLinuxSocketsTCP::GetInbox()
{
    //
    return &inbox;
}
bool NetEngineLinuxSocketsTCP::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return true;
    }
    return false;
}





void NetEngineLinuxSocketsTCP::InitClient()
{
    
}
void NetEngineLinuxSocketsTCP::Connect( uint64_t target )
{
    this->target = target;

    memset( &peerAddress, 0, sizeof( peerAddress ) );
    peerAddress.sin_family = AF_INET;
    peerAddress.sin_port = htons( port );
    peerAddress.sin_addr.s_addr = target;


    engine->debug->PrintString( "establishing connection...\n" );
    if ( connect( socketDescriptor, (struct sockaddr*)&peerAddress , sizeof( peerAddress ) ) < 0 )
    {
        engine->debug->PrintString( "connection error!\n" );
    }
    else
    {
        engine->debug->PrintString( "connection established\n" );
        isConnected = true;
    }   
}
void NetEngineLinuxSocketsTCP::Disconnect()
{
    if( isConnected )
    {
        close( socketDescriptor );
        isConnected = false;
    }
}
bool NetEngineLinuxSocketsTCP::GetIsConnected()
{
    //
    return isConnected;
}




void NetEngineLinuxSocketsTCP::InitServer()
{
    isServer = true;

    engine->debug->PrintString( "binding socket...\n" );

    memset( &myAddress, 0, sizeof( myAddress ) );
    myAddress.sin_family = AF_INET;
    myAddress.sin_port = htons( port );
    myAddress.sin_addr.s_addr = htonl( INADDR_ANY );

    if( bind( socketDescriptor, (struct sockaddr*)&myAddress, sizeof( myAddress ) ) == -1 )
    {
        engine->debug->PrintString( "error binding socket!\n" );
    }

    listen( socketDescriptor , 3 );
}
vector<uint64_t> NetEngineLinuxSocketsTCP::GetClientAddresses()
{
    vector<uint64_t> clients;

    for( unsigned int i = 0; i < incomingDescriptors.size(); i++ )
    {
        int c = sizeof( struct sockaddr_in );
        sockaddr_in address;
        getpeername( incomingDescriptors[i], (struct sockaddr *)&address, (socklen_t*)&c );
        clients.push_back( address.sin_addr.s_addr );
    }
    return clients;
}


void* NetEngineLinuxSocketsTCP::SerializePacketData( Packet* packet, int* dataLength )
{
    void* data = malloc( sizeof( Packet ) + packet->dataLength + sizeof( uint16_t ) );
    *(uint16_t*)data = (uint16_t)sizeof( Packet ) + packet->dataLength;
    memcpy( (char*)data + sizeof( uint16_t ) , packet, sizeof( Packet ) );
    memcpy( (char*)data + sizeof( uint16_t ) + sizeof( Packet ), packet->data, packet->dataLength );
    *dataLength = sizeof( Packet ) + sizeof( uint16_t ) + packet->dataLength;

    engine->debug->PrintString( "serializing packet...\n" );
    engine->debug->PrintString( "   allocating %i bytes \n", sizeof( Packet ) + packet->dataLength + sizeof( uint16_t ) );
    engine->debug->PrintString( "   writing %i to the beginning \n", (uint16_t)sizeof( Packet ) + packet->dataLength );

    return data;
}
vector<Packet*> NetEngineLinuxSocketsTCP::DeSerializePacketData( void* data, int dataLength )
{
    engine->debug->PrintString( "De-serializing packet...\n" );
    engine->debug->PrintString( "   dataLegnth %i\n", dataLength );

    vector<Packet*> packets;

    int i = 0;
    while( i < dataLength )
    {
        int packetSize = *(uint16_t*)((char*)data + i);

        engine->debug->PrintString( "      packetSize %i\n", packetSize );
        
        Packet* packet = new Packet;
        memcpy( packet, (char*)data + i + sizeof( uint16_t ), sizeof( Packet ) );
        packet->data = malloc( packet->dataLength );
        memcpy( packet->data, (char*)data + i + sizeof( uint16_t ) + sizeof( Packet ), packet->dataLength );

        packets.push_back( packet );
        i = i + packetSize + sizeof( uint16_t );
    }
    return packets;
}


void NetEngineLinuxSocketsTCP::ReceivePackets()
{
    engine->debug->PrintString( "checking socket for data...\n" );
    if( isServer )
    {
        for( unsigned int i = 0; i < incomingDescriptors.size(); i++ )
        {
            //check all packets from all open sockets (incomingDescriptors)
            int receiveLength = 0;
            int c = sizeof( struct sockaddr_in );
            while( ( receiveLength = recvfrom( incomingDescriptors[i], receiveBuffer, NET_BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&peerAddress, (socklen_t*)&c ) ) != -1 )
            {
                char str[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(peerAddress.sin_addr), str, INET_ADDRSTRLEN);
                engine->debug->PrintString( "received %i bytes from %s\n", receiveLength, str );
                
                vector<Packet*> packets = DeSerializePacketData( receiveBuffer, receiveLength );
                for( unsigned int i = 0; i < packets.size(); i++ )
                {
                    engine->debug->PrintString( "adding packet to inbox...\n" );
                    inbox.push_back( packets[i] );
                }
            }
            if( receiveLength == -1 )
            {
                engine->debug->PrintString( "no data received\n" );
            }

            i++;
        }
    }
    else
    {
        int receiveLength = 0;
        int c = sizeof( struct sockaddr_in );
        while( ( receiveLength = recvfrom( socketDescriptor, receiveBuffer, NET_BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&peerAddress, (socklen_t*)&c ) ) != -1 )
        {
            char str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(peerAddress.sin_addr), str, INET_ADDRSTRLEN);
            cout<<"received "<<receiveLength<<" bytes from "<<str<<endl;
            engine->debug->PrintString( "received %i bytes from %s\n", receiveLength, str );
            
            vector<Packet*> packets = DeSerializePacketData( receiveBuffer, receiveLength );
            for( unsigned int i = 0; i < packets.size(); i++ )
            {
                engine->debug->PrintString( "adding packet to inbox\n" );
                inbox.push_back( packets[i] );
            }
        }
        if( receiveLength == -1 )
        {
            engine->debug->PrintString( "no data received\n" );
        }
    }
}
void NetEngineLinuxSocketsTCP::Update()
{
    if( isServer )
    {
        ListenForNewConnections();
    }

    ReceivePackets();
}
void NetEngineLinuxSocketsTCP::ListenForNewConnections()
{
    engine->debug->PrintString( "listening on socket...\n" );
    

    int c = sizeof( struct sockaddr_in );
    int new_socket = accept4( socketDescriptor, (struct sockaddr *)&peerAddress, (socklen_t*)&c, SOCK_NONBLOCK );
    if ( new_socket < 0 )
    {
        engine->debug->PrintString( "no peer is trying to connect\n" );
    }
    else
    {
        engine->debug->PrintString( "connection attempt detected\n" );
        char *client_ip = inet_ntoa(peerAddress.sin_addr);
        engine->debug->PrintString( "   peer ip %s\n", client_ip );
        incomingDescriptors.push_back( new_socket );
    }
}