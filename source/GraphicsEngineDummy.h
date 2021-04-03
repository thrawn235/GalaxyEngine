//====================================
// GraphicsEngineDummy.h
// Dummy Implementation of GraphicsEngine
//====================================

//========== include guard ===========
#ifndef GRAPHICS_ENGINE_DUMMY
#define GRAPHICS_ENGINE_DUMMY
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GraphicsEngine.h"
//====================================

//========= other includes ===========
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
//====================================


class GraphicsEngineDummy : public GraphicsEngine
{
protected:

public:
                                        GraphicsEngineDummy         ( GameEngine* engine );
    virtual                             ~GraphicsEngineDummy        ();

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