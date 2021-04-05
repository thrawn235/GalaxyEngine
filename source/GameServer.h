//====================================
// GameServer.h
// the Gameserver does all the Game Logic and sends the current state to the client(s)
//====================================

//========== include guard ===========
#ifndef GAME_SERVER
#define GAME_SERVER
//====================================

//========== stdlib includes =========
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GameNode.h"
//====================================

//======= forward declarations =======
class GameNode;
//====================================

class GameServer : public GameNode
{
protected:

public:
            			GameServer  ();
    virtual	       		~GameServer ();
    		GameEngine*	GetEngine	();
    		void    	Run         ();
};

#endif