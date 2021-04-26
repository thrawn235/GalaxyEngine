//GameServer.cpp

#include "GameServer.h"
#include "GameEngine.h"

GameServer::GameServer()
{  
    engine->SetDebugType( TEXT_TYPE_DUMMY );
    //Client and Server cant use the same Input engine. the client keyup might be used by the server and vice versa.
    engine->SetInputType( INPUT_TYPE_DUMMY );

    engine->net->ConfigureAsServer();

    Object* tmp = new Enemy( engine );
    engine->objects->AddObject( tmp );
    tmp = new Enemy( engine );
    engine->objects->AddObject( tmp );
    tmp = new Player( engine );
    tmp->PrintStats();
    engine->objects->AddObject( tmp );
    tmp->PrintStats();
    tmp = new Enemy( engine );
    engine->objects->AddObject( tmp );

    engine->debug->PrintString( "\n\n" );
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
        
    //engine->debug->PrintString( "server - frametime:%f", engine->time->TicksToMilliSeconds( engine->time->GetCurrentFrameTime() ) );
    if( engine->time->TicksToMilliSeconds( engine->time->GetCurrentFrameTime() )  > 50 )
    {
        engine->time->FrameStart();
        engine->debug->PrintString( "================ server ===============:\n" );
        
        engine->debug->PrintString( "checking the net for packtes\n" );
        engine->net->Update();
        engine->debug->PrintString( "Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

        while( !engine->net->InboxEmpty() )
        {
            Packet* pkt = engine->net->GetFirstPacketFromInbox();
            if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
            {
                UpdateObjectFromNet( pkt );
            }
            pkt->~Packet();
        }

        
        engine->debug->PrintString( "these are my objects:\n" );
        vector<Object*> objects = engine->objects->GetAllObjects();
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

        engine->time->FrameEnd();
        engine->debug->PrintString( "======================================:\n\n\n" );
    }
}