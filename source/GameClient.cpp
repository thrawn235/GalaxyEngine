//Client.cpp

#include "GameClient.h"

GameClient::GameClient()
{
    engine = new GameEngine;

    if( engine->net->GetType() == NET_TYPE_LOCAL_BUFFER )
    {
        engine->net->SetAddress( 1 );
        engine->net->Connect( 2 );
    }
    if( engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_UDP || engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_TCP )
    {
        #ifdef linux
            engine->net->InitClient();
            engine->debug->PrintString( "connecting to server (join request)...\n" );
            engine->net->Connect( inet_addr( "127.0.0.1" ) );
        #endif
    }

    engine->SetHighestUID( 1000 );
    
    //network variables
    waitingForUpdate            = false;

    //prediction variables
    tickRate                    = 1;
    clientTicksSinceLogicTick   = 0;

    engine->debug->PrintString( "\n\n" );
}
GameClient::~GameClient()
{
    engine->debug->PrintString( "destroying gameclient...\n" );
    delete engine;
}

void GameClient::Run()
{
    //debug:
    engine->debug->PrintString( "===================== client ==================\n" );

    //count ticks (for prediction step)
    clientTicksSinceLogicTick++;

    engine->net->Update();
    engine->debug->PrintString( "Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

    while( !engine->net->InboxEmpty() )
    {
        engine->text->PrintString( "received Packet: " );

        Packet* pkt = engine->net->GetFirstPacketFromInbox();
        NetStats* newStatus = (NetStats*)pkt->data;
        if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
        {   
            Object* foundObject = engine->GetObjectByUID( newStatus->uid );
            if( foundObject != NULL )
            {
                foundObject->LoadStatus( pkt->data );
            }
            else
            {
                //Object is not already in the list, so create one
                if( newStatus->type == OBJECT_TYPE_OBJECT )
                {
                    //text->PrintString( "Adding new Object" );
                    Object* newObject = new Object( engine );
                    newObject->LoadStatus( pkt->data );
                    engine->AddObject( newObject );
                }
                if( newStatus->type == OBJECT_TYPE_PLAYER )
                {
                    //text->PrintString( "Adding new Object" );
                    Object* newObject = new Player( engine );
                    newObject->LoadStatus( pkt->data );
                    engine->AddObject( newObject );
                }
                if( newStatus->type == OBJECT_TYPE_ENEMY )
                {
                    //text->PrintString( "Adding new Object" );
                    Object* newObject = new Enemy( engine );
                    newObject->LoadStatus( pkt->data );
                    engine->AddObject( newObject );
                }
            }
        }
        else if( pkt->type == NET_PACKET_TYPE_SEND_COMPLETE )
        {
            engine->debug->PrintString( "   Packet: Gameround done!\n");
            waitingForUpdate = false;


            tickRate = 1.0 / clientTicksSinceLogicTick;
            engine->debug->PrintString( "       tickrate:%f clientTicks:%i!\n", tickRate, clientTicksSinceLogicTick );
            clientTicksSinceLogicTick = 0;
        }

        //clear memory for the packet
        pkt->~Packet();
    }

    //only update if the server has send a Ack Packet
    if( !waitingForUpdate )
    {
        engine->ClientSideUpdateAll();
        waitingForUpdate = true;
    }

    engine->PredictAll( tickRate );
    engine->RenderAll();

    engine->debug->PrintString( "===============================================\n\n\n" );
}