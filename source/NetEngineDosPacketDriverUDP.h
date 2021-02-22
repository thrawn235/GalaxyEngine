//====================================
// NetEngineDosPacketDriverUDP.h
// the implementation uses direct Packet Driver Acces and UDP
// al lot of stuff will have to be implemented manually
//====================================

//========== include guard ===========
#ifndef NET_ENGINE_DOS_PACKET_DRIVER_UDP
#define NET_ENGINE_DOS_PACKET_DRIVER_UDP
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
using namespace std;
//====================================

//============== defines =============
#define NET_BUFFER_SIZE 1024
//====================================

//========= galaxy includes ==========
#include "NetEngine.h"
//====================================

//======= forward declarations =======
//====================================


class NetEngineDosPacketDriverUDP : public NetEngine
{
protected:
    vector<Packet*>     inbox;
    uint64_t            address;
    uint64_t            target;

    int                 port;
    bool                isServer;
    bool                isConnected;
    void*               receiveBuffer;

public:
    //---------- Constructor / Destructor ------------
                                NetEngineDosPacketDriverUDP     ( GameEngine* engine );
                                ~NetEngineDosPacketDriverUDP    ();

    //-------------- Network Methods -----------------
    virtual void                SetAddress                      ( uint64_t address );
    virtual uint64_t            GetAddress                      ();
    virtual int                 GetType                         ();                         //Get the Type of the Net Implementation (ex. local buffer of ethernet )
    virtual unsigned int        GetNumPacketsInInbox            ();
    virtual bool                GetIsServer                     ();
    virtual void                Send                            ( Packet* packet );
    virtual Packet*             GetFirstPacketFromInbox         ();
    virtual vector<Packet*>*    GetInbox                        ();
    virtual bool                InboxEmpty                      ();

    //-------------------- Client --------------------
    virtual void                Connect                         ( uint64_t target );
    virtual void                Disconnect                      ();
    virtual bool                GetIsConnected                  ();

    //-------------------- Server --------------------
    virtual void                ConfigureAsServer               ();
    virtual vector<uint64_t>    GetClientAddresses              ();

    virtual void                Update                          ();

    //------------ Dos Packet Driver only ------------
    virtual void                ReceivePackets                  ();
    virtual void                SendJoinRequest                 ();
    virtual void                SendDisconnectRequest           ();
    virtual void                SendJoinAck                     ();

    virtual void*               SerializePacketData             ( Packet* packet, int* dataLength );
    virtual Packet*             DeSerializePacketData           ( void* data, int dataLength );
};

#endif