//====================================
// GameNode.h
// common Parent of GameServer and GameClient
// it has nothing to do with networking
//====================================

//========== include guard ===========
#ifndef GAME_NODE
#define GAME_NODE
//====================================

//========== stdlib includes =========
using namespace std;
//====================================

//========= galaxy includes ==========
//#include "NetEngine.h"
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
class GameEngine;
class Packet;
//====================================


class GameNode
{
protected:
    GameEngine* engine;

public:
                        GameNode                ();
    virtual             ~GameNode               ();
    		GameEngine* GetEngine               ();
    virtual void        Run                     ();
    		void      	UpdateObjectFromNet     ( Packet* pkt );
    virtual	float   	GetNetworkUpdateTime    () = 0;
    virtual float   	GetUpdateTime           () = 0;
};

#endif