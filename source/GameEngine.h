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
#include <stdlib.h>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Object.h"
#include "DerivedObjects.h"
#include "TextEngine.h"
#include "InputEngine.h"
#ifdef win
    #include "NetEngineWinSocketsUDP.h"
    #include "NetEngineLocal.h"
    #include "TextEngineIOStream.h"
    #include "InputEngineSDL.h"
#endif
#ifdef linux
    #include "NetEngineLinuxSocketsUDP.h"
    #include "NetEngineLinuxSocketsTCP.h"
    #include "NetEngineLocal.h"
    #include "TextEngineIOStream.h"
    #include "TextEngineSTDIO.h"
    #include "InputEngineSDL.h"
#endif
#ifdef dos
    #include "NetEngineLocal.h"
    #include "TextEngineSTDIO.h"
    #include "TextEngineIOStream.h"
#endif
#include "Vector2D.h"
//====================================

//======= forward declarations =======
class Object;
class NetEngine;
class InputEngine;
//====================================

class GameEngine
{
protected:
    vector<Object*>     objects;
    vector<Object*>     deletedObjects;

    unsigned long int   highestUID;

public:
    //-------------- Engine Components ----------------
    TextEngine*         text;
    TextEngine*         debug;
    NetEngine*          net;
    InputEngine*        input;

    //------------- Constructor / Destructor -----------
                        GameEngine              ();
                        ~GameEngine             ();

    // ------------------ Set / Get --------------------
    void                SetHighestUID           ( unsigned long int UID );
    unsigned long int   GetHighestUID           ();
    unsigned long int   GetHighestUIDAndInc     ();

    //-------------- Auxilary Network Mthods ----------
    vector<int>         GetAvailableNetTypes    ();
    void                SetNetType              ( int netType );

    //----------------- Auxilary Methods --------------
    void                Quit                    ();

    //---------------- Main Engine Fuctions -----------
    vector<Object*>     GetAllObjects           ();
    Object*             GetObjectByUID          ( unsigned long int uid );

    void                AddObject               ( Object* object );

    void                DeleteObject            ( Object* object );             //move Object to deleteList (graveyard) 
    void                DeleteObject            ( unsigned long uid );
    void                DeleteObjects           ( vector<Object*> objects );
    void                DeleteObjects           ( vector<unsigned long> uids );
    void                PurgeObject             ( Object* object );             //delete Object immediatly without moving it to the graveyard first. use at your own risk!
    void                PurgeObject             ( unsigned long uid );
    void                PurgeObjects            ( vector<Object*> objects );
    void                PurgeObjects            ( vector<unsigned long> uids );
    void                ClearDeletedObjects     ();       
    void                DeleteAllObjects        ( bool includePersistent );
    void                DeleteAllObjectsExcept  ( Object* object, bool includePersistent );
    void                PurgeAllObjects         ( bool includePersistent );
    void                PurgeAllObjectsExcept   ( Object* object, bool includePersistent );

    //---------------- Object Update Functions --------
    void                UpdateAll               ();                             //all the gamelogic happens here. Usually on the Server side
    void                ClientSideUpdateAll     ();                             //gamelogic update on the client side. use with caution
    void                UpdateServerIndependend ();
    void                PredictAll              ( float tickRate );             //moves all objects on along its movement vector based on frametime. this is for visual smoothness only
    void                RenderAll               ();                             //draw all objects

    //------------------- Network ---------------------
    //void                UpdateGamestateFromNet  ();
};

//include Guard End
#endif