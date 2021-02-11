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
    bool                isConnected;
    void*               receiveBuffer;

public:
    //---------- Constructor / Destructor ------------
                                NetEngineLinuxSocketsUDP    ();
                                ~NetEngineLinuxSocketsUDP   ();

    //-------------- Network Methods -----------------
    virtual void                SetAddress                  ( uint64_t address );
    virtual uint64_t            GetAddress                  ();
    virtual int                 GetType                     ();                         //Get the Type of the Net Implementation (ex. local buffer of ethernet )
    virtual unsigned int        GetNumPacketsInInbox        ();
    virtual bool                GetIsServer                 ();
    virtual void                Send                        ( Packet* packet );
    virtual Packet*             GetFirstPacketFromInbox     ();
    virtual vector<Packet*>*    GetInbox                    ();
    virtual bool                InboxEmpty                  ();

    //-------------------- Client --------------------
    virtual void                InitClient                  ();
    virtual void                Connect                     ( uint64_t target );
    virtual void                Disconnect                  ();
    virtual bool                GetIsConnected              ();

    //-------------------- Server --------------------
    virtual void                InitServer                  ();
    virtual vector<uint64_t>    GetClientAddresses          ();

    virtual void                Update                      ();

    //--------------- LinuxSockets only --------------
    virtual void                ReceivePackets              ();
    virtual void                SendJoinRequest             ();
    virtual void                SendDisconnectRequest       ();
    virtual void                SendJoinAck                 ();

    virtual void*               SerializePacketData         ( Packet* packet, int* dataLength );
    virtual Packet*             DeSerializePacketData       ( void* data, int dataLength );
};

#endif