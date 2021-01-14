//Object

//include Guard
#ifndef OBJECT
#define OBJECT

//stdlib inludes:
#include <iostream>
using namespace std;

//Galaxy includes:
#include "GameEngine.h"

//forward declarations:
class GameEngine;

class Object
{
protected:
	GameEngine* engine;
public:
	Object(GameEngine* engine);
	void Talk();
};

#endif