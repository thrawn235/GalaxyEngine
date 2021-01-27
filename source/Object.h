//====================================
// Object.h
// the Main Parent Class of all Objects in the Game.
// All other Objects (player, enemies etc) are derived vom it-
//====================================

//========== include guard ===========
#ifndef OBJECT
#define OBJECT
//====================================

//========== stdlib includes =========
#include <stdio.h>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GameEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

class Object
{
protected:
    GameEngine* engine;
public:
            Object  ( GameEngine* engine );
    void    Talk    ();
};

#endif