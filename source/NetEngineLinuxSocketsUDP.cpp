//NetEngineLinuxSocketsUDP.cpp

#define debug

#include "NetEngineLinuxSocketsUDP.h"

#ifdef debug
    #include <iostream>
#endif


NetEngineLinuxSocketsUDP::NetEngineLinuxSocketsUDP()
{
    port = 1234;
    connectedToServer = false;
    isServer = false;
    receiveBuffer = malloc( NET_BUFFER_SIZE );

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
NetEngineLinuxSocketsUDP::~NetEngineLinuxSocketsUDP()
{
    #ifdef debug
        cout<<"closing socket"<<endl;
    #endif

    close( socketDescriptor );
}


void NetEngineLinuxSocketsUDP::InitClient()
{
    //
    //nothing to do
}
void NetEngineLinuxSocketsUDP::InitServer()
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
}


void NetEngineLinuxSocketsUDP::SetTarget( uint64_t target )
{
    this->target = target;

    memset( &peerAddress, 0, sizeof( peerAddress ) );
    peerAddress.sin_family = AF_INET;
    peerAddress.sin_port = htons( port );
    peerAddress.sin_addr.s_addr = target;
}
void NetEngineLinuxSocketsUDP::SetAddress( uint64_t address )
{
    //
    this->address = address;
}
void* NetEngineLinuxSocketsUDP::SerializePacketData( Packet* packet, int* dataLength )
{
    void* data = malloc( sizeof( Packet ) + packet->dataLength );
    memcpy( data, packet, sizeof( Packet ) );
    memcpy( (char*)data + sizeof( Packet ), packet->data, packet->dataLength );
    *dataLength = sizeof( Packet ) + packet->dataLength;
    return data;
}
Packet* NetEngineLinuxSocketsUDP::DeSerializePacketData( void* data, int dataLength )
{
    Packet* packet = new Packet;
    memcpy( packet, data, sizeof( Packet ) );
    packet->data = malloc( packet->dataLength );
    memcpy( packet->data, (char*)data + sizeof( Packet), packet->dataLength );
    return packet;
}
void NetEngineLinuxSocketsUDP::Send( Packet* packet )
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
        //the server sends packages to all clients
        for( unsigned int i = 0; i < incomingAddresses.size(); i++ )
        {
            if( sendto( socketDescriptor, data, dataLength, 0, (struct sockaddr*) &incomingAddresses[i], sizeof( peerAddress ) ) == -1 )
            {
                #ifdef debug
                    cout<<"error sending data!"<<endl;
                #endif
            }
        }  
    }
    else
    {
        //the client only sends packets to the server (peerAddress)
        if( sendto( socketDescriptor, data, dataLength, 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) ) == -1 )
        {
            #ifdef debug
                cout<<"error sending data!"<<endl;
            #endif
        }
    }
}


Packet* NetEngineLinuxSocketsUDP::GetFirstPacketFromInbox()
{
    if( inbox.size() > 0 )
    {
        Packet* tmp = inbox[0];
        inbox.erase( inbox.begin() );
        return tmp;
    }
    return NULL;
}
bool NetEngineLinuxSocketsUDP::InboxEmpty()
{
    if( inbox.size() == 0 )
    {
        return true;
    }
    return false;
}
unsigned int NetEngineLinuxSocketsUDP::GetNumPacketsInInbox()
{
    //
    return inbox.size();
}
uint64_t NetEngineLinuxSocketsUDP::GetAddress()
{
    //
    return address;
}
vector<Packet*>* NetEngineLinuxSocketsUDP::GetInbox()
{
    //
    return &inbox;
}
int NetEngineLinuxSocketsUDP::GetType()
{
    //
    return NET_TYPE_LINUX_SOCKETS_UDP;
}
void NetEngineLinuxSocketsUDP::SendJoinRequest()
{
    #ifdef debug
        cout<<"sending join request..."<<endl;
    #endif

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_JOIN_REQUEST;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    sendto( socketDescriptor, &joinPacket, sizeof( Packet ), 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) );

    #ifdef debug
        cout<<"   sending "<<dataLength<<" bytes"<<endl;
    #endif
}
void NetEngineLinuxSocketsUDP::SendJoinAck()
{
    #ifdef debug
        cout<<"sending join acknolagement..."<<endl;
    #endif

    Packet joinPacket;
    joinPacket.type = NET_PACKET_TYPE_JOIN_ACK;
    joinPacket.dataLength = 0;
    int dataLength = 0;

    sendto( socketDescriptor, &joinPacket, sizeof( Packet ), 0, (struct sockaddr*) &peerAddress, sizeof( peerAddress ) );

    #ifdef debug
        cout<<"   sending "<<dataLength<<" bytes"<<endl;
    #endif
}
void NetEngineLinuxSocketsUDP::ReceivePackets()
{
    #ifdef debug
        cout<<"checking socket for data"<<endl;
    #endif
    int receiveLength = 0;
    int c = sizeof( struct sockaddr_in );
    while( ( receiveLength = recvfrom( socketDescriptor, receiveBuffer, NET_BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&peerAddress, (socklen_t*)&c ) ) != -1 )
    {
        //check all packages in the ip stack

        #ifdef debug
            char str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(peerAddress.sin_addr), str, INET_ADDRSTRLEN);
            cout<<"received "<<receiveLength<<" bytes from "<<str<<endl;
        #endif
        
        Packet* receivePacket = DeSerializePacketData( receiveBuffer, receiveLength );

        if( receivePacket->type == NET_PACKET_TYPE_JOIN_REQUEST )
        {
            //if the package is a join request
            //add the sender address to the incomingÁddresses (clients) list (ist its not already in there)
            //and immediatly send a join_Ack back to the sender
            #ifdef debug
                cout<<"   join request"<<endl;
            #endif
            
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
            #ifdef debug
                cout<<"   received Join Ack"<<endl;
            #endif
            connectedToServer = true;
        }
        else
        {
            //the packet has nothing to do with the implementation
            //so its put in the inbox for the gameclient to grab it.
            inbox.push_back( receivePacket );
        }
    }
    if( receiveLength == -1 )
    {
        #ifdef debug
            cout<<"no data received"<<endl;
        #endif
    }
}
void NetEngineLinuxSocketsUDP::Update()
{
    if( !isServer )
    {
        if( !connectedToServer )
        {
            //if a client is not connected yet it sends a join request to the server (peerAddress)
            SendJoinRequest();
        }
    }
    ReceivePackets();
}