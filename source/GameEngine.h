//Game Engine

//include Guard
#ifndef GAMEENGINE
#define GAMEENGINE

//stdlib:
#include <vector>
using namespace std;

//Galaxy includes
#include "Object.h"
#include "TextEngine.h"
#include "NetEngineLocal.h"
#ifdef dos
    #include "TextEngineSTDIO.h"
#else
    #include "TextEngineIOStream.h"
#endif

//forward declaration:
class Object;

class GameEngine
{
protected:
    vector<Object*> objects;

    unsigned long int highestUID;

public:
    TextEngine*     text;
    NetEngine*      net;

                        GameEngine          ();

    void                SetHighestUID       ( unsigned long int UID );
    unsigned long int   GetHighestUID       ();
    unsigned long int   GetHighestUIDAndInc ();

    vector<Object*>     GetAllObjects       ();

    void                AddObject           ( Object* object );

    void                UpdateAll           ();
    void                ClientSideUpdateAll ();
    void                PredictAll          ();
    void                RenderAll           ();
};

//include Guard End
#endif