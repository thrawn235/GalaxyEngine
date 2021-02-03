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
//====================================

//============= defines ==============
#define NET_BUFFER_SIZE 1024

#define NET_TYPE_LOCAL_BUFFER   1
#define NET_TYPE_WIN_SOCKETS    2
#define NET_TYPE_LINUX_SOCKETS  3

#define NET_PACKET_TYPE_OBJECT_UPDATE   1
#define NET_PACKET_TYPE_SEND_COMPLETE   2
//====================================

class Packet
{
public:
    uint64_t            sender;
    uint32_t            sequence;
    uint8_t             type;       //Object Update, Acknoledge Packet etc
    uint16_t            dataLength;
    void*               data;

    //---------- Constructor / Destructor ------------
    Packet          ();
    ~Packet         ();

    //----------------- Data -------------------------
    void FixData    ();     //allocate memory and copy data from the data pointer
};





class NetEngine
{
protected:

public:
    //---------- Constructor / Destructor ------------
                            NetEngine                   ()                                          {};

    //-------------------- Init ----------------------
    virtual void            Init                        ()                                          = 0;

    //------------------ Set / Get -------------------
    virtual void            SetTarget                   ( uint64_t target )                         = 0;
    virtual void            SetAddress                  ( uint64_t address )                        = 0;
    virtual uint64_t        GetAddress                  ()                                          = 0;
    virtual int             GetType                     ()                                          = 0;        //Get the Type of the Net Implementation (ex. local buffer of ethernet )
    virtual unsigned int    GetNumPacketsInInbox        ()                                          = 0;
    
    //-------------- Network Methods -----------------
    virtual void            Send                        ( Packet* packet )                          = 0;
    virtual void            Send                        ( Packet* packet, uint64_t target )         = 0;
    virtual Packet*         GetFirstPacketFromInbox     ()                                          = 0;
    virtual bool            InboxEmpty                  ()                                          = 0;
    virtual bool            InboxFull                   ()                                          = 0;
};

#endif