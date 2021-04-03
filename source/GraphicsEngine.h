//====================================
// GraphicsEngine.h
// 2D Graphics engine.
//====================================

//========== include guard ===========
#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Vector2D.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
#define GRAPHICS_TYPE_DUMMY     0
#define GRAPHICS_TYPE_SDL       1
#define GRAPHICS_TYPE_VESA      2

#define COLOR_BLACK             0
#define COLOR_BLUE              1
#define COLOR_GREEN             2
#define COLOR_CYAN              3
#define COLOR_RED               4
#define COLOR_PINK              5
#define COLOR_BROWN             6
#define COLOR_GREY              7
#define COLOR_DARK_GREY         8
#define COLOR_LIGHT_BLUE        9
#define COLOR_LIGHT_GREEN       10
#define COLOR_LIGHT_CYAN        11
#define COLOR_LIGHT_RED         12
#define COLOR_LIGHT_PINK        13
#define COLOR_YELLOW            14
#define COLOR_WHITE             15
//====================================

class DisplayMode
{
public:
    unsigned int    width;
    unsigned int    height;
    unsigned int    colorDepth;
    string          name;
};


class GraphicsEngine
{
protected:

public:
                                        GraphicsEngine              ( GameEngine* engine )                  {};
    virtual                             ~GraphicsEngine             ()                                      {};

    virtual     void                    InitGraphics                ()                                      = 0;

    virtual     vector<DisplayMode>     GetAvailableDisplayModes    ()                                      = 0;
    virtual     void                    SetDisplayMode              ( DisplayMode mode )                    = 0;
    virtual     void                    SetFullScreen               ( bool fullScreen )                     = 0;

    virtual     unsigned int            GetScreenWidth              ()                                      = 0;
    virtual     unsigned int            GetScreenHeight             ()                                      = 0;
    
    //Clear and Flip
    virtual     void                    PreFrame                    ()                                      = 0;
    virtual     void                    PostFrame                   ()                                      = 0;

    //Camera
    virtual     Vector2D                GetCamPos                   ()                                      = 0;
    virtual     void                    SetCamPos                   ( Vector2D newPos )                     = 0;
    virtual     void                    SetCamCenter                ( Vector2D newPos )                     = 0;
    virtual     Vector2D                GetCamCenter                ()                                      = 0;

    //Drawing
    virtual     void                    ClearScreen                 ()                                      = 0;
    virtual     void                    ClearScreen                 ( unsigned char color )                 = 0;
    virtual     void                    DrawPixel                   ( Vector2D pos, unsigned char color )   = 0;
};

#endif