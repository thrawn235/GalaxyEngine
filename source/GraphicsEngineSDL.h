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

class Texture
{
public:
    unsigned int    id;
    SDL_Texture*    texture;
};


class GraphicsEngineSDL : public GraphicsEngine
{
protected:
    GameEngine*             engine;

    SDL_Window*             window;
    SDL_Renderer*           renderer;

    int                     screenWidth, screenHeight;
    int                     logicalScreenWidth, logicalScreenHeight;
    int                     screenPadding;
    Color                   colors[16];

    //camera
    Vector2D                camPos;

    vector<Texture>         textures;

public:
                            GraphicsEngineSDL           ( GameEngine* engine );
    virtual                 ~GraphicsEngineSDL          ();

    void                    InitGraphics                ();

    vector<DisplayMode>     GetAvailableDisplayModes    ();
    void                    SetDisplayMode              ( DisplayMode mode );
    void                    SetFullScreen               ( bool fullScreen );

    unsigned int            GetScreenWidth              ();
    unsigned int            GetScreenHeight             ();
    
    void                    PreFrame                    ();
    void                    PostFrame                   ();

    //Camera
    Vector2D                GetCamPos                   ();
    void                    SetCamPos                   ( Vector2D newPos );
    void                    SetCamCenter                ( Vector2D newPos );
    Vector2D                GetCamCenter                ();

    void                    ClearScreen                 ();
    void                    ClearScreen                 ( unsigned char color );
    void                    DrawPixel                   ( Vector2D pos, unsigned char color );
    void                    DrawLine                    ( Vector2D start, Vector2D end, unsigned char color );
    void                    DrawHLine                   ( Vector2D start, int length, unsigned char color );
    void                    DrawVLine                   ( Vector2D start, int length, unsigned char color );
    void                    DrawRect                    ( Vector2D pos, int width, int height, unsigned char color );
    void                    DrawFilledRect              ( Vector2D pos, int width, int height, unsigned char color );
    void                    DrawCircle                  ( Vector2D pos, int radius, unsigned char color );
    void                    DrawFilledCircle            ( Vector2D pos, int radius, unsigned char color );
    void                    DrawVector                  ( Vector2D pos, Vector2D vec, float scale, unsigned char color );

    //Sprites
    void                    DrawSprite                  ( unsigned long id, Vector2D pos );
    void                    DrawSpriteInSheet           ( unsigned int id, unsigned int index, Vector2D pos );
    void                    DrawSpriteSheet             ( unsigned int id, unsigned int width, Vector2D pos );

    //Text
    void                    DrawText                    ( unsigned int id, string text, Vector2D pos );
    void                    DrawText                    ( unsigned int id, string text, unsigned int lineLength, Vector2D pos );

    //SDL only
    void                    DrawSprite                  ( SDL_Texture* texture, Vector2D pos );
    SDL_Texture*            GetTextureInCollection      ( unsigned long id, unsigned long index );
    SDL_Texture*            GetTexture                  ( unsigned long id );
};

#endif