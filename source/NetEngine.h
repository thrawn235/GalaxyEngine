//====================================
// NetEngine.h
// NetEngine is the interface to the Network
// sends and receives Data over a Network
// protocol, medium and everything else is implemented in the children
//====================================

//========== include guard ===========
#ifndef NETENGINE
#define NETENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
using namespace std;
//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
#define NET_TYPE_LOCAL_BUFFER               1
#define NET_TYPE_WIN_SOCKETS                2
#define NET_TYPE_WIN_SOCKETS_UDP            3
#define NET_TYPE_WIN_SOCKETS_TCP            4
#define NET_TYPE_LINUX_SOCKETS_UDP          5
#define NET_TYPE_LINUX_SOCKETS_TCP          6
#define NET_TYPE_DOS_PACKET_DRIVER_UDP      7

#define NET_PACKET_TYPE_OBJECT_UPDATE       1
#define NET_PACKET_TYPE_SEND_COMPLETE       2
#define NET_PACKET_TYPE_JOIN_REQUEST        3
#define NET_PACKET_TYPE_JOIN_ACK            4
#define NET_PACKET_TYPE_DISCONNECT_REQUEST  5
//====================================

class Packet
{
public:
    uint64_t            sender;
    uint8_t             type;           //Object Update, Acknoledge Packet etc
    uint16_t            dataLength;
    void*               data;

    //---------- Constructor / Destructor ------------
    Packet          ();
    ~Packet         ();

    //----------------- Data -------------------------
    void FixData    ();                 //allocate memory and copy data from the data pointer
}__attribute__((packed));



class NetEngine
{
protected:
    GameEngine* engine;
public:
    //---------- Constructor / Destructor ------------
                                NetEngine                   ( GameEngine* engine );
    virtual                     ~NetEngine                  ();

    //-------------- Network Methods -----------------
    virtual void                SetAddress                  ( uint64_t address )    = 0;
    virtual uint64_t            GetAddress                  ()                      = 0;
    virtual int                 GetType                     ()                      = 0;        //Get the Type of the Net Implementation (ex. local buffer of ethernet )
    virtual unsigned int        GetNumPacketsInInbox        ()                      = 0;
    virtual bool                GetIsServer                 ()                      = 0;
    virtual void                Send                        ( Packet* packet )      = 0;
    virtual Packet*             GetFirstPacketFromInbox     ()                      = 0;
    virtual vector<Packet*>*    GetInbox                    ()                      = 0;
    virtual bool                InboxEmpty                  ()                      = 0;

    //-------------------- Client --------------------
    virtual void                Connect                     ( uint64_t target )     = 0;
    virtual void                Disconnect                  ()                      = 0;
    virtual bool                GetIsConnected              ()                      = 0;

    //-------------------- Server --------------------
    virtual void                ConfigureAsServer           ()                      = 0;
    virtual vector<uint64_t>    GetClientAddresses          ()                      = 0;


    virtual void                Update                      ()                      = 0;        //runs in every game loop
};

#endif