//====================================
// GraphicsEngineSDL.h
// 2D Graphics engine. SDL Engine
//====================================

//========== include guard ===========
#ifndef GRAPHICS_ENGINE_SDL
#define GRAPHICS_ENGINE_SDL
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
//====================================

//========= galaxy includes ==========
#include "Vector2D.h"
#include "GraphicsEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
//====================================

class Color
{
public:
    unsigned char r, g, b, a;
};


class GraphicsEngineSDL : public GraphicsEngine
{
protected:
    GameEngine*         engine;

    SDL_Window*         window;
    SDL_Renderer*       renderer;

    Color               colors[16];

    //camera
    Vector2D            camPos;

public:
                                        GraphicsEngineSDL           ( GameEngine* engine );
    virtual                             ~GraphicsEngineSDL          ();

    virtual     void                    InitGraphics                ();

    virtual     vector<DisplayMode>     GetAvailableDisplayModes    ();
    virtual     void                    SetDisplayMode              ( DisplayMode mode );
    virtual     void                    SetFullScreen               ( bool fullScreen );

    virtual     unsigned int            GetScreenWidth              ();
    virtual     unsigned int            GetScreenHeight             ();
    
    virtual     void                    PreFrame                    ();
    virtual     void                    PostFrame                   ();

    //Camera
    virtual     Vector2D                GetCamPos                   ();
    virtual     void                    SetCamPos                   ( Vector2D newPos );
    virtual     void                    SetCamCenter                ( Vector2D newPos );
    virtual     Vector2D                GetCamCenter                ();

    virtual     void                    ClearScreen                 ();
    virtual     void                    ClearScreen                 ( unsigned char color );
    virtual     void                    DrawPixel                   ( Vector2D pos, unsigned char color );
};

#endif