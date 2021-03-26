//====================================
// GraphicsEngine.h
// 2D Graphics engine.
//====================================

//========== include guard ===========
#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Vector2D.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
#define GRAPHICS_TYPE_DUMMY   0
#define GRAPHICS_TYPE_SDL     1
//====================================

class DisplayMode
{
public:
	unsigned int 	width;
	unsigned int 	height;
	unsigned int 	colorDepth;
	string			name;
};


class GraphicsEngine
{
protected:
public:
										GraphicsEngine 				( GameEngine* engine )	{};
	virtual 							~GraphicsEngine 			()						{};

	virtual 	void 					InitGraphics 				()						= 0;

	virtual		vector<DisplayMode> 	GetAvailableDisplayModes	() 						= 0;
	virtual 	void 					SetDisplayMode				()						= 0;

	virtual 	unsigned int 			GetScreenWidth 				()						= 0;
	virtual 	unsigned int 			GetScreenHeight 			()						= 0;
	
	virtual 	void 					Update						()						= 0;
	virtual 	void 					Clear						()						= 0;
	virtual 	void 					Flip						()						= 0;

	virtual 	void 					DrawPixel					( Vector2D pos )		= 0;
};

#endif