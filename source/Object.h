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
//#include "GameEngine.h"
#include "Vector2D.h"
//====================================

//============= defines ==============
#define OBJECT_TYPE_OBJECT  0
#define OBJECT_TYPE_PLAYER  1
#define OBJECT_TYPE_ENEMY   2
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

class Object
{
protected:
    GameEngine* engine;                 //pointer to the game engine

    Vector2D            pos;            //position of the object
    Vector2D            movement;       //final movement vector (once all forces are added)

    unsigned long int   uid;            //unique identifier
    
    unsigned int        type;           //type of the object

    bool                visible;
    bool                active;
    bool                predict;
    bool                clientActive;

    long unsigned int test;
public:
    //------------ Constructor/Destructor: --------------------
                                Object             ( GameEngine* engine );

    //---------------------- Get/Set --------------------------
    virtual unsigned long int   GetUID             ();
    virtual void                SetUID             ( unsigned long uid );
    virtual unsigned int        GetType            ();
    virtual void                SetType            ( unsigned int type );
    virtual bool                GetVisible         ();
    virtual bool                GetActive          ();
    virtual bool                GetPredict         ();
    virtual bool                GetClientActive    ();
    virtual void                SetVisible         ( bool visible );
    virtual void                SetActive          ( bool active );
    virtual void                SetPredict         ( bool predict );
    virtual void                SetClientActive    ( bool clientActive );
    virtual Vector2D            GetPos             ();
    virtual void                SetPos             ( Vector2D pos );
    virtual Vector2D            GetMovement        ();
    virtual void                SetMovement        ( Vector2D movement );

    //-------------------- Network ----------------------------
    virtual void                SendStatus         ();                          //serialize all attributes and send them over the net
    virtual void                LoadStatus         ( void* data );              //get data from the net and update all attributes

    //-- Base Engine Funcions (called by engine every Frame) --
    virtual void                Update             ();                          //is called every tick (usually on the server)
    virtual void                GameLogic          ();                          //is called from Update. handles just the GameLogic (minus netupdate etc)
    virtual void                ClientSideUpdate   ();
    virtual void                Predict            ();
    virtual void                Render             ();
};

#endif