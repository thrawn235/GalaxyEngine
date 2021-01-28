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

    virtual void                SendStatus         ();
    virtual void                LoadStatus         ( void* data );

    virtual void                Update             ();
    virtual void                ClientSideUpdate   ();
    virtual void                Predict            ();
    virtual void                Render             ();
};

#endif