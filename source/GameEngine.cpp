#include "GameEngine.h"

GameEngine::GameEngine()
{
	net = new NetEngineLocal;
	#ifdef dos
		text = new TextEngineSTDIO;
	#else
		text = new TextEngineIOStream;
	#endif
}
vector<Object*> GameEngine::GetAllObjects()
{
	return objects;
}