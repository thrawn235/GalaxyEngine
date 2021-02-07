//Client.cpp

#include "GameClient.h"

GameClient::GameClient()
{
    engine = new GameEngine;
    if( engine->net->GetType() == NET_TYPE_LOCAL_BUFFER )
    {
        engine->net->SetAddress( 1 );
        engine->net->SetTarget( 2 );
    }
    if( engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_UDP || engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_TCP )
    {
        #ifdef linux
            engine->net->SetTarget( inet_addr( "127.0.0.1" ) );
            engine->net->InitClient();
        #endif
    }

    engine->SetHighestUID( 1000 );
    
    //network variables
    waitingForUpdate            = false;

    //prediction variables
    tickRate                    = 1;
    clientTicksSinceLogicTick   = 0;
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
    engine->debug->PrintString( "Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

    //count ticks (for prediction step)
    clientTicksSinceLogicTick++;

    engine->text->PrintString( "checking the net for packtes\n" );
    engine->net->Update();

    while( !engine->net->InboxEmpty() )
    {
        Packet* pkt = engine->net->GetFirstPacketFromInbox();
        if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
        {
            Object* newStatus = ( Object* )pkt->data;
            newStatus->SetEngine( engine );

            engine->debug->PrintString( "   received Packet: UID:%i Type:%i Pos:%f:%f from:%i rewrite NetAddr to:%i\n", newStatus->GetUID(), newStatus->GetType(), newStatus->GetPos().x, newStatus->GetPos().y, pkt->sender, newStatus->GetEngine()->net->GetAddress() );

            Object* foundObject = engine->GetObjectByUID( newStatus->GetUID() );
            if( foundObject != NULL )
            {
                foundObject->LoadStatus( newStatus );
            }
            else
            {
                //Object is not already in the list, so create one
                if( newStatus->GetType() == OBJECT_TYPE_OBJECT )
                {
                    //text->PrintString( "Adding new Object" );
                    Object* newObject = new Object( engine );
                    newObject->LoadStatus( newStatus );
                    engine->AddObject( newObject );
                }
                if( newStatus->GetType() == OBJECT_TYPE_PLAYER )
                {
                    //text->PrintString( "Adding new Object" );
                    Object* newObject = new Player( engine );
                    newObject->LoadStatus( newStatus );
                    engine->AddObject( newObject );
                }
                if( newStatus->GetType() == OBJECT_TYPE_ENEMY )
                {
                    //text->PrintString( "Adding new Object" );
                    Object* newObject = new Enemy( engine );
                    newObject->LoadStatus( newStatus );
                    engine->AddObject( newObject );
                }
            }
        }
        else if( pkt->type == NET_PACKET_TYPE_SEND_COMPLETE )
        {
            engine->debug->PrintString( "   received Packet: Gameround done!\n");
            waitingForUpdate = false;


            tickRate = 1.0 / clientTicksSinceLogicTick;
            engine->debug->PrintString( "       tickrate:%f clientTicks:%i!\n", tickRate, clientTicksSinceLogicTick );
            clientTicksSinceLogicTick = 0;
        }

        //clear memory for the packet
        pkt->~Packet();
    }
    
    //debug
    /*engine->debug->PrintString("these are my objects:\n");
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->debug->PrintString("   UID: %i\n", objects[i]->GetUID() );
    }*/

    //only update if the server has send a Ack Packet
    if( !waitingForUpdate )
    {
        engine->ClientSideUpdateAll();
        waitingForUpdate = true;
    }

    engine->PredictAll( tickRate );
    engine->RenderAll();

    engine->debug->PrintString( "===========================================:\n\n\n" );
}