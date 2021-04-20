//====================================
// GraphicsEngineVESA.h
// 2D Graphics engine. uses VESA 3.0
//====================================

//========== include guard ===========
#ifndef GRAPHICS_ENGINE_VESA
#define GRAPHICS_ENGINE_VESA
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;

//djgpp includes:
#include <sys/nearptr.h>
#include <dpmi.h>
#include <go32.h>
#include <pc.h>
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

struct VbeInfoBlock
{
    unsigned char   VbeSignature[4];
    unsigned short  VbeVersion;
    unsigned long   OemStrPtr;
    unsigned char   Capabilities[4];
    unsigned long   VideoModePtr;
    unsigned short  TotalMemory;
    unsigned short  OemSoftwareRev;
    unsigned long   OemVendorNamePtr;
    unsigned long   OemProductNamePtr;
    unsigned long   OemProductRevPtr;
    unsigned char   Reserved[222];
    unsigned char   OemData[256];
}__attribute__( ( packed ) );


struct ModeInfoBlock
{   
    unsigned short  ModeAttributes;
    unsigned char   WinAAttributes;
    unsigned char   WinBAttributes;
    unsigned short  WinGranularity;
    unsigned short  WinSize;
    unsigned short  WinASegment;
    unsigned short  WinBSegment;
    unsigned long   WinFuncPtr;
    unsigned short  BytesPerScanLine;
    unsigned short  XResolution;
    unsigned short  YResolution;
    unsigned char   XCharSize;
    unsigned char   YCharSize;
    unsigned char   NumberOfPlanes;
    unsigned char   BitsPerPixel;
    unsigned char   NumberOfBanks;
    unsigned char   MemoryModel;
    unsigned char   BankSize;
    unsigned char   NumberOfImagesPages;
    unsigned char   Reserved1;
    unsigned char   RedMaskSize;
    unsigned char   RedFieldPosition;
    unsigned char   GreenMaskSize;
    unsigned char   GreenFieldPosition;
    unsigned char   BlueMaskSize;
    unsigned char   BlueFieldPosition;
    unsigned char   RsvdMaskSize;
    unsigned char   RsvdFieldPosition;
    unsigned char   DirectColorModeInfo;
    unsigned long   PhysBasePtr;
    unsigned long   OffScreenMemOffset;
    unsigned char   Reserved2[206];
}__attribute__( ( packed ) );

struct Sprite
{
    char        magic[3];
    uint32_t    width;
    uint32_t    height;
    uint32_t    format;
    uint32_t    bpp;
    char        pixelData;
}__attribute__( ( packed ) );


class GraphicsEngineVESA : public GraphicsEngine
{
protected:
    GameEngine*     engine;

    VbeInfoBlock vbeInfoBlock;

    //Graphicsmode Infos
    bool                initialized;
    int                 screenWidth, screenHeight;
    int                 logicalScreenWidth, logicalScreenHeight;
    int                 screenPadding;
    int                 bitDepth;
    char*               screenMemory;
    int                 totalScreenMemory;
    char*               backBuffer;
    int                 mode;
    int                 oldMode; //mode to go back to

    bool                fullScreen;

    //double buffering
    char*               currentBackBuffer;
    char*               currentScreenMemory;

    //camera
    Vector2D            camPos;


public:
                            GraphicsEngineVESA          ( GameEngine* engine );
                            ~GraphicsEngineVESA         ();

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


    //Graphics Engine VESA specific
    void                    Flip                        ();
    void                    BackToTextMode              ();
    void                    WaitForRetrace              ();
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

    //VESA only
    void                    LoadPalette                 ( char* palette, int numColors );
};

#endif