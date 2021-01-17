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


struct NetCommand
{

};

class NetEngine
{
protected:

public:
					NetEngine 	( vector<NetCommand>* localNetBuffer )	{};
	virtual void 	SetTarget	( string target ) 						= 0;
	virtual void 	SendCommand	( NetCommand* command )					= 0;
};

#endif