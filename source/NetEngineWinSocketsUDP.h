//====================================
// NetEngineWinSocketsUDP.h
// the implementation uses windows sockets
// this implementation uses UDP
//====================================

//========== include guard ===========
#ifndef NET_ENGINE_WIN_SOCKETS_UDP
#define NET_ENGINE_WIN_SOCKETS_UDP
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <ws2tcpip.h>
#include <winsock2.h>
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


class NetEngineWinSocketsUDP : public NetEngine
{
protected:
    vector<Packet*>             inbox;
    uint64_t                    address;
    uint64_t                    target;

    //Sockets:
    WSADATA                     wsa;
    struct sockaddr_in          myAddress, peerAddress;
    long long unsigned int      socketDescriptor;
    vector<sockaddr_in>         incomingAddresses;
    int                         port;
    bool                        isServer;
    bool                        isConnected;
    void*                       receiveBuffer;

public:
    //---------- Constructor / Destructor ------------
                                NetEngineWinSocketsUDP      ( GameEngine* engine );
                                ~NetEngineWinSocketsUDP     ();

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

    virtual void                Update                      ();

    //--------------- LinuxSockets only --------------
    virtual void                ReceivePackets              ();
    virtual void                SendJoinRequest             ();
    virtual void                SendDisconnectRequest       ();
    virtual void                SendJoinAck                 ();

    virtual void*               SerializePacketData         ( Packet* packet, int* dataLength );
    virtual Packet*             DeSerializePacketData       ( void* data, int dataLength );
};

#endif