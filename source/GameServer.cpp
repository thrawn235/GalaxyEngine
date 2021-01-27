//GameServer.cpp

#include "GameServer.h"

GameServer::GameServer()
{
    engine = new GameEngine;
    engine->net->SetAddress( 2 );
    engine->net->SetTarget( 1 );
}
void GameServer::Run()
{
    engine->text->PrintString( "this is the Server:" );
    engine->text->EndLine();
    if( !engine->net->InboxEmpty() )
    {
        engine->text->PrintString( (char*)engine->net->GetFirstPacketFromInbox()->data );
    }
}