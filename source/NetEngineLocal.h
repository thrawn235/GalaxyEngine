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
using namespace std;
//====================================

//========= galaxy includes ==========
#include "NetEngine.h"
//====================================

//======= forward declarations =======
//====================================


class NetEngineLocal : public NetEngine
{
protected:
	NetBuffer*		localNetBuffer;

public:
							NetEngineLocal 	( NetBuffer* localNetBuffer );
	virtual void 			SetTarget		( string target );
	virtual void 			SendCommand		( NetCommand* command );
	virtual void 			SendLayer1		( unsigned char out );
	virtual unsigned char 	ReceiveLayer1	();
	virtual unsigned int 	GetLayer1Unread	();
};

#endif