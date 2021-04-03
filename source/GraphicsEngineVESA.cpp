//GraphicsEngineVESA.cpp
#include "GraphicsEngineVESA.h"
#include "GameEngine.h"

GraphicsEngineVESA::GraphicsEngineVESA( GameEngine* engine ) : GraphicsEngine( engine )
{
    this->engine = engine;

    screenPadding   = 64;

    backBuffer      = NULL;
    screenMemory    = NULL;
    fullScreen      = true; //always true for dos
    initialized     = false;

    InitGraphics();
}
GraphicsEngineVESA::~GraphicsEngineVESA()
{
    //
    BackToTextMode();
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

    //SetDisplayMode( modes[1] );

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

        //get mode info
        r.x.ax = 0x4F01;
        r.x.cx = newMode;
        r.x.es = ( dosBuffer>>4 ) & 0xFFFF;
        r.x.di = dosBuffer & 0xF;
        __dpmi_int( 0x10, &r );


        ModeInfoBlock modeInfoBlock;
        dosmemget( dosBuffer, sizeof( ModeInfoBlock ), &modeInfoBlock );

        if( mode.width == modeInfoBlock.XResolution && mode.height == modeInfoBlock.YResolution && mode.colorDepth == modeInfoBlock.BitsPerPixel )
        {
            //found the correct mode

            //save width, hight, screenram, backbuffer etc
            //save mode infos:
            screenWidth     = modeInfoBlock.XResolution;
            screenHeight    = modeInfoBlock.YResolution;
            bitDepth        = modeInfoBlock.BitsPerPixel;
            //screenMemory = ( char* )modeInfoBlock.PhysBasePtr;
            __dpmi_meminfo mapping;
            mapping.address     = modeInfoBlock.PhysBasePtr;
            mapping.size        = vbeInfoBlock.TotalMemory << 16;
            __dpmi_physical_address_mapping( &mapping );
            __djgpp_nearptr_enable();
            screenMemory        = ( char* )modeInfoBlock.PhysBasePtr + __djgpp_conventional_base;
            __djgpp_nearptr_disable();
            
            //set logical screen width
            logicalScreenWidth = screenWidth + ( screenPadding*2 );
            logicalScreenHeight = screenHeight + ( screenPadding*2 );

            //for VESA the back buffer is also in screen memory. we just flip the screen window
            backBuffer = screenMemory + ( logicalScreenWidth*logicalScreenHeight );

            printf( "ScreenMemoryAddress:   %p \n",         ( void* )screenMemory   );
            printf( "screenWidth:           %i \n",                  screenWidth    );
            printf( "screenHeight:          %i \n",                  screenHeight   );
            printf( "screenPadding:         %i \n",                  screenPadding  );
            printf( "logicalWidth:          %i \n",         logicalScreenWidth  );
            printf( "logicalHeight:         %i \n",         logicalScreenHeight     );
            printf( "lWidth*lHeight:        %d \n",         logicalScreenWidth*logicalScreenHeight  );
            printf( "backBufferAddress:     %p \n",         ( void* )backBuffer     );
            getchar();    


            //set mode!
            r.x.ax = 0x4F02;
            r.x.bx = newMode | 0b0100000000000000;
            __dpmi_int( 0x10, &r );
            
            
            //set logical scan linie width
            r.x.ax = 0x4F06;
            r.h.bl = 00;
            r.x.cx = logicalScreenWidth;
            __dpmi_int( 0x10, &r );

            //setup for Flip    
            //flip = true;
            currentScreenMemory = screenMemory;
            currentBackBuffer = backBuffer;

            //set display window to proper position
            r.x.ax = 0x4F07;
            r.h.bh = 0;
            r.h.bl = 0;
            r.x.cx = screenPadding;
            r.x.dx = screenPadding;
            __dpmi_int( 0x10, &r );


            initialized = true;

            return;
        }

        i++;
    }

    //could not find the mode 
    printf( "Error! could not find Display Mode...\n" ); 

    return; 
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
void GraphicsEngineVESA::PreFrame()
{
    //
    ClearScreen();
}
void GraphicsEngineVESA::PostFrame()
{
    //
    Flip();
}
void GraphicsEngineVESA::Flip()
{
    if( initialized )
    {
        WaitForRetrace();

        __dpmi_regs r;
        if( currentScreenMemory == screenMemory )
        {
            currentScreenMemory = backBuffer;
            currentBackBuffer = screenMemory;


            r.x.ax = 0x4F07;
            r.h.bh = 0;
            r.h.bl = 0;
            r.x.cx = screenPadding;
            r.x.dx = logicalScreenHeight + screenPadding;
            __dpmi_int( 0x10, &r );
        }
        else
        {
            currentScreenMemory = screenMemory;
            currentBackBuffer = backBuffer;


            r.x.ax = 0x4F07;
            r.h.bh = 0;
            r.h.bl = 0;
            r.x.cx = screenPadding;
            r.x.dx = screenPadding;
            __dpmi_int( 0x10, &r );
        }
    }
}

//Camera
Vector2D GraphicsEngineVESA::GetCamPos()
{
   //
    return camPos;
}
void GraphicsEngineVESA::SetCamPos( Vector2D newPos )
{
   //
    camPos = newPos;
}
void GraphicsEngineVESA::SetCamCenter( Vector2D newPos )
{
    if( initialized )
    {
        newPos.x = newPos.x - (  screenWidth / 2  );
        newPos.y = newPos.y - (  screenHeight / 2  );
        camPos = newPos;
    }
}
Vector2D GraphicsEngineVESA::GetCamCenter()
{
    //
    return Vector2D( camPos.x + (  screenWidth / 2  ), camPos.y + (  screenHeight / 2  ) );
}

void GraphicsEngineVESA::ClearScreen()
{
    //color black, color index 0
    if( initialized )
    {
        int startAddress = ( int )currentBackBuffer + ( screenPadding * logicalScreenWidth + screenPadding );
        int endAddress = startAddress + ( screenHeight * logicalScreenWidth );

        asm( "mov $0, %%al;"
             "shl $8, %%eax;"
             "mov $0, %%al;"
             "shl $8, %%eax;"
             "mov $0, %%al;"
             "shl $8, %%eax;"
             "mov $0, %%al;"
             "loop%=:;"
             "   mov %%eax, ( %%edi );"
             "   add $4, %%edi;"
             "   cmp %1, %%edi;"
             "   jb loop%=;"
             :
             :"D"( startAddress ), "m"( endAddress )
             :"eax", "memory" );
    }
}
void GraphicsEngineVESA::ClearScreen( unsigned char color )
{
    if( initialized )
    {
        int startAddress = ( int )currentBackBuffer + ( screenPadding * logicalScreenWidth + screenPadding );
        int endAddress = startAddress + ( screenHeight * logicalScreenWidth );

        asm( "mov %2, %%al;"
             "shl $8, %%eax;"
             "mov %2, %%al;"
             "shl $8, %%eax;"
             "mov %2, %%al;"
             "shl $8, %%eax;"
             "mov %2, %%al;"
             "loop%=:;"
             "   mov %%eax, ( %%edi );"
             "   add $4, %%edi;"
             "   cmp %1, %%edi;"
             "   jb loop%=;"
             :
             :"D"( startAddress ), "m"( endAddress ), "m"( color )
             :"eax", "memory" );
    }
}
void GraphicsEngineVESA::DrawPixel( Vector2D pos, unsigned char color )
{
    if( initialized )
    {
        pos = pos + screenPadding;
        pos = pos - camPos;
        //and assembly
        if( pos.x > 0 && pos.y > 0 && pos.x < logicalScreenWidth && pos.y < logicalScreenHeight )
        {
            currentBackBuffer[( int )( ( int )pos.y * logicalScreenWidth+ ( int )pos.x )] = color;
        }
    }
}

void GraphicsEngineVESA::BackToTextMode()
{
    //set mode:
    __dpmi_regs r;
    r.x.ax = 03;
    __dpmi_int( 0x10, &r );
}
void GraphicsEngineVESA::WaitForRetrace()
{
    /* wait until done with vertical retrace */
    while  ( ( inportb( 0x03da ) & 0x08 ) != 8 ) {};
    /* wait until done refreshing */
    while ( ( inportb( 0x03da ) & 0x08 ) == 8 ) {};
}
void GraphicsEngineVESA::DrawLine( Vector2D start, Vector2D end, unsigned char color )
{
    //not by me. method is from brakeen
    //no boundary checks
    start = start + screenPadding;
    end = end + screenPadding;
    start = start - camPos;
    end = end - camPos;

    if(     start.x > 0 && start.y > 0 && start.x < logicalScreenWidth && start.y < logicalScreenHeight &&
        end.x > 0 && end.y > 0 && end.x < logicalScreenWidth && end.y < logicalScreenHeight )
    {
        #define sgn( x ) ( ( x<0 )?-1:( ( x>0 )?1:0 ) )

        

        int x1 = start.x;
        int y1 = start.y;
        int x2 = end.x;
        int y2 = end.y;

        int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

        dx=x2-x1;      /* the horizontal distance of the line */
        dy=y2-y1;      /* the vertical distance of the line */
        dxabs=abs( dx );
        dyabs=abs( dy );
        sdx=sgn( dx );
        sdy=sgn( dy );
        x=dyabs>>1;
        y=dxabs>>1;
        px=x1;
        py=y1;

        //VGA[( py<<8 )+( py<<6 )+px]=color;
        currentBackBuffer[py * logicalScreenWidth + px] = color;

        if ( dxabs>=dyabs ) /* the line is more horizontal than vertical */
        {
            for( i=0;i<dxabs;i++ )
            {
                y+=dyabs;
                if ( y>=dxabs )
                {
                    y-=dxabs;
                    py+=sdy;
                }
                px+=sdx;
                //plot_pixel( px,py,color );
                currentBackBuffer[py * logicalScreenWidth + px] = color;
            }
        }
        else /* the line is more vertical than horizontal */
        {
            for( i=0;i<dyabs;i++ )
            {
                x+=dxabs;
                if ( x>=dyabs )
                {
                    x-=dyabs;
                    px+=sdx;
                }
                py+=sdy;
                //plot_pixel( px,py,color );
                currentBackBuffer[py * logicalScreenWidth + px] = color;
            }
        }
    }
}
void GraphicsEngineVESA::DrawHLine( Vector2D start, int length, unsigned char color )
{
    //assembly and long pointers could speed it up. probably not worth it though
    start = start + screenPadding;
    start = start - camPos;
    
    if(     start.x > 0 && start.y > 0 && start.x < logicalScreenWidth && start.y < logicalScreenHeight &&
        start.x + length > 0 && start.x + length < logicalScreenWidth )
    {
        
        int startAddress = ( int )start.y * logicalScreenWidth + ( int )start.x;
        for( int i = 0; i < length; i++ )
        {
            currentBackBuffer[startAddress+i] = color;
        }
    }
}
void GraphicsEngineVESA::DrawVLine( Vector2D start, int length, unsigned char color )
{
    start = start + screenPadding;
    start = start - camPos;

    if(     start.x > 0 && start.y > 0 && start.x < logicalScreenWidth && start.y < logicalScreenHeight &&
        start.y + length > 0 && start.y + length < logicalScreenHeight )
    {
        
        int startAddress = ( int )start.y * logicalScreenWidth + ( int )start.x;
        for( int i = 0; i < length; i++ )
        {
            currentBackBuffer[startAddress] = color;
            startAddress = startAddress + logicalScreenWidth;
        }
    }
}
void GraphicsEngineVESA::DrawRect( Vector2D pos, int width, int height, unsigned char color )
{
    //Boundary Checks are done in Line Methods
    DrawVLine( pos, height+1, color );
    DrawVLine( Vector2D( pos.x+width, pos.y ), height+1, color );
    DrawHLine( pos, width, color );
    DrawHLine( Vector2D( pos.x, pos.y+height ), width, color );
}
void GraphicsEngineVESA::DrawFilledRect( Vector2D pos, int width, int height, unsigned char color )
{
    pos = pos + screenPadding;
    pos = pos - camPos;

    if( pos.x > 0 && pos.y > 0 && pos.x < logicalScreenWidth && pos.y < logicalScreenHeight )
    {
        if( pos.x+width > 0 && pos.y+height > 0 && pos.x+width < logicalScreenWidth && pos.y+height < logicalScreenHeight )
        {
            if( width % 4 == 0 )
            {
                int startAddress = ( int )currentBackBuffer + ( ( int )pos.y * logicalScreenWidth + ( int )pos.x );
                asm( "mov %2, %%al;"
                    "shl $8, %%eax;"
                    "mov %2, %%al;"
                    "shl $8, %%eax;"
                    "mov %2, %%al;"
                    "shl $8, %%eax;"
                    "mov %2, %%al;"
                    "mov $0, %%ebx;"
                    "loop1%=:;"
                    "   mov $0, %%ecx;"
                    "   loop2%=:;"
                    "       mov %%eax, ( %%edi, %%ecx );"
                    "       add $4, %%ecx;"
                    "       cmp %2, %%ecx;"
                    "       jb loop2%=;"
                    "   add %1, %%edi;"
                    "   inc %%ebx;"
                    "   cmp %3, %%ebx;"
                    "   jb loop1%=;"
                    :
                    :"D"( startAddress ), "m"( logicalScreenWidth ), "m"( width ), "m"( height )
                    :"eax", "ebx", "ecx", "memory" ); 
            }
            else
            {
                int startAddress = ( int )currentBackBuffer + ( ( int )pos.y * logicalScreenWidth + ( int )pos.x );
                int widthMinus4 = width - 4;
                asm( "mov %2, %%al;"
                    "shl $8, %%eax;"
                    "mov %2, %%al;"
                    "shl $8, %%eax;"
                    "mov %2, %%al;"
                    "shl $8, %%eax;"
                    "mov %2, %%al;"
                    "mov $0, %%ebx;"
                    "loop1%=:;"
                    "   mov $0, %%ecx;"
                    "   loop2%=:;"
                    "       mov %%eax, ( %%edi, %%ecx );"
                    "       add $4, %%ecx;"
                    "       cmp %2, %%ecx;"
                    "       jb loop2%=;"
                    "   loop3%=:;"
                    "       movb %%al, ( %%edi, %%ecx );"
                    "       inc %%ecx;"
                    "       cmp %4, %%ecx;"
                    "       jb loop3%=;"
                    "   add %1, %%edi;"
                    "   inc %%ebx;"
                    "   cmp %3, %%ebx;"
                    "   jb loop1%=;"
                    :
                    :"D"( startAddress ), "m"( logicalScreenWidth ), "m"( widthMinus4 ), "m"( height ), "m"( width )
                    :"eax", "ebx", "ecx", "memory" ); 
            }
        }
    }
}
void GraphicsEngineVESA::DrawCircle( Vector2D pos, int radius, unsigned char color )
{
    //incredibly dumb and horrendously slow!

    pos = pos + screenPadding;
    pos = pos - camPos;

    Vector2D startCoord( pos.x - radius, pos.y - radius );
    if(     startCoord.x > 0 && startCoord.y > 0 && startCoord.x < logicalScreenWidth && startCoord.y < logicalScreenHeight &&
        startCoord.x + ( 2*radius ) > 0 && startCoord.y + ( 2*radius ) > 0 && startCoord.x + ( 2*radius ) < logicalScreenWidth && startCoord.y + ( 2*radius ) < logicalScreenHeight )
    {
        for( int x = startCoord.x; x <= startCoord.x + ( 2*radius ); x++ )
        {
            for( int y = startCoord.y; y <= startCoord.y + ( 2*radius ); y++ )
            {
                if( ( int )pos.DistanceFrom( Vector2D( x,y ) ) == radius )
                {
                    currentBackBuffer[y * logicalScreenWidth + x] = color;
                }
            }
        } 
    }
}
void GraphicsEngineVESA::DrawFilledCircle( Vector2D pos, int radius, unsigned char color )
{
    //incredibly dumb and horrendously slow!

    pos = pos + screenPadding;
    pos = pos - camPos;

    Vector2D startCoord( pos.x - radius, pos.y - radius );
    if(     startCoord.x > 0 && startCoord.y > 0 && startCoord.x < logicalScreenWidth && startCoord.y < logicalScreenHeight &&
        startCoord.x + ( 2*radius ) > 0 && startCoord.y + ( 2*radius ) > 0 && startCoord.x + ( 2*radius ) < logicalScreenWidth && startCoord.y + ( 2*radius ) < logicalScreenHeight )
    {
        for( int x = startCoord.x; x <= startCoord.x + ( 2*radius ); x++ )
        {
            for( int y = startCoord.y; y <= startCoord.y + ( 2*radius ); y++ )
            {
                if( ( int )pos.DistanceFrom( Vector2D( x,y ) ) <= radius )
                {
                    currentBackBuffer[y * logicalScreenWidth + x] = color;
                }
            }
        } 
    }
}
void GraphicsEngineVESA::DrawVector( Vector2D pos, Vector2D vec, float scale, unsigned char color )
{
    //Draw Dot at origin
    DrawPixel( Vector2D( pos.x-1, pos.y-1 ), color );
    DrawPixel( Vector2D( pos.x, pos.y-1   ), color );
    DrawPixel( Vector2D( pos.x+1, pos.y-1 ), color );
    DrawPixel( Vector2D( pos.x-1, pos.y   ), color );
    DrawPixel( Vector2D( pos.x, pos.y     ), color );
    DrawPixel( Vector2D( pos.x+1, pos.y   ), color );
    DrawPixel( Vector2D( pos.x-1, pos.y+1 ), color );
    DrawPixel( Vector2D( pos.x, pos.y+1   ), color );
    DrawPixel( Vector2D( pos.x+1, pos.y+1 ), color );

    //Draw Line for Direction
    DrawLine( pos, ( vec * scale )+pos, color );
}