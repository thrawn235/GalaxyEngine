//NetEngineLinuxSockets.cpp

#define debug

#include "NetEngineLinuxSockets.h"

#ifdef debug
    #include <iostream>
#endif


NetEngineLinuxSockets::NetEngineLinuxSockets()
{
    port = 1234;

    #ifdef debug
        cout<<"creating socket..."<<endl;
    #endif

    socketDescriptor = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

    #ifdef debug
        if( socketDescriptor == -1 )
        {
            cout<<"Could not create socket"<<endl;
        }
    #endif
}
NetEngineLinuxSockets::~NetEngineLinuxSockets()
{
    #ifdef debug
        cout<<"closing socket"<<endl;
    #endif

    //close( socketDescriptor );
}
void NetEngineLinuxSockets::InitClient()
{

}
void NetEngineLinuxSockets::InitServer()
{
    #ifdef debug
        cout<<"binding socket..."<<endl;
    #endif

    memset( &my_address, 0, sizeof( my_address ) );
    my_address.sin_family = AF_INET;
    my_address.sin_port = htons( port );
    my_address.sin_addr.s_addr = htonl( INADDR_ANY );

    if( bind( socketDescriptor, (struct sockaddr*)&my_address, sizeof( my_address ) ) == -1 )
    {
        #ifdef debug
            cout<<"error binding socket!"<<endl;
        #endif
    }
}
void NetEngineLinuxSockets::Send( Packet* packet, uint64_t target )
{
    packet->FixData();

}
void NetEngineLinuxSockets::SetTarget( uint64_t target )
{
    this->target = target;

    memset( &peer_address, 0, sizeof( peer_address ) );
    peer_address.sin_family = AF_INET;
    peer_address.sin_port = htons( port );
    peer_address.sin_addr.s_addr = target;
}
void NetEngineLinuxSockets::SetAddress( uint64_t address )
{
    this->address = address;
}
void NetEngineLinuxSockets::Send( Packet* packet )
{
    if ( sendto( socketDescriptor, packet->data, packet->dataLength, 0, (struct sockaddr*) &peer_address, sizeof( peer_address ) ) == -1 )
    {
        #ifdef debug
            cout<<"error sednding data!"<<endl;
        #endif
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
void NetEngineLinuxSockets::ReceivePackets()
{
    #ifdef debug
        cout<<"checking socket for data"<<endl;
    #endif
    Packet* receivePacket = new Packet;
    receivePacket->data = malloc( NET_BUFFER_SIZE );
    int receiveLength = 0;
    if( ( receiveLength = recv( socketDescriptor, receivePacket->data, NET_BUFFER_SIZE, MSG_DONTWAIT ) ) == -1 )
    {
        //free( receivePacket->data );
        delete receivePacket;
        #ifdef debug
            cout<<"no data received"<<endl;
        #endif
    }
    else
    {
        #ifdef debug
            cout<<"received "<<receiveLength<<" bytes"<<endl;
        #endif
        //realloc( receivePacket->data, receiveLength );
        receivePacket->dataLength = receiveLength;
        inbox.push_back( receivePacket );
    }
}
void NetEngineLinuxSockets::Update()
{
    ReceivePackets();
}