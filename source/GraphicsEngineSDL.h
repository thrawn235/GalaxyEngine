//====================================
// GraphicsEngineSDL.h
// 2D Graphics engine. SDL Engine
//====================================

//========== include guard ===========
#ifndef GRAPHICS_ENGINE_SDL
#define GRAPHICS_ENGINE_SDL
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
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


class GraphicsEngineSDL : public GraphicsEngine
{
protected:
	GameEngine* engine;

	SDL_Window* window;

public:
										GraphicsEngineSDL 			( GameEngine* engine );
	virtual 							~GraphicsEngineSDL 			();

	virtual 	void 					InitGraphics 				();

	virtual		vector<DisplayMode> 	GetAvailableDisplayModes	();
	virtual 	void 					SetDisplayMode				();

	virtual 	unsigned int 			GetScreenWidth 				();
	virtual 	unsigned int 			GetScreenHeight 			();
	
	virtual 	void 					Update						();
	virtual 	void 					Clear						();
	virtual 	void 					Flip						();

	virtual 	void 					DrawPixel					( Vector2D pos );
};

#endif