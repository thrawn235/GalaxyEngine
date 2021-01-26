//Client.cpp

#include "GameClient.h"

GameClient::GameClient()
{
	engine = new GameEngine;
	engine->net->SetAddress( (char*)1 );
	engine->net->SetTarget( (char*)2 );
}
void GameClient::Run()
{
	engine->text->PrintString( "this is the Client:" );
	engine->text->EndLine();

	Packet* msg = new Packet;
	//msg->sender = engine->net->GetAddress();
	msg->data = malloc(30);
	msg->data = (char*)"this is a msg from the client";

	engine->net->Send( msg );
}