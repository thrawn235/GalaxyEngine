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
    connectionType = CONNECTION_TYPE_TCP;
    isServer = false;

    #ifdef debug
        cout<<"creating socket..."<<endl;
    #endif

    if( connectionType == CONNECTION_TYPE_UDP )
    {
        #ifdef debug
            cout<<"socket type UDP..."<<endl;
        #endif
        socketDescriptor = socket( AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP );
    }
    else if( connectionType == CONNECTION_TYPE_TCP )
    {
        #ifdef debug
            cout<<"socket type TCP..."<<endl;
        #endif
        socketDescriptor = socket( AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_IP );
    }

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

    listen( socketDescriptor , 3 );
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


void NetEngineLinuxSockets::Send( Packet* packet, uint64_t target )
{
    packet->FixData();

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
    this->address = address;
}
void NetEngineLinuxSockets::Send( Packet* packet )
{
    if( connectionType == CONNECTION_TYPE_UDP )
    {
        if ( sendto( socketDescriptor, packet->data, packet->dataLength, 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) ) == -1 )
        {
            #ifdef debug
                cout<<"error sednding data!"<<endl;
            #endif
        }
    }
    else if( connectionType == CONNECTION_TYPE_TCP )
    {
        if( isServer )
        {
            for( unsigned int i = 0; i < incomingDescriptors.size(); i++ )
            {
                #ifdef debug
                    cout<<"sending..."<<endl;
                #endif
                if ( send( incomingDescriptors[i], packet->data, packet->dataLength, 0 ) == -1 )
                {
                    #ifdef debug
                        cout<<"error sednding data!"<<endl;
                    #endif
                }
            }
        }
        else
        {
            if ( send( socketDescriptor, packet->data, packet->dataLength, 0 ) == -1 )
            {
                #ifdef debug
                    cout<<"error sednding data!"<<endl;
                #endif
            }
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
void NetEngineLinuxSockets::ReceivePackets()
{
    #ifdef debug
        cout<<"checking socket for data"<<endl;
    #endif
    Packet* receivePacket = new Packet;
    receivePacket->data = malloc( NET_BUFFER_SIZE );
    int receiveLength = 0;
    receiveLength = recv( socketDescriptor, receivePacket->data, NET_BUFFER_SIZE, MSG_DONTWAIT);
    if( receiveLength == -1 )
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
    if( isServer )
    {
        ListenForNewConnections();
    }
    else
    {
        if( !connectedToServer )
        {
            if( connectionType == CONNECTION_TYPE_TCP )
            {
                ConnectToServer();
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