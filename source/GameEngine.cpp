#include "GameEngine.h"

GameEngine::GameEngine( NetBuffer* localNetBuffer )
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