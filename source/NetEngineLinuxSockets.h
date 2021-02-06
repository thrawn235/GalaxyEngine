//====================================
// NetEngineLinuxSockets.h
// the implementation uses linux sockets from sys/sockets.h
// it uses UDP
//====================================

//========== include guard ===========
#ifndef NET_ENGINE_LINUX_SOCKETS
#define NET_ENGINE_LINUX_SOCKETS
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
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


class NetEngineLinuxSockets : public NetEngine
{
protected:
    vector<Packet*>     inbox;
    uint64_t            address;
    uint64_t            target;

    //Sockets:
    struct sockaddr_in  my_address, peer_address;
    int                 socketDescriptor;
    int                 port;

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

    //-------------- Network Methods -----------------
    virtual void                Send                        ( Packet* packet, uint64_t target );
    virtual void                Send                        ( Packet* packet );
    virtual Packet*             GetFirstPacketFromInbox     ();
    virtual bool                InboxEmpty                  ();
    virtual bool                InboxFull                   ();

    virtual void                ReceivePackets              ();

    virtual void                Update                      ();
};

#endif