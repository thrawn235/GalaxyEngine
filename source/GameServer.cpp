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

    Object* tmp = new Object( engine );
    engine->AddObject( tmp );
    tmp = new Object( engine );
    engine->AddObject( tmp );
    tmp = new Object( engine );
    engine->AddObject( tmp );
}
void GameServer::Run()
{
    engine->text->PrintString("this is the server:\n");
    engine->text->PrintString("these are my objects:\n");
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->text->PrintString("UID: ");
        engine->text->PrintInt( objects[i]->GetUID() );
        engine->text->EndLine();
    }

    while( !engine->net->InboxEmpty() )
    {
        Packet* tmp = engine->net->GetFirstPacketFromInbox();
        engine->text->PrintString( (char*)tmp->data );
        //free( tmp->data );
        delete tmp;
    }

    engine->UpdateAll();
}