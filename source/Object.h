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
    GameEngine*         engine;         //pointer to the game engine

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
            void                SetEngine          ( GameEngine* engine );
            GameEngine*         GetEngine          ();
            unsigned long int   GetUID             ();
            void                SetUID             ( unsigned long uid );
            unsigned int        GetType            ();
            void                SetType            ( unsigned int type );
            bool                GetVisible         ();
            bool                GetActive          ();
            bool                GetPredict         ();
            bool                GetClientActive    ();
            void                SetVisible         ( bool visible );
            void                SetActive          ( bool active );
            void                SetPredict         ( bool predict );
            void                SetClientActive    ( bool clientActive );
            Vector2D            GetPos             ();
            void                SetPos             ( Vector2D pos );
            Vector2D            GetMovement        ();
            void                SetMovement        ( Vector2D movement );

    //-------------------- Network ----------------------------
    virtual void                SendStatus         ();                          //serialize all attributes and send them over the net
    virtual void                LoadStatus         ( void* data );              //get data from the net and update all attributes

    //-- Base Engine Funcions (called by engine every Frame) --
    virtual void                Update             ();                          //is called every tick (usually on the server)
    virtual void                GameLogic          ();                          //is called from Update. handles just the GameLogic (minus netupdate etc)
    virtual void                ClientSideUpdate   ();
    virtual void                Predict            ( float tickRate );
    virtual void                Render             ();
};

#endif