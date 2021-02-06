//====================================
// NetEngineLocal.h
// the Gameserver does all the Game Logic and sends the current state to the client(s)
//====================================

//========== include guard ===========
#ifndef NETENGINELOCAL
#define NETENGINELOCAL
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "NetEngine.h"
//====================================

//======= forward declarations =======
class NetEngineLocal;
//====================================


class NetEngineLocal : public NetEngine
{
protected:
    vector<Packet*>     inbox;
    uint64_t            address;
    uint64_t            target;

public:
                                NetEngineLocal              ();
    
    //-------------------- Init ----------------------
    virtual void                InitClient                  ();
    virtual void                InitServer                  ();

    //------------------ Set / Get -------------------
    virtual void                SetTarget                   ( uint64_t target );
    virtual void                SetAddress                  ( uint64_t address );
    virtual Packet*             GetFirstPacketFromInbox     ();
    virtual void                Send                        ( Packet* packet, uint64_t target );
    virtual unsigned int        GetNumPacketsInInbox        ();
    virtual uint64_t            GetAddress                  ();
    virtual vector<Packet*>*    GetInbox                    ();
    virtual int                 GetType                     ();
    virtual void                Send                        ( Packet* packet );
    
    //----------------- Communication-----------------
    virtual vector<string>  GetAllValueNames                ();
    virtual uint64_t        GetNumericalValue               ( string valueName );
    virtual void            SetNumericalValue               ( string valueName, uint64_t value );

    //-------------- Network Methods -----------------
    virtual bool                InboxEmpty                  ();
    virtual bool                InboxFull                   ();

    virtual void                ReceivePackets              ();

    virtual void                Update                      ();
};

#endif