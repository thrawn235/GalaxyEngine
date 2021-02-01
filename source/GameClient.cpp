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
    engine->SetHighestUID( 1000 );
    waitingForUpdate            = false;

    tickRate                    = 1;
    clientTicksSinceLogicTick   = 0;
}
void GameClient::Run()
{
    //debug:
    engine->debug->PrintString( "this is the client:\n" );
    engine->debug->PrintString( "Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

    clientTicksSinceLogicTick++;

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

            tickRate = 1 / clientTicksSinceLogicTick;
            clientTicksSinceLogicTick = 0;
        }
    }
    
    engine->debug->PrintString("these are my objects:\n");
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->debug->PrintString("   UID: %i\n", objects[i]->GetUID() );
    }

    if( !waitingForUpdate )
    {
        engine->ClientSideUpdateAll();
    }
    waitingForUpdate = true;

    engine->PredictAll( tickRate );
    engine->RenderAll();
}