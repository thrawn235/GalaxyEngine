//GameServer.cpp

#include "GameServer.h"

GameServer::GameServer()
{
	engine = new GameEngine;	
}
void GameServer::Run()
{
	engine->text->PrintString( "this is the Server:" );
	engine->text->EndLine();
}