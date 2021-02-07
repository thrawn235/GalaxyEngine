//NetEngineLinuxSockets.cpp

#define debug

#include "NetEngineLinuxSockets.h"

#ifdef debug
    #include <iostream>
#endif


NetEngineLinuxSockets::NetEngineLinuxSockets()
{
    port = 1234;
    connectedToServer = false;
    isServer = false;
    receiveBuffer = malloc( NET_BUFFER_SIZE );

    connectionType = CONNECTION_TYPE_UDP;

    if( connectionType == CONNECTION_TYPE_UDP )
    {
        CreateUDPSocket();
    }
    else if( connectionType == CONNECTION_TYPE_TCP )
    {
        CreateTCPSocket();
    }
}
NetEngineLinuxSockets::~NetEngineLinuxSockets()
{
    #ifdef debug
        cout<<"closing socket"<<endl;
    #endif

    close( socketDescriptor );
}

void NetEngineLinuxSockets::CreateTCPSocket()
{
    #ifdef debug
        cout<<"creating TCP Socket..."<<endl;
    #endif
    socketDescriptor = socket( AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_IP );
    if( socketDescriptor == -1 )
    {
        #ifdef debug
            cout<<"could not create Socket..."<<endl;
        #endif
    }
}
void NetEngineLinuxSockets::CreateUDPSocket()
{
    #ifdef debug
        cout<<"creating UDP Socket..."<<endl;
    #endif
    socketDescriptor = socket( AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP );
    if( socketDescriptor == -1 )
    {
        #ifdef debug
            cout<<"could not create Socket..."<<endl;
        #endif
    }
}

void NetEngineLinuxSockets::InitClient()
{
    
}
void NetEngineLinuxSockets::InitServer()
{
    isServer = true;

    #ifdef debug
        cout<<"binding socket..."<<endl;
    #endif

    memset( &myAddress, 0, sizeof( myAddress ) );
    myAddress.sin_family = AF_INET;
    myAddress.sin_port = htons( port );
    myAddress.sin_addr.s_addr = htonl( INADDR_ANY );

    if( bind( socketDescriptor, (struct sockaddr*)&myAddress, sizeof( myAddress ) ) == -1 )
    {
        #ifdef debug
            cout<<"error binding socket!"<<endl;
        #endif
    }

    if( connectionType == CONNECTION_TYPE_TCP )
    {
        listen( socketDescriptor , 3 );
    }
}


vector<string> NetEngineLinuxSockets::GetAllValueNames()
{
    vector<string> values;
    values.push_back( "port" );
    values.push_back( "connectionType" );
    return values;
}
uint64_t NetEngineLinuxSockets::GetNumericalValue( string valueName )
{
    if( valueName == "port" )
    {
        return port;
    }
    if( valueName == "connectionType" )
    {
        return 0;
    }
    return 0;
}
void NetEngineLinuxSockets::SetNumericalValue( string valueName, uint64_t value )
{
    if( valueName == "port" )
    {
        port = value;
    }
    if( valueName == "connectionType" )
    {
    
    }
}


void NetEngineLinuxSockets::SetTarget( uint64_t target )
{
    this->target = target;

    memset( &peerAddress, 0, sizeof( peerAddress ) );
    peerAddress.sin_family = AF_INET;
    peerAddress.sin_port = htons( port );
    peerAddress.sin_addr.s_addr = target;
}
void NetEngineLinuxSockets::SetAddress( uint64_t address )
{
    //
    this->address = address;
}
void* NetEngineLinuxSockets::SerializePacketData( Packet* packet, int* dataLength )
{
    void* data = malloc( sizeof( Packet ) + packet->dataLength );
    memcpy( data, packet, sizeof( Packet ) );
    memcpy( data + sizeof( Packet ), packet->data, packet->dataLength );
    *dataLength = sizeof( Packet ) + packet->dataLength;
    return data;
}
Packet* NetEngineLinuxSockets::DeSerializePacketData( void* data, int dataLength )
{
    Packet* packet = new Packet;
    memcpy( packet, data, sizeof( Packet ) );
    packet->data = malloc( packet->dataLength );
    memcpy( packet->data, data + sizeof( Packet), packet->dataLength );
    return packet;
}
void NetEngineLinuxSockets::Send( Packet* packet )
{
    #ifdef debug
        cout<<"sending..."<<endl;
    #endif
    int dataLength = 0;
    void* data = SerializePacketData( packet, &dataLength );
    #ifdef debug
        cout<<"   "<<dataLength<<" bytes..."<<endl;
    #endif
    if( connectionType == CONNECTION_TYPE_UDP )
    {
        SendUDP( data, dataLength );
    }
    else if( connectionType == CONNECTION_TYPE_TCP )
    {
        SendTCP( data, dataLength );
    }    
}
void NetEngineLinuxSockets::SendUDP( void* data, int dataLength )
{
    if ( sendto( socketDescriptor, data, dataLength, 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) ) == -1 )
    {
        #ifdef debug
            cout<<"error sending data!"<<endl;
        #endif
    }
}
void NetEngineLinuxSockets::SendTCP( void* data, int dataLength )
{
    if( isServer )
    {
        for( unsigned int i = 0; i < incomingDescriptors.size(); i++ )
        {
            
            if ( send( incomingDescriptors[i], data, dataLength, 0 ) == -1 )
            {
                #ifdef debug
                    cout<<"error sednding data!"<<endl;
                #endif
            }
        }
    }
    else
    {
        if ( send( socketDescriptor, data, dataLength, 0 ) == -1 )
        {
            #ifdef debug
                cout<<"error sednding data!"<<endl;
            #endif
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
    //
    return false;
}
unsigned int NetEngineLinuxSockets::GetNumPacketsInInbox()
{
    //
    return inbox.size();
}
uint64_t NetEngineLinuxSockets::GetAddress()
{
    //
    return address;
}
vector<Packet*>* NetEngineLinuxSockets::GetInbox()
{
    //
    return &inbox;
}
int NetEngineLinuxSockets::GetType()
{
    //
    return NET_TYPE_LINUX_SOCKETS;
}
void NetEngineLinuxSockets::ReceivePackets()
{
    #ifdef debug
        cout<<"checking socket for data"<<endl;
    #endif
    int receiveLength = 0;
    int c = sizeof( struct sockaddr_in );
    while( ( receiveLength = recvfrom( socketDescriptor, receiveBuffer, NET_BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&peerAddress, (socklen_t*)&c ) ) != -1 )
    {
        #ifdef debug
            char str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(peerAddress.sin_addr), str, INET_ADDRSTRLEN);
            cout<<"received "<<receiveLength<<" bytes from "<<str<<endl;
        #endif
        if( connectionType == CONNECTION_TYPE_UDP )
        {
            inbox.push_back( DeSerializePacketData( receiveBuffer, receiveLength ) );
        }
    }
    if( receiveLength == -1 )
    {
        #ifdef debug
            cout<<"no data received"<<endl;
        #endif
    }
}
void NetEngineLinuxSockets::Update()
{
    if( connectionType == CONNECTION_TYPE_TCP )
    {
        if( isServer )
        {
            ListenForNewConnections();
        }
        else
        {
            if( !connectedToServer )
            {
                ConnectToServer();
            }
        }
    }
    if( connectionType == CONNECTION_TYPE_UDP )
    {
        if( !isServer )
        {
            if( !connectedToServer )
            {
                #ifdef debug
                    cout<<"sending join request..."<<endl;
                #endif
                Packet joinPacket;
                joinPacket.type = NET_PACKET_TYPE_JOIN_REQUEST;
                joinPacket.dataLength = 0;
                int dataLength = 0;
                SendUDP( SerializePacketData( &joinPacket, &dataLength ), dataLength );
                #ifdef debug
                    cout<<"   sending "<<dataLength<<" bytes"<<endl;
                #endif
            }
        }
    }
    ReceivePackets();
}
void NetEngineLinuxSockets::ListenForNewConnections()
{
    #ifdef debug
        cout<<"listening on socket..."<<endl;
    #endif
    

    int c = sizeof( struct sockaddr_in );
    int new_socket = accept4( socketDescriptor, (struct sockaddr *)&peerAddress, (socklen_t*)&c, SOCK_NONBLOCK );
    if ( new_socket < 0 )
    {
        #ifdef debug
            cout<<"no peer is trying to connect!"<<endl;
        #endif
    }
    else
    {
        #ifdef debug
            cout<<"connection attempt detected!"<<endl;
            char *client_ip = inet_ntoa(peerAddress.sin_addr);
            cout<<"   peer ip: "<<client_ip<<endl;
            incomingDescriptors.push_back( new_socket );
        #endif
    }
}
void NetEngineLinuxSockets::ConnectToServer()
{
    #ifdef debug
        cout<<"establishing connection..."<<endl;
    #endif
    if ( connect( socketDescriptor , (struct sockaddr*)&peerAddress , sizeof( peerAddress ) ) < 0 )
    {
        #ifdef debug
            cout<<"connection error!"<<endl;
        #endif
    }
    else
    {
        #ifdef debug
            cout<<"connection established!"<<endl;
        #endif
        connectedToServer = true;
    }   
}