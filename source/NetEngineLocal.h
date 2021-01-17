//=============================
// NetEngineLocal.h
// the Gameserver does all the Game Logic and sends the current state to the client(s)
//=============================

//========== include guard ===========
#ifndef NETENGINELOCAL
#define NETENGINELOCAL
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
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
	vector<NetCommand>*		localNetBuffer;

public:
					NetEngineLocal 	( vector<NetCommand>* localNetBuffer );
	virtual void 	SetTarget		( string target );
	virtual void 	SendCommand		( NetCommand* command );
};

#endif