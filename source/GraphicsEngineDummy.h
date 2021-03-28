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
    
    virtual     void                    Update                      ();
    virtual     void                    Clear                       ();
    virtual     void                    Flip                        ();

    virtual     void                    DrawPixel                   ( Vector2D pos, unsigned char color );
};

#endif