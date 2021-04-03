//GraphicsEngineSDL.cpp
#include "GraphicsEngineSDL.h"
#include "GameEngine.h"

GraphicsEngineSDL::GraphicsEngineSDL( GameEngine* engine ) : GraphicsEngine( engine )
{
    colors[0].r = 0;
    colors[0].g = 0;
    colors[0].b = 0;
    colors[0].a = 255;

    colors[1].r = 0;
    colors[1].g = 0;
    colors[1].b = 255;
    colors[1].a = 255;

    colors[2].r = 0;
    colors[2].g = 255;
    colors[2].b = 0;
    colors[2].a = 255;

    colors[3].r = 0;
    colors[3].g = 255;
    colors[3].b = 255;
    colors[3].a = 255;

    colors[4].r = 255;
    colors[4].g = 0;
    colors[4].b = 0;
    colors[4].a = 255;

    colors[5].r = 255;
    colors[5].g = 0;
    colors[5].b = 255;
    colors[5].a = 255;

    colors[6].r = 165;
    colors[6].g = 42;
    colors[6].b = 42;
    colors[6].a = 255;

    colors[7].r = 192;
    colors[7].g = 192;
    colors[7].b = 192;
    colors[7].a = 255;

    colors[8].r = 128;
    colors[8].g = 128;
    colors[8].b = 128;
    colors[8].a = 255;

    colors[9].r = 128;
    colors[9].g = 128;
    colors[9].b = 255;
    colors[9].a = 255;

    colors[10].r = 128;
    colors[10].g = 255;
    colors[10].b = 128;
    colors[10].a = 255;

    colors[11].r = 128;
    colors[11].g = 255;
    colors[11].b = 255;
    colors[11].a = 255;

    colors[12].r = 255;
    colors[12].g = 128;
    colors[12].b = 128;
    colors[12].a = 255;

    colors[13].r = 255;
    colors[13].g = 128;
    colors[13].b = 255;
    colors[13].a = 255;

    colors[14].r = 255;
    colors[14].g = 255;
    colors[14].b = 0;
    colors[14].a = 255;

    colors[15].r = 255;
    colors[15].g = 255;
    colors[15].b = 255;
    colors[15].a = 255;

    this->engine = engine;

    Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if( subsystem_init == 0 )
    {
        SDL_Init( 0 );
    }
    if( !(subsystem_init & SDL_INIT_VIDEO) )
    {
        SDL_InitSubSystem( SDL_INIT_VIDEO );
    }

    vector<DisplayMode> modes = GetAvailableDisplayModes();
    for( unsigned int i = 0; i < modes.size(); i++ )
    {
        engine->debug->PrintString( "%s\n", modes[i].name.c_str() );
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow( "An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL );

    

    // Check that the window was successfully created
    if( window == NULL )
    {
        // In the case that the window could not be made...
        this->engine->debug->PrintString("Could not create window: %s\n", SDL_GetError());
        this->engine->Quit();
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())


    SetDisplayMode( modes[30] );
    //SetFullScreen( true );
}
GraphicsEngineSDL::~GraphicsEngineSDL()
{
    // Close and destroy the window
    SDL_DestroyWindow(window);

    SDL_QuitSubSystem( SDL_INIT_VIDEO );

    // Clean up
    Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if( subsystem_init == 0 )
    {
        SDL_Quit();
    } 
}
void GraphicsEngineSDL::InitGraphics()
{
    
}
vector<DisplayMode> GraphicsEngineSDL::GetAvailableDisplayModes()
{
    vector<DisplayMode> modes;

    DisplayMode mode;

    SDL_DisplayMode SDLmode;
    Uint32 f;
    unsigned int displayModeCount = SDL_GetNumDisplayModes( 0 );
    if( displayModeCount < 1 )
    {
        engine->debug->PrintString("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
        engine->Quit();
    }
    engine->debug->PrintString("SDL_GetNumDisplayModes: %i\n", displayModeCount);

    for( unsigned int i = 0; i < displayModeCount; ++i )
    {
        if( SDL_GetDisplayMode( 0, i, &SDLmode ) != 0 )
        {
            engine->debug->PrintString("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
            engine->Quit();
        }
        f = SDLmode.format;

        //engine->debug->PrintString("Mode %i\tbpp %i\t%s\t%i x %i\n", i, SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f), SDLmode.w, SDLmode.h );
    
        mode.name.clear();
        mode.width = SDLmode.w;
        mode.height = SDLmode.h;
        mode.colorDepth = SDL_BITSPERPIXEL(f);
        mode.name.append( engine->text->SPrintString( "%i x %i x %ibpp", SDLmode.w, SDLmode.h, SDL_BITSPERPIXEL(f) ) );
        //engine->text->PrintString( "%s\n", mode.name.c_str() );
        modes.push_back( mode );
    }

    return modes;
}
void GraphicsEngineSDL::SetDisplayMode( DisplayMode mode )
{
    //

    SDL_DisplayMode SDLmode;
    Uint32 f;
    unsigned int displayModeCount = SDL_GetNumDisplayModes( 0 );
    if( displayModeCount < 1 )
    {
        engine->debug->PrintString("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
        engine->Quit();
    }

    for( unsigned int i = 0; i < displayModeCount; ++i )
    {
        if( SDL_GetDisplayMode( 0, i, &SDLmode ) != 0 )
        {
            engine->debug->PrintString("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
            engine->Quit();
        }
        f = SDLmode.format;

        if( mode.width == (unsigned int)SDLmode.w && mode.height == (unsigned int)SDLmode.h && mode.colorDepth == (unsigned int)SDL_BITSPERPIXEL(f) )
        {
            SDL_SetWindowDisplayMode( window, &SDLmode );
            SDL_SetWindowSize( window, mode.width, mode.height );

            renderer = SDL_CreateRenderer( window, -1, 0 );


            return;
        }
    }

}
void GraphicsEngineSDL::SetFullScreen( bool fullScreen )
{
    if( fullScreen )
    {
        SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN );
    }
    else
    {
        SDL_SetWindowFullscreen( window, 0 );
    }
}
unsigned int GraphicsEngineSDL::GetScreenWidth()
{
    int w;
    SDL_GetWindowSize( window, &w, NULL );
    return (unsigned int)w; 
}
unsigned int GraphicsEngineSDL::GetScreenHeight()
{
    int h;
    SDL_GetWindowSize( window, NULL, &h );
    return (unsigned int)h;   
}
void GraphicsEngineSDL::PreFrame()
{
    //
    ClearScreen();   
}
void GraphicsEngineSDL::PostFrame()
{
    //
    SDL_RenderPresent( renderer );
}

//Camera
Vector2D GraphicsEngineSDL::GetCamPos()
{
   //
    return camPos;
}
void GraphicsEngineSDL::SetCamPos( Vector2D newPos )
{
   //
    camPos = newPos;
}
void GraphicsEngineSDL::SetCamCenter( Vector2D newPos )
{
    newPos.x = newPos.x - (  GetScreenWidth() / 2  );
    newPos.y = newPos.y - (  GetScreenHeight() / 2  );
    camPos = newPos;
}
Vector2D GraphicsEngineSDL::GetCamCenter()
{
    //
    return Vector2D( camPos.x + (  GetScreenWidth() / 2  ), camPos.y + (  GetScreenHeight() / 2  ) );
}

void GraphicsEngineSDL::ClearScreen()
{
    unsigned char color = COLOR_BLACK;
    SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
    SDL_RenderClear( renderer );
}
void GraphicsEngineSDL::ClearScreen( unsigned char color )
{
    SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
    SDL_RenderClear( renderer );
}
void GraphicsEngineSDL::DrawPixel( Vector2D pos, unsigned char color )
{
    pos = pos - camPos;
    SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
    SDL_RenderDrawPoint( renderer, pos.x, pos.y );
}