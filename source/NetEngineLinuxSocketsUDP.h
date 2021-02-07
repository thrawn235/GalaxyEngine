//====================================
// NetEngineLinuxSocketsUDP.h
// the implementation uses linux sockets from sys/sockets.h
// this implementation uses UDP
//====================================

//========== include guard ===========
#ifndef NET_ENGINE_LINUX_SOCKETS_UDP
#define NET_ENGINE_LINUX_SOCKETS_UDP
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
//====================================

//============== defines =============
#define NET_BUFFER_SIZE 1024
//====================================

//========= galaxy includes ==========
#include "NetEngine.h"
//====================================

//======= forward declarations =======
class NetEngineLocal;
//====================================


class NetEngineLinuxSocketsUDP : public NetEngine
{
protected:
    vector<Packet*>     inbox;
    uint64_t            address;
    uint64_t            target;

    //Sockets:
    struct sockaddr_in  myAddress, peerAddress;
    int                 socketDescriptor;
    vector<sockaddr_in> incomingAddresses;
    int                 port;
    bool                isServer;
    bool                connectedToServer;
    void*               receiveBuffer;

public:
    //---------- Constructor / Destructor ------------
                                NetEngineLinuxSocketsUDP    ();
                                ~NetEngineLinuxSocketsUDP   ();

    //-------------------- Init ----------------------
    virtual void                InitClient                  ();
    virtual void                InitServer                  ();

    //------------------ Set / Get -------------------
    virtual void                SetTarget                   ( uint64_t target );
    virtual void                SetAddress                  ( uint64_t address );
    virtual unsigned int        GetNumPacketsInInbox        ();
    virtual uint64_t            GetAddress                  ();
    virtual vector<Packet*>*    GetInbox                    ();
    virtual int                 GetType                     ();

    //-------------- Network Methods -----------------
    virtual void                Send                        ( Packet* packet );
    virtual Packet*             GetFirstPacketFromInbox     ();
    virtual bool                InboxEmpty                  ();

    virtual void                Update                      ();

    //--------------- LinuxSockets only --------------
    virtual void                ReceivePackets              ();
    virtual void                SendJoinRequest             ();
    virtual void                SendJoinAck                 ();

    virtual void*               SerializePacketData         ( Packet* packet, int* dataLength );
    virtual Packet*             DeSerializePacketData       ( void* data, int dataLength );
};

#endif