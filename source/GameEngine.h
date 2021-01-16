//Game Engine

//include Guard
#ifndef GAMEENGINE
#define GAMEENGINE

//stdlib:
#include <vector>
using namespace std;

//Galaxy includes
#include "Object.h"
#include "TextEngine.h"
#include "TextEngineIOStream.h"

//forward declaration:
class Object;

class GameEngine
{
protected:
	vector<Object*> objects;

public:
	TextEngine* 	text;

					GameEngine 		();
	vector<Object*> GetAllObjects 	();
};

//include Guard End
#endif