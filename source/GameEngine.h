//====================================
// GameEngine.h
// the game engine handles all game objects (basically everything in game)
// all objects have a pointer to it and all communication with other objects is handled though that pointer
// you can ask the game engine for objects (pointers) based on various criteria
// for example what game object is at Pos X/Y, or what game objects are closer then Z units from X/Y etc.
//====================================

//========== include guard ===========
#ifndef GAME_ENGINE
#define GAME_ENGINE
//====================================

//========== stdlib includes =========
#include <vector>
#include <cstring>
#include <stdlib.h>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "TextEngine.h"
#include "InputEngine.h"
#include "NetEngine.h"
#include "GraphicsEngine.h"
#include "TimeEngine.h"
#include "FileEngine.h"
#include "DataEngine.h"
#include "ObjectsEngine.h"
#ifdef TARGET_LINUX
    #include "NetEngineLinuxSocketsUDP.h"
    #include "NetEngineLinuxSocketsTCP.h"
    #include "InputEngineSDL.h"
    #include "AssetsLinux.h"
#endif
#ifdef TARGET_WIN
    #include "NetEngineWinSocketsUDP.h"
    #include "InputEngineSDL.h"
    #include "AssetsWin.h"
#endif
#ifdef TARGET_DOS
    #include "InputEngineDOS.h"
    #include "AssetsDOS.h"
#endif




#include "Vector2D.h"
//#include "Object.h"
#include "DerivedObjects.h"
//====================================

//======= forward declarations =======
class Object;
class NetEngine;
class InputEngine;
class NetEngine;
class GraphicsEngine;
class TextEngine;
class TimeEngine;
class FileEngine;
class DataEngine;
class ObjectsEngine;
//====================================

class GameEngine
{
protected:
    int engineUID;

public:
    //-------------- Engine Components ----------------
    TextEngine*         text;
    TextEngine*         debug;
    NetEngine*          net;
    InputEngine*        input;
    GraphicsEngine*     graphics;
    TimeEngine*         time;
    FileEngine*         file;
    DataEngine*         data;
    ObjectsEngine*      objects;

    //------------- Constructor / Destructor -----------
                        GameEngine                  ();
                        ~GameEngine                 ();

    int                 GetEngineUID                ();

    //-------------- Auxilary Engine Methods ----------
    vector<int>         GetAvailableNetTypes        ();
    void                SetNetType                  ( int netType );
    vector<int>         GetAvailableTextTypes       ();
    void                SetTextType                 ( int TextType );
    void                SetDebugType                ( int TextType );
    vector<int>         GetAvailableInputTypes      ();
    void                SetInputType                ( int InputType );
    vector<int>         GetAvailableGraphicsTypes   ();
    void                SetGraphicsType             ( int graphicsType );
    vector<int>         GetAvailableTimeTypes       ();
    void                SetTimeType                 ( int timeType );
    vector<int>         GetAvailableFileTypes       ();
    void                SetFileType                 ( int timeType );
    vector<int>         GetAvailableDataTypes       ();
    void                SetDataType                 ( int dataType );
    vector<int>         GetAvailableObjectsTypes    ();
    void                SetObjectsType              ( int objectsType );

    //----------------- Auxilary Methods --------------
    void                Quit                        ();
};

//include Guard End
#endif