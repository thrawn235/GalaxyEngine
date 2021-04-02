//GraphicsEngineVESA.cpp
#include "GraphicsEngineVESA.h"
#include "GameEngine.h"

GraphicsEngineVESA::GraphicsEngineVESA( GameEngine* engine ) : GraphicsEngine( engine )
{
    this->engine = engine;

    screenPadding   = 64;

    backBuffer      = NULL;
    screenMemory    = NULL;
    flip            = false;
    fullScreen      = true; //always true for dos

    InitGraphics();
}
GraphicsEngineVESA::~GraphicsEngineVESA()
{
    BackToTextMode();

    //__djgpp_nearptr_disable(); better call that in engine proper
}
void GraphicsEngineVESA::InitGraphics()
{

    //Get Graphics Card Infos----------------------------------
    long dosBuffer;
    dosBuffer = __tb & 0xFFFFF;

    __dpmi_regs r;
    r.x.ax = 0x4F00;
    r.x.es = ( dosBuffer>>4 ) & 0xFFFF;
    r.x.di = dosBuffer & 0xF;
    __dpmi_int( 0x10, &r );

    dosmemget( dosBuffer, sizeof( VbeInfoBlock ), &vbeInfoBlock );
    //--------------------------------------------------------- 

    long mode_ptr; 
    printf( "VBE Signature: %s\n", vbeInfoBlock.VbeSignature );
    printf( "VBE Version: %hu \n", vbeInfoBlock.VbeVersion );
    mode_ptr = ( ( vbeInfoBlock.OemStrPtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemStrPtr & 0xFFFF );
    printf( "OEM String: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
    printf( "Capabilities: %li \n", ( long )vbeInfoBlock.Capabilities );
    printf( "VideoModes Ptr: %p \n", ( void* )vbeInfoBlock.VideoModePtr );
    printf( "total Memory: %hu \n", vbeInfoBlock.TotalMemory );
    printf( "software rev: %hu \n", vbeInfoBlock.OemSoftwareRev );
    mode_ptr = ( ( vbeInfoBlock.OemVendorNamePtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemVendorNamePtr & 0xFFFF );
    printf( "Vendor Name: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
    mode_ptr = ( ( vbeInfoBlock.OemProductNamePtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemProductNamePtr & 0xFFFF );
    printf( "Product Name: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
    mode_ptr = ( ( vbeInfoBlock.OemProductRevPtr & 0xFFFF0000 ) >> 12 ) + ( vbeInfoBlock.OemProductRevPtr & 0xFFFF );
    printf( "Product Rev: %s \n", ( char* )mode_ptr + __djgpp_conventional_base );
    getchar();
    



    //Get Old Mode:
    r.x.ax = 0x4F03;
    __dpmi_int( 0x10, &r );
    oldMode = r.x.bx;

    printf( "oldMode: %x \n", oldMode );




    vector<DisplayMode> modes = GetAvailableDisplayModes();
    for( unsigned int i = 0; i < modes.size(); i++ )
    {
        engine->debug->PrintString( "%s\n", modes[i].name.c_str() );
    }

}
vector<DisplayMode> GraphicsEngineVESA::GetAvailableDisplayModes()
{
    vector<DisplayMode> modes;
    DisplayMode displayMode;

    long dosBuffer;
    dosBuffer = __tb & 0xFFFFF;

    __djgpp_nearptr_enable();
    unsigned long segment = ( vbeInfoBlock.VideoModePtr & 0xFFFF0000 ) >> 12;
    unsigned long offset = vbeInfoBlock.VideoModePtr & 0x0000FFFF;
    unsigned long final = segment + offset + __djgpp_conventional_base; 
    printf("seg:%p, off:%p, linear:%p, final:%p\n", (void*)segment, (void*)offset, (void*)(segment+offset), (void*)final );
    __djgpp_nearptr_disable();

    __dpmi_regs r;
    
    uint16_t* vesaModes = (uint16_t*)final;
    printf( "modeptr %p\n", vesaModes );
    unsigned int i = 0;
    while( vesaModes[i] != 0xFFFF )
    {
        printf("Mode %i: %X\n", i, vesaModes[i] );
        uint16_t newMode = vesaModes[i];

        dosBuffer = __tb & 0xFFFFF;

        r.x.ax = 0x4F01;
        r.x.cx = newMode;
        r.x.es = ( dosBuffer>>4 ) & 0xFFFF;
        r.x.di = dosBuffer & 0xF;
        __dpmi_int( 0x10, &r );


        ModeInfoBlock modeInfoBlock;

        dosmemget( dosBuffer, sizeof( ModeInfoBlock ), &modeInfoBlock );
        printf("Mode %i: %X\n", i, vesaModes[i] );
        printf( "ModeAttributes: %u \n",    modeInfoBlock.ModeAttributes        );
        printf( "WinSize: %u \n",           modeInfoBlock.WinSize               );
        printf( "WinFuncPtr: %p \n",        ( void* )modeInfoBlock.WinFuncPtr   );
        printf( "BytesPerScanline: %u \n",  modeInfoBlock.BytesPerScanLine      );
        printf( "XResolution: %hu \n",      modeInfoBlock.XResolution           );
        printf( "YResolution: %hu \n",      modeInfoBlock.YResolution           );
        printf( "XCharSize: %hu \n",        modeInfoBlock.XCharSize             );
        printf( "YCharSize: %hu \n",        modeInfoBlock.YCharSize             );
        printf( "NumberOfPlanes: %hu \n",   modeInfoBlock.NumberOfPlanes        );
        printf( "BitsPerPixel: %hu \n",     modeInfoBlock.BitsPerPixel          );
        printf( "NumberOfBanks: %hu \n",    modeInfoBlock.NumberOfBanks         );
        printf( "MemoryModel: %hu \n",      modeInfoBlock.MemoryModel           );
        printf( "BankSize: %hu \n",         modeInfoBlock.BankSize              );
        printf( "PhysBasePtr: %p \n",       ( void* )modeInfoBlock.PhysBasePtr  );
        printf( "ModeAttributes: %u \n",    modeInfoBlock.ModeAttributes        );
        
        displayMode.name.clear();
        displayMode.width = modeInfoBlock.XResolution;
        displayMode.height = modeInfoBlock.YResolution;
        displayMode.colorDepth = modeInfoBlock.BitsPerPixel;
        displayMode.name.append( engine->text->SPrintString( "%X", vesaModes[i] ) );
        engine->text->PrintString( "%X\n", vesaModes[i] );
        modes.push_back( displayMode );
        i++;
    }   

    return modes;
}
void GraphicsEngineVESA::SetDisplayMode( DisplayMode mode )
{
    
}
void GraphicsEngineVESA::SetFullScreen( bool fullScreen )
{
    //
    this->fullScreen = true; //always true for dos
}
unsigned int GraphicsEngineVESA::GetScreenWidth()
{
    //
    return screenWidth; 
}
unsigned int GraphicsEngineVESA::GetScreenHeight()
{
    //
    return screenHeight;
}
void GraphicsEngineVESA::Update()
{
    
}
void GraphicsEngineVESA::Clear()
{
    
}
void GraphicsEngineVESA::Flip()
{
    
}
void GraphicsEngineVESA::DrawPixel( Vector2D pos, unsigned char color )
{
    
}

void GraphicsEngineVESA::BackToTextMode()
{

}