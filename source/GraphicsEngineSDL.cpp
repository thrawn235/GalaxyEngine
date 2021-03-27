//GraphicsEngineSDL.cpp
#include "GraphicsEngineSDL.h"
#include "GameEngine.h"

GraphicsEngineSDL::GraphicsEngineSDL( GameEngine* engine ) : GraphicsEngine( engine )
{
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

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

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
	return modes;
}
void GraphicsEngineSDL::SetDisplayMode()
{
	
}
unsigned int GraphicsEngineSDL::GetScreenWidth()
{
	return 0;	
}
unsigned int GraphicsEngineSDL::GetScreenHeight()
{
	return 0;
}
void GraphicsEngineSDL::Update()
{
	
}
void GraphicsEngineSDL::Clear()
{
	
}
void GraphicsEngineSDL::Flip()
{
	
}
void GraphicsEngineSDL::DrawPixel( Vector2D pos )
{
	
}