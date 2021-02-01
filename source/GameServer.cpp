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

    Object* tmp = new Enemy( engine );
    engine->AddObject( tmp );
    tmp = new Enemy( engine );
    engine->AddObject( tmp );
    tmp = new Player( engine );
    engine->AddObject( tmp );
}
void GameServer::Run()
{
    engine->text->PrintString( "this is the server:\n" );

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
    }

    
    engine->text->PrintString( "these are my objects:\n" );
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->text->PrintString( "   UID: %i\n", objects[i]->GetUID() );
    }

    //Game Logic for all Objects
    engine->UpdateAll();

    //create and send GameLogic complete packet
    Packet* ack = new Packet;
    ack->type = NET_PACKET_TYPE_SEND_COMPLETE;
    engine->net->Send( ack );
}