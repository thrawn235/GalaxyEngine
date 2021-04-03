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
    virtual     void                    DrawLine                    ( Vector2D start, Vector2D end, unsigned char color );
    virtual     void                    DrawHLine                   ( Vector2D start, int length, unsigned char color );
    virtual     void                    DrawVLine                   ( Vector2D start, int length, unsigned char color );
    virtual     void                    DrawRect                    ( Vector2D pos, int width, int height, unsigned char color );
    virtual     void                    DrawFilledRect              ( Vector2D pos, int width, int height, unsigned char color );
    virtual     void                    DrawCircle                  ( Vector2D pos, int radius, unsigned char color );
    virtual     void                    DrawFilledCircle            ( Vector2D pos, int radius, unsigned char color );
    virtual     void                    DrawVector                  ( Vector2D pos, Vector2D vec, float scale, unsigned char color );
};

#endif