//NetEngineLinuxSocketsTCP.cpp

#define debug

#include "NetEngineLinuxSocketsTCP.h"

#ifdef debug
    #include <iostream>
#endif


NetEngineLinuxSocketsTCP::NetEngineLinuxSocketsTCP()
{
    port = 1234;
    isConnected = false;
    isServer = false;
    receiveBuffer = malloc( NET_BUFFER_SIZE );

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
NetEngineLinuxSocketsTCP::~NetEngineLinuxSocketsTCP()
{
    #ifdef debug
        cout<<"closing socket"<<endl;
    #endif

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
    #ifdef debug
        cout<<"sending..."<<endl;
    #endif
    int dataLength = 0;
    void* data = SerializePacketData( packet, &dataLength );
    #ifdef debug
        cout<<"   "<<dataLength<<" bytes..."<<endl;
    #endif
    
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
        #ifdef debug
            cout<<"   client sending..."<<endl;
        #endif
        if ( send( socketDescriptor, data, dataLength, 0 ) == -1 )
        {
            #ifdef debug
                cout<<"error sednding data!"<<endl;
            #endif
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


    #ifdef debug
        cout<<"establishing connection..."<<endl;
    #endif
    if ( connect( socketDescriptor, (struct sockaddr*)&peerAddress , sizeof( peerAddress ) ) < 0 )
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

    #ifdef debug
        cout<<"serializing packet..."<<endl;
        cout<<"   allocating "<<sizeof( Packet ) + packet->dataLength + sizeof( uint16_t )<<" bytes"<<endl;
        cout<<"   writing "<<(uint16_t)sizeof( Packet ) + packet->dataLength<<" to the beginning"<<endl;
    #endif

    return data;
}
vector<Packet*> NetEngineLinuxSocketsTCP::DeSerializePacketData( void* data, int dataLength )
{
    #ifdef debug
        cout<<"De-serializing packet..."<<endl;
        cout<<"   dataLength "<<dataLength<<endl;
    #endif

    vector<Packet*> packets;

    int i = 0;
    while( i < dataLength )
    {
        int packetSize = *(uint16_t*)((char*)data + i);

        #ifdef debug
            cout<<"      packetSize "<<packetSize<<endl;
        #endif
        
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
    #ifdef debug
        cout<<"checking socket for data"<<endl;
    #endif
    if( isServer )
    {
        for( unsigned int i = 0; i < incomingDescriptors.size(); i++ )
        {
            //check all packets from all open sockets (incomingDescriptors)
            int receiveLength = 0;
            int c = sizeof( struct sockaddr_in );
            while( ( receiveLength = recvfrom( incomingDescriptors[i], receiveBuffer, NET_BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&peerAddress, (socklen_t*)&c ) ) != -1 )
            {
                #ifdef debug
                    char str[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &(peerAddress.sin_addr), str, INET_ADDRSTRLEN);
                    cout<<"received "<<receiveLength<<" bytes from "<<str<<endl;
                #endif
                
                vector<Packet*> packets = DeSerializePacketData( receiveBuffer, receiveLength );
                for( unsigned int i = 0; i < packets.size(); i++ )
                {
                    #ifdef debug
                        cout<<"   adding packet to inbox"<<endl;
                    #endif
                    inbox.push_back( packets[i] );
                }
            }
            if( receiveLength == -1 )
            {
                #ifdef debug
                    cout<<"no data received"<<endl;
                #endif
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
            #ifdef debug
                char str[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(peerAddress.sin_addr), str, INET_ADDRSTRLEN);
                cout<<"received "<<receiveLength<<" bytes from "<<str<<endl;
            #endif
            
            vector<Packet*> packets = DeSerializePacketData( receiveBuffer, receiveLength );
            for( unsigned int i = 0; i < packets.size(); i++ )
            {
                #ifdef debug
                    cout<<"   adding packet to inbox"<<endl;
                #endif
                inbox.push_back( packets[i] );
            }
        }
        if( receiveLength == -1 )
        {
            #ifdef debug
                cout<<"no data received"<<endl;
            #endif
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