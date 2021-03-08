//====================================
// NetEngineDummy.h
// dummy implementation of NetEngine
//====================================

//========== include guard ===========
#ifndef NET_ENGINE_DUMMY
#define NET_ENGINE_DUMMY
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
using namespace std;
//====================================

//============== defines =============
//====================================

//========= galaxy includes ==========
#include "NetEngine.h"
//====================================

//======= forward declarations =======
class NetEngineLocal;
//====================================


class NetEngineDummy : public NetEngine
{
protected:

public:
    //---------- Constructor / Destructor ------------
                                NetEngineDummy              ( GameEngine* engine );
                                ~NetEngineDummy             ();

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
    virtual void                Connect                     ( uint64_t target );
    virtual void                Disconnect                  ();
    virtual bool                GetIsConnected              ();

    //-------------------- Server --------------------
    virtual void                ConfigureAsServer           ();
    virtual vector<uint64_t>    GetClientAddresses          ();

    virtual void                Update                      ();
};

#endif