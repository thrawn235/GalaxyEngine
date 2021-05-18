//GraphicsEngineDummy.cpp
#include "GraphicsEngineDummy.h"

GraphicsEngineDummy::GraphicsEngineDummy( GameEngine* engine ) : GraphicsEngine( engine )
{
	
}
GraphicsEngineDummy::~GraphicsEngineDummy()
{
	
}
void GraphicsEngineDummy::InitGraphics()
{
	
}

void GraphicsEngineDummy::SetFrameRedraw( bool frameRedraw )
{
	
}

vector<DisplayMode> GraphicsEngineDummy::GetAvailableDisplayModes()
{
	vector<DisplayMode> modes;
	return modes;
}
void GraphicsEngineDummy::SetDisplayMode( DisplayMode mode )
{
	
}
void GraphicsEngineDummy::SetFullScreen( bool fullScreen )
{
	
}
unsigned int GraphicsEngineDummy::GetScreenWidth()
{
	return 0;	
}
unsigned int GraphicsEngineDummy::GetScreenHeight()
{
	return 0;
}
void GraphicsEngineDummy::PreFrame()
{
	
}
void GraphicsEngineDummy::PostFrame()
{
	
}

//Camera
Vector2D GraphicsEngineDummy::GetCamPos()
{
	//
	return Vector2D(0,0);
}
void GraphicsEngineDummy::SetCamPos( Vector2D newPos )
{

}
void GraphicsEngineDummy::SetCamCenter( Vector2D newPos )
{
	
}
Vector2D GraphicsEngineDummy::GetCamCenter()
{
	return Vector2D(0,0);
}

void GraphicsEngineDummy::ClearScreen()
{
	
}
void GraphicsEngineDummy::ClearScreen( unsigned char color )
{
	
}
void GraphicsEngineDummy::DrawPixel( Vector2D pos, unsigned char color )
{
	
}
void GraphicsEngineDummy::DrawLine( Vector2D start, Vector2D end, unsigned char color )
{

}
void GraphicsEngineDummy::DrawHLine( Vector2D start, int length, unsigned char color )
{

}
void GraphicsEngineDummy::DrawVLine( Vector2D start, int length, unsigned char color )
{

}
void GraphicsEngineDummy::DrawRect( Vector2D pos, int width, int height, unsigned char color )
{

}
void GraphicsEngineDummy::DrawFilledRect( Vector2D pos, int width, int height, unsigned char color )
{

}
void GraphicsEngineDummy::DrawCircle( Vector2D pos, int radius, unsigned char color )
{

}
void GraphicsEngineDummy::DrawFilledCircle( Vector2D pos, int radius, unsigned char color )
{

}
void GraphicsEngineDummy::DrawVector( Vector2D pos, Vector2D vec, float scale, unsigned char color )
{

}

//Sprite
void GraphicsEngineDummy::DrawSprite( unsigned long id, Vector2D pos )
{
	
}
void GraphicsEngineDummy::DrawSpriteInSheet( unsigned int id, unsigned int index, Vector2D pos )
{

}

void GraphicsEngineDummy::DrawSpriteSheet( unsigned int id, unsigned int width, Vector2D pos )
{

}

//Text
void GraphicsEngineDummy::DrawString( unsigned int id, string text, Vector2D pos )
{

}
void GraphicsEngineDummy::DrawString( unsigned int id, string text, unsigned int lineLength, Vector2D pos )
{
	
}

void GraphicsEngineDummy::DrawSprite( char* texture, Vector2D pos )
{

}
char* GraphicsEngineDummy::GetSprite( unsigned int id )
{
	return NULL;
}
char* GraphicsEngineDummy::GetSpriteInCollection( unsigned int id, unsigned int index )
{
	return NULL;
}
