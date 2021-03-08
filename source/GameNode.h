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
#include "NetEngine.h"
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
class GameEngine;
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
    virtual void        UpdateObjectsFromNet    ( Packet* pkt );
};

#endif