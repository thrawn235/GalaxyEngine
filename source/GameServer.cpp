//GameServer.cpp

#include "GameServer.h"

GameServer::GameServer()
{
    engine = new GameEngine;
    
    engine->net->ConfigureAsServer();

    Object* tmp = new Enemy( engine );
    engine->AddObject( tmp );
    tmp = new Enemy( engine );
    engine->AddObject( tmp );
    tmp = new Player( engine );
    engine->AddObject( tmp );

    engine->text->PrintString( "\n\n" );
}
GameServer::~GameServer()
{
    engine->debug->PrintString( "destroying gameserver...\n" );
    delete engine;
}
GameEngine* GameServer::GetEngine()
{
    return engine;
}
void GameServer::Run()
{
    engine->text->PrintString( "================ server ===============:\n" );
    
    engine->text->PrintString( "checking the net for packtes\n" );
    engine->net->Update();
    engine->debug->PrintString( "Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

    while( !engine->net->InboxEmpty() )
    {
        Packet* pkt = engine->net->GetFirstPacketFromInbox();
        if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
        {
            UpdateObjectsFromNet( pkt );
        }
        pkt->~Packet();
    }

    
    engine->debug->PrintString( "these are my objects:\n" );
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->debug->PrintString( "   UID: %i\n", objects[i]->GetUID() );
    }

    //Game Logic for all Objects
    engine->UpdateAll();

    //create and send GameLogic complete packet
    engine->debug->PrintString( "sending Gamelogic comlete packet\n" );
    Packet* ack = new Packet;
    ack->type = NET_PACKET_TYPE_SEND_COMPLETE;
    engine->net->Send( ack );

    engine->debug->PrintString( "======================================:\n\n\n" );
}