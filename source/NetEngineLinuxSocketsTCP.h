//====================================
// NetEngineLinuxSocketsTCP.h
// the implementation uses linux sockets from sys/sockets.h
// this implementation uses TCP
//====================================

//========== include guard ===========
#ifndef NET_ENGINE_LINUX_SOCKETS_TCP
#define NET_ENGINE_LINUX_SOCKETS_TCP
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


class NetEngineLinuxSocketsTCP : public NetEngine
{
protected:
    vector<Packet*>     inbox;
    uint64_t            address;
    uint64_t            target;

    //Sockets:
    struct sockaddr_in  myAddress, peerAddress;
    int                 socketDescriptor;
    vector<int>         incomingDescriptors;
    int                 port;
    bool                isServer;
    bool                isConnected;
    void*               receiveBuffer;

public:
    //---------- Constructor / Destructor ------------
                                NetEngineLinuxSocketsTCP    ();
                                ~NetEngineLinuxSocketsTCP   ();

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
    virtual void                ListenForNewConnections     ();

    virtual void*               SerializePacketData         ( Packet* packet, int* dataLength );
    virtual vector<Packet*>     DeSerializePacketData       ( void* data, int dataLength );
};

#endif