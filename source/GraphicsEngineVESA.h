//====================================
// GraphicsEngineVESA.h
// 2D Graphics engine. uses VESA
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


class GraphicsEngineVESA : public GraphicsEngine
{
protected:
	GameEngine* 	engine;

	//Graphicsmode Infos
	int 				screenWidth, screenHeight;
	int 				logicalScreenWidth, logicalScreenHeight;
	int 				screenPadding;
	int 				bitDepth;
	char* 				screenMemory;
	int 				totalScreenMemory;
	char* 				backBuffer;
	int 				mode;
	int 				oldMode; //mode to go back to

	//double buffering
	bool 				flip;
	char* 				currentBackBuffer;
	char* 				currentScreenMemory;


public:
										GraphicsEngineVESA 			( GameEngine* engine );
	virtual 							~GraphicsEngineVESA			();

	virtual 	void 					InitGraphics 				();

	virtual		vector<DisplayMode> 	GetAvailableDisplayModes	();
	virtual 	void 					SetDisplayMode				( DisplayMode mode );
	virtual 	void 					SetFullScreen				( bool fullScreen );

	virtual 	unsigned int 			GetScreenWidth 				();
	virtual 	unsigned int 			GetScreenHeight 			();
	
	virtual 	void 					Update						();
	virtual 	void 					Clear						();
	virtual 	void 					Flip						();

	virtual 	void 					DrawPixel					( Vector2D pos, unsigned char color );


	virtual 	void 					BackToTextMode				();
};

#endif