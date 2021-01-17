//Client.cpp

#include "GameClient.h"

GameClient::GameClient( NetBuffer* localNetBuffer )
{
	engine = new GameEngine( localNetBuffer );
}
void GameClient::Run()
{
	engine->text->PrintString( "this is the Client:" );
	engine->text->EndLine();
}