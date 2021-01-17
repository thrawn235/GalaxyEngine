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
using namespace std;
//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
#define NET_BUFFER_SIZE 1024
//====================================

struct NetBuffer
{
	unsigned int firstIndex = 0;
	unsigned int lastIndex = 0;
	unsigned char buffer[NET_BUFFER_SIZE];
};

struct NetCommand
{

};

class NetEngine
{
protected:

public:
							NetEngine 		( NetBuffer* localNetBuffer )			{};
	virtual void 			SetTarget		( string target ) 						= 0;
	virtual void 			SendCommand		( NetCommand* command )					= 0;
	virtual void 			SendLayer1		( unsigned char out ) 					= 0;
	virtual unsigned char 	ReceiveLayer1	() 										= 0;
	virtual unsigned int 	GetLayer1Unread	() 										= 0;
};

#endif