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

public:
    TextEngine*     text;
    NetEngine*      net;

                    GameEngine          ();
    vector<Object*> GetAllObjects       ();
    void            UpdateAll           ();
    void            ClientSideUpdateAll ();
    void            PredictAll          ();
    void            RenderAll           ();
};

//include Guard End
#endif