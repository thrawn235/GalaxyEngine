//GameServer.cpp

#include "GameServer.h"

GameServer::GameServer( NetBuffer* localNetBuffer )
{
	engine = new GameEngine( localNetBuffer );	
}
void GameServer::Run()
{
	engine->text->PrintString( "this is the Server:" );
	engine->text->EndLine();
}