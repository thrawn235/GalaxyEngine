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
void GraphicsEngineDummy::SetDisplayMode()
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
void GraphicsEngineDummy::Update()
{
	
}
void GraphicsEngineDummy::Clear()
{
	
}
void GraphicsEngineDummy::Flip()
{
	
}
void GraphicsEngineDummy::DrawPixel( Vector2D pos )
{
	
}