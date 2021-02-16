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
    bool                isServer;
    bool                isConnected;

public:
                                NetEngineLocal              ( GameEngine* engine );
    
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


    virtual void                Update                      ();                         //runs in every game loop
};

#endif