//====================================
// NetEngineLinuxSockets.h
// the implementation uses linux sockets from sys/sockets.h
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

#define CONNECTION_TYPE_UDP     1
#define CONNECTION_TYPE_TCP     2
//====================================

//========= galaxy includes ==========
#include "NetEngine.h"
//====================================

//======= forward declarations =======
class NetEngineLocal;
//====================================


class NetEngineLinuxSockets : public NetEngine
{
protected:
    vector<Packet*>     inbox;
    uint64_t            address;
    uint64_t            target;

    //Sockets:
    int                 connectionType;              //UDP or TCP
    struct sockaddr_in  myAddress, peerAddress;
    int                 socketDescriptor;
    vector<int>         incomingDescriptors;
    int                 port;
    bool                isServer;
    bool                connectedToServer;
    void*               receiveBuffer;

public:
    //---------- Constructor / Destructor ------------
                                NetEngineLinuxSockets       ();
                                ~NetEngineLinuxSockets      ();

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

    //----------------- Communication-----------------
    virtual vector<string>      GetAllValueNames            ();
    virtual uint64_t            GetNumericalValue           ( string valueName );
    virtual void                SetNumericalValue           ( string valueName, uint64_t value );

    //-------------- Network Methods -----------------
    virtual void                Send                        ( Packet* packet );
    virtual Packet*             GetFirstPacketFromInbox     ();
    virtual bool                InboxEmpty                  ();
    virtual bool                InboxFull                   ();

    virtual void                Update                      ();

    //--------------- LinuxSockets only --------------
    virtual void                ReceivePackets              ();

    virtual void                CreateTCPSocket             ();
    virtual void                CreateUDPSocket             ();

    virtual void                ListenForNewConnections     ();
    virtual void                ConnectToServer             ();

    virtual void*               SerializePacketData         ( Packet* packet, int* dataLength );
    virtual Packet*             DeSerializePacketData       ( void* data, int dataLength );
    virtual void                SendUDP                     ( void* data, int dataLength );
    virtual void                SendTCP                     ( void* data, int dataLength );
};

#endif