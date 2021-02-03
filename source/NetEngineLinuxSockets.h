//====================================
// NetEngineLinuxSockets.h
// the implementation uses linux sockets from sys/sockets.h
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
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
    int                 socketDescriptor;

public:
    //---------- Constructor / Destructor ------------
                                NetEngineLinuxSockets       ();

    //-------------------- Init ----------------------
    virtual void                Init                        ();

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
};

#endif