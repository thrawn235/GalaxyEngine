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