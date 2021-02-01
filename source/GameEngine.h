//====================================
// GameEngine.h
// the game engine handles all game objects (basically everything in game)
// all objects have a pointer to it and all communication with other objects is handled though that pointer
// you can ask the game engine for objects (pointers) based on various criteria
// for example what game object is at Pos X/Y, or what game objects are closer then Z units from X/Y etc.
//====================================

//========== include guard ===========
#ifndef GAMEENGINE
#define GAMEENGINE
//====================================

//========== stdlib includes =========
#include <vector>
#include <cstring>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Object.h"
#include "DerivedObjects.h"
#include "TextEngine.h"
#include "NetEngineLocal.h"
#ifdef dos
    #include "TextEngineSTDIO.h"
#else
    #include "TextEngineIOStream.h"
#endif
#include "Vector2D.h"
//====================================

//======= forward declarations =======
class Object;
//====================================

class GameEngine
{
protected:
    vector<Object*> objects;

    unsigned long int highestUID;

public:
    //-------------- Engine Components ----------------
    TextEngine*     text;
    TextEngine*     debug;
    NetEngine*      net;

    //------------- Constructor / Destructor -----------
                        GameEngine              ();

    // ------------------ Set / Get --------------------
    void                SetHighestUID           ( unsigned long int UID );
    unsigned long int   GetHighestUID           ();
    unsigned long int   GetHighestUIDAndInc     ();

    //---------------- Main Engine Fuctions -----------
    vector<Object*>     GetAllObjects           ();
    Object*             GetObjectByUID          ( unsigned long int uid );

    void                AddObject               ( Object* object );

    //---------------- Object Update Functions --------
    void                UpdateAll               ();                             //all the gamelogic happens here. Usually on the Server side
    void                ClientSideUpdateAll     ();                             //gamelogic update on the client side. use with caution
    void                PredictAll              ( float tickRate );             //moves all objects on along its movement vector based on frametime. this is for visual smoothness only
    void                RenderAll               ();                             //draw all objects

    //------------------- Network ---------------------
    //void                UpdateGamestateFromNet  ();
};

//include Guard End
#endif