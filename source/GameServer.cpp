//GameServer.cpp

#include "GameServer.h"

GameServer::GameServer()
{
    engine = new GameEngine;
    if( engine->net->GetType() == NET_TYPE_LOCAL_BUFFER )
    {
        engine->net->SetAddress( 2 );
        engine->net->SetTarget( 1 );
    }
}
void GameServer::Run()
{
    engine->text->PrintString( "this is the Server:" );
    engine->text->EndLine();
    while( !engine->net->InboxEmpty() )
    {
        Packet* tmp = engine->net->GetFirstPacketFromInbox();
        engine->text->PrintString( (char*)tmp->data );
        //free( tmp->data );
        delete tmp;
    }

    engine->UpdateAll();
}