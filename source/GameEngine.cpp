#include "GameEngine.h"

GameEngine::GameEngine()
{
	text = new TextEngineIOStream;
}
vector<Object*> GameEngine::GetAllObjects()
{
	return objects;
}