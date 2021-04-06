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
                            GraphicsEngineDummy                     ( GameEngine* engine );
    virtual                 ~GraphicsEngineDummy                    ();

    void                    InitGraphics                            ();

    vector<DisplayMode>     GetAvailableDisplayModes                ();
    void                    SetDisplayMode                          ( DisplayMode mode );
    void                    SetFullScreen                           ( bool fullScreen );

    unsigned int            GetScreenWidth                          ();
    unsigned int            GetScreenHeight                         ();
    
    void                    PreFrame                                ();
    void                    PostFrame                               ();

    //Camera
    Vector2D                GetCamPos                               ();
    void                    SetCamPos                               ( Vector2D newPos );
    void                    SetCamCenter                            ( Vector2D newPos );
    Vector2D                GetCamCenter                            ();

    void                    ClearScreen                             ();
    void                    ClearScreen                             ( unsigned char color );
    void                    DrawPixel                               ( Vector2D pos, unsigned char color );
    void                    DrawLine                                ( Vector2D start, Vector2D end, unsigned char color );
    void                    DrawHLine                               ( Vector2D start, int length, unsigned char color );
    void                    DrawVLine                               ( Vector2D start, int length, unsigned char color );
    void                    DrawRect                                ( Vector2D pos, int width, int height, unsigned char color );
    void                    DrawFilledRect                          ( Vector2D pos, int width, int height, unsigned char color );
    void                    DrawCircle                              ( Vector2D pos, int radius, unsigned char color );
    void                    DrawFilledCircle                        ( Vector2D pos, int radius, unsigned char color );
    void                    DrawVector                              ( Vector2D pos, Vector2D vec, float scale, unsigned char color );
};

#endif