//====================================
// GameServer.h
// the Gameserver does all the Game Logic and sends the current state to the client(s)
//====================================

//========== include guard ===========
#ifndef GAMESERVER
#define GAMESERVER
//====================================

//========== stdlib includes =========
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GameEngine.h"
#include "NetEngine.h"
//====================================

//======= forward declarations =======
//====================================

class GameServer
{
protected:
	GameEngine* engine;

public:
			GameServer 	( vector<NetCommand>* localNetBuffer );
	void 	Run			();
};

#endif