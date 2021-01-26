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
	vector<Packet*>		inbox;
	unsigned int 		address;
	unsigned int 		target;

public:
								NetEngineLocal 				();
	virtual void 				Init 						();
	virtual void				Send 						( Packet* packet, char* target );
	virtual void 				SetTarget 					( char* target );
	virtual void 				SetAddress 					( char* address );
	virtual void				Send 						( Packet* packet );
	virtual Packet*				GetFirstPacketFromInbox 	();
	virtual bool				InboxEmpty	 				();
	virtual bool 				InboxFull					();
	virtual unsigned int 		NumPacketsInInbox			();
	virtual char*				GetAddress 					();
	virtual vector<Packet*>* 	GetInbox 					();
};

#endif