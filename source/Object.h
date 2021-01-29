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

//============= defines ==============
#define OBJECT_TYPE_OBJECT 0
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

class Object
{
protected:
    GameEngine* engine;

    unsigned long int   uid;
    unsigned int        type;
    bool                visible;
    bool                active;
    bool                predict;
    bool                clientActive;

    int test;
public:
                                Object             ( GameEngine* engine );

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

    virtual void                SendStatus         ();                          //serialize all attributes and send them over the net
    virtual void                LoadStatus         ( void* data );              //get data from the net and update all attributes

    virtual void                Update             ();                          //is called every tick (usually on the server)
    virtual void                GameLogic          ();                          //is called from Update. handles just the GameLogic (minus netupdate etc)
    virtual void                ClientSideUpdate   ();
    virtual void                Predict            ();
    virtual void                Render             ();
};

#endif