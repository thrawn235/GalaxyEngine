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
    long long int       address;
    long long int       target;

public:
                                NetEngineLocal              ();
    virtual void                Init                        ();
    virtual void                Send                        ( Packet* packet, long long int target );
    virtual void                SetTarget                   ( long long int target );
    virtual void                SetAddress                  ( long long int address );
    virtual void                Send                        ( Packet* packet );
    virtual Packet*             GetFirstPacketFromInbox     ();
    virtual bool                InboxEmpty                  ();
    virtual bool                InboxFull                   ();
    virtual unsigned int        GetNumPacketsInInbox        ();
    virtual long long int       GetAddress                  ();
    virtual vector<Packet*>*    GetInbox                    ();
    virtual int                 GetType                     ();
};

#endif