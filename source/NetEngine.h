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
using namespace std;
//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
#define NET_BUFFER_SIZE 1024
//====================================

struct Packet
{
	char			 	sender[32];
	unsigned long		sequence;
	unsigned int 		dataLength;
	void*				data;
};

class NetEngine
{
protected:

public:
							NetEngine 					()									{};
	virtual void 			Init 						()									= 0;
	virtual void			Send 						( Packet* packet, char* target )	= 0;
	virtual void 			SetTarget 					( char* target )					= 0;
	virtual void 			SetAddress 					( char* address )					= 0;
	virtual char* 			GetAddress					()									= 0;
	virtual void			Send 						( Packet* packet )					= 0;
	virtual Packet*			GetFirstPacketFromInbox 	()									= 0;
	virtual bool			InboxEmpty	 				()									= 0;
	virtual bool 			InboxFull					()									= 0;
	virtual unsigned int 	NumPacketsInInbox			()									= 0;
};

#endif