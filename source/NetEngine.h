//====================================
// NetEngine.h
// the Gameserver does all the Game Logic and sends the current state to the client(s)
//====================================

//========== include guard ===========
#ifndef NETENGINE
#define NETENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <cstdint>
using namespace std;
//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
#define NET_BUFFER_SIZE 1024
#define NET_TYPE_LOCAL_BUFFER   1
#define NET_TYPE_SOCKETS        2

#define NET_PACKET_TYPE_OBJECT_UPDATE   1
#define NET_PACKET_TYPE_SEND_COMPLETE   2
//====================================

struct Packet
{
    uint64_t            sender;
    uint32_t            sequence;
    uint8_t             type;       //Object Update, Acknoledge Packet etc
    uint16_t            dataLength;
    void*               data;
};

class NetEngine
{
protected:

public:
                            NetEngine                   ()                                          {};
    virtual void            Init                        ()                                          = 0;
    virtual void            Send                        ( Packet* packet, long long int target )    = 0;
    virtual void            SetTarget                   ( long long int target )                    = 0;
    virtual void            SetAddress                  ( long long int address )                   = 0;
    virtual long long int   GetAddress                  ()                                          = 0;
    virtual void            Send                        ( Packet* packet )                          = 0;
    virtual Packet*         GetFirstPacketFromInbox     ()                                          = 0;
    virtual bool            InboxEmpty                  ()                                          = 0;
    virtual bool            InboxFull                   ()                                          = 0;
    virtual unsigned int    GetNumPacketsInInbox        ()                                          = 0;
    virtual int             GetType                     ()                                          = 0;        //Get the Type of the Net Implementation (ex. local buffer of ethernet )
};

#endif