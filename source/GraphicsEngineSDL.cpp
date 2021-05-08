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

    screenWidth = screenHeight = 0;
    screenPadding   = 64;

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


    SetDisplayMode( modes[25] );
    //SetFullScreen( true );
}
GraphicsEngineSDL::~GraphicsEngineSDL()
{
    //Free all textures!
    for( unsigned int i = 0; i < textures.size(); i++ )
    {
        engine->data->FreeData( textures[i].id );
    }
    textures.clear();

    // Close and destroy the window
    SDL_DestroyWindow( window );

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

            screenWidth = mode.width;
            screenHeight = mode.height;
            //set logical screen width
            logicalScreenWidth = screenWidth + ( screenPadding * 2 );
            logicalScreenHeight = screenHeight + ( screenPadding * 2 );

            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );

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
    if( pos.x >= 0 && pos.x < screenWidth && pos.y >= 0 && pos.y < screenHeight )
    {
        SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
        SDL_RenderDrawPoint( renderer, pos.x, pos.y );
    }
}
void GraphicsEngineSDL::DrawLine( Vector2D start, Vector2D end, unsigned char color )
{
    start = start - camPos;
    end = end - camPos;
    if( start.x >= 0 && start.x < logicalScreenWidth && start.y >= 0 && start.y < logicalScreenHeight &&
        end.x >= 0 && end.x < logicalScreenWidth && end.y >= 0 && end.y < logicalScreenHeight)
    {
        SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
        SDL_RenderDrawLine( renderer, start.x, start.y, end.x, end. y);
    }
}
void GraphicsEngineSDL::DrawHLine( Vector2D start, int length, unsigned char color )
{
    start = start - camPos;
    Vector2D end( start.x + length, start.y );
    if( start.x >= 0 && start.x < logicalScreenWidth && start.y >= 0 && start.y < logicalScreenHeight &&
        end.x >= 0 && end.x < logicalScreenWidth && end.y >= 0 && end.y < logicalScreenHeight)
    {
        SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
        SDL_RenderDrawLine( renderer, start.x, start.y, start.x + length, start.y );
    }  
}
void GraphicsEngineSDL::DrawVLine( Vector2D start, int length, unsigned char color )
{
    start = start - camPos;
    Vector2D end( start.x, start.y + length );
    if( start.x >= 0 && start.x < logicalScreenWidth && start.y >= 0 && start.y < logicalScreenHeight &&
        end.x >= 0 && end.x < logicalScreenWidth && end.y >= 0 && end.y < logicalScreenHeight)
    {
        SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
        SDL_RenderDrawLine( renderer, start.x, start.y, start.x, start.y + length );
    }
}
void GraphicsEngineSDL::DrawRect( Vector2D pos, int width, int height, unsigned char color )
{
    pos = pos - camPos;
    Vector2D end( pos.x + width, pos.y + height );
    if( pos.x >= 0 && pos.x < logicalScreenWidth && pos.y >= 0 && pos.y < logicalScreenHeight &&
        end.x >= 0 && end.x < logicalScreenWidth && end.y >= 0 && end.y < logicalScreenHeight)
    {
        SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
        SDL_RenderDrawLine( renderer, pos.x, pos.y, pos.x + width, pos.y );
        SDL_RenderDrawLine( renderer, pos.x + width, pos.y, pos.x + width, pos.y + height );
        SDL_RenderDrawLine( renderer, pos.x, pos.y, pos.x , pos.y + height );
        SDL_RenderDrawLine( renderer, pos.x, pos.y + height, pos.x + width, pos.y + height );
    }
}
void GraphicsEngineSDL::DrawFilledRect( Vector2D pos, int width, int height, unsigned char color )
{
    pos = pos + camPos;
    Vector2D end( pos.x + width, pos.y + height );
    if( pos.x >= 0 && pos.x < logicalScreenWidth && pos.y >= 0 && pos.y < logicalScreenHeight &&
        end.x >= 0 && end.x < logicalScreenWidth && end.y >= 0 && end.y < logicalScreenHeight)
    {
        SDL_SetRenderDrawColor( renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a );
        SDL_Rect rect;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = width;
        rect.h = height;
        SDL_RenderDrawRect( renderer, &rect );
    }
}
void GraphicsEngineSDL::DrawCircle( Vector2D pos, int radius, unsigned char color )
{
    
}
void GraphicsEngineSDL::DrawFilledCircle( Vector2D pos, int radius, unsigned char color )
{
    
}
void GraphicsEngineSDL::DrawVector( Vector2D pos, Vector2D vec, float scale, unsigned char color )
{
    pos = pos - camPos;
    if( pos.x >= 0 && pos.x < screenWidth && pos.y >= 0 && pos.y < screenHeight )
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
}

//Sprite
void GraphicsEngineSDL::DrawSprite( unsigned long id, Vector2D pos )
{ 
    pos = pos - camPos;

    SDL_Texture* texture = GetTexture( id );
    engine->debug->PrintString( "texture loaded...\n" );

    int access, width, height;
    Uint32 format;
    SDL_QueryTexture( texture, &format, &access, &width, &height );


    if( texture != NULL )
    {
        if( pos.x >= 0 && pos.y >= 0 && pos.x + width < logicalScreenWidth && pos.y + height < logicalScreenHeight )
        {

            SDL_Rect srcrect;
            SDL_Rect dstrect;

            srcrect.x = 0;
            srcrect.y = 0;
            srcrect.w = width;
            srcrect.h = height;
            dstrect.x = pos.x;
            dstrect.y = pos.y;
            dstrect.w = width;
            dstrect.h = height;


            SDL_RenderCopy( renderer, texture, &srcrect, &dstrect );
        }
    }      
}

void GraphicsEngineSDL::DrawSpriteInSheet( unsigned int id, unsigned int index, Vector2D pos )
{
    SDL_Texture* texture = GetTextureInCollection( id, index );
    DrawSprite( texture, pos );
}

void GraphicsEngineSDL::DrawSpriteSheet( unsigned int id, unsigned int width, Vector2D pos )
{
    struct Collection
    {
        char        magic[3];
        uint32_t    numItems;
        uint32_t    itemSize;
        char        data;
    }__attribute__( ( packed ) );

    Vector2D savePos = pos;
    unsigned int linePos = 0;

    Collection* collection = (Collection*)engine->data->GetData( id );

    SDL_Texture* texture = GetTextureInCollection( id, 0 );


    if( collection != NULL )
    {
        for( unsigned int i = 0; i < collection->numItems; i++ )
        {
            int access, spriteWidth, spriteHeight;
            Uint32 format;
            SDL_QueryTexture( texture, &format, &access, &spriteWidth, &spriteHeight );

            DrawSpriteInSheet( id, i, pos );
            linePos++;
            pos.x = pos.x + spriteWidth;
            if( linePos >= width )
            {
                linePos = 0;
                pos.x = savePos.x;
                pos.y = pos.y + spriteHeight;
            }
        }
    }
}

//Text
void GraphicsEngineSDL::DrawString( unsigned int id, string text, Vector2D pos )
{
    Vector2D savePos = pos;
    
    SDL_Texture* texture = GetTextureInCollection( id, 0 );
    int access, width, height;
    Uint32 format;
    SDL_QueryTexture( texture, &format, &access, &width, &height );

    for( unsigned int i = 0; i < text.size(); i++ )
    {
        DrawSpriteInSheet( id, text[i] - 32, pos );
        pos.x = pos.x + width;
        if( text[i] == '\n' )
        {
            pos.x = savePos.x;
            pos.y = pos.y + height;
        }
    }
}
void GraphicsEngineSDL::DrawString( unsigned int id, string text, unsigned int lineLength, Vector2D pos )
{
    unsigned int linePos = 0;
    Vector2D savePos = pos;
    
    SDL_Texture* texture = GetTextureInCollection( id, 0 );
    int access, width, height;
    Uint32 format;
    SDL_QueryTexture( texture, &format, &access, &width, &height );

    for( unsigned int i = 0; i < text.size(); i++ )
    {
        DrawSpriteInSheet( id, text[i] - 32, pos );
        pos.x = pos.x + width;
        linePos++;
        if( linePos >= lineLength || text[i] == '\n' )
        {
            linePos = 0;
            pos.x = savePos.x;
            pos.y = pos.y + height;
        }
    }  
}

//SDL only
SDL_Texture* GraphicsEngineSDL::GetTextureInCollection( unsigned long id, unsigned long index )
{
    struct Collection
    {
        char        magic[3];
        uint32_t    numItems;
        uint32_t    itemSize;
        char        data;
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

    Collection* collection = (Collection*)engine->data->GetData( id );

    if( collection != NULL )
    {
        if( index <= collection->numItems )
        {
            for( unsigned int i = 0; i < textures.size(); i++ )
            {
                if( id * 10000 + index == textures[i].id )
                {
                    return textures[i].texture;
                }
            }

            char* data = &collection->data + collection->itemSize * index;
            Sprite* out = (Sprite*)data;

            engine->debug->PrintString( "w:%i h:%i bpp:%i\n", out->width, out->height, out->bpp );

            int pitch = (out->bpp / 8) * out->width; 

            Texture texture;
            texture.texture = SDL_CreateTextureFromSurface( renderer, SDL_CreateRGBSurfaceWithFormatFrom( &out->pixelData, out->width, out->height, out->bpp, pitch, out->format ) );
            texture.id = id * 10000 + index;
            textures.push_back( texture );
            return texture.texture;        
        }
    }
    return NULL;
}
void GraphicsEngineSDL::DrawSprite( SDL_Texture* texture, Vector2D pos )
{
    pos = pos - camPos;

    engine->debug->PrintString( "texture loaded...\n" );

    int access, width, height;
    Uint32 format;
    SDL_QueryTexture( texture, &format, &access, &width, &height );


    if( texture != NULL )
    {
        if( pos.x >= 0 && pos.y >= 0 && pos.x + width < logicalScreenWidth && pos.y + height < logicalScreenHeight )
        {

            SDL_Rect srcrect;
            SDL_Rect dstrect;

            srcrect.x = 0;
            srcrect.y = 0;
            srcrect.w = width;
            srcrect.h = height;
            dstrect.x = pos.x;
            dstrect.y = pos.y;
            dstrect.w = width;
            dstrect.h = height;


            SDL_RenderCopy( renderer, texture, &srcrect, &dstrect );

        }
    } 
}
SDL_Texture* GraphicsEngineSDL::GetTexture( unsigned long id )
{
    for( unsigned int i = 0; i < textures.size(); i++ )
    {
        if( id == textures[i].id )
        {
            return textures[i].texture;
        }
    }


    struct Sprite
    {
        char        magic[3];
        uint32_t    width;
        uint32_t    height;
        uint32_t    format;
        uint32_t    bpp;
        char        pixelData;
    }__attribute__( ( packed ) );

    //texture not found
    Sprite* data = (Sprite*)engine->data->GetData( id );
    engine->debug->PrintString( "w:%i h:%i bpp:%i\n", data->width, data->height, data->bpp );

    int pitch = (data->bpp / 8) * data->width; 

    Texture texture;
    texture.texture = SDL_CreateTextureFromSurface( renderer, SDL_CreateRGBSurfaceWithFormatFrom( &data->pixelData, data->width, data->height, data->bpp, pitch, data->format ) );
    texture.id = id;
    textures.push_back( texture );
    return texture.texture;
}