#include "GameEngine.h"

GameEngine::GameEngine( vector<NetCommand> *localNetBuffer )
{
	net = new NetEngineLocal( localNetBuffer );
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