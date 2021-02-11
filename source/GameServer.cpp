//GameServer.cpp

#include "GameServer.h"

GameServer::GameServer()
{
    engine = new GameEngine;
    if( engine->net->GetType() == NET_TYPE_LOCAL_BUFFER )
    {
        engine->net->SetAddress( 2 );
        engine->net->Connect( 1 );
    }
    if( engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_UDP || engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_TCP )
    {
        #ifdef linux
            //engine->net->Connect( inet_addr( "127.0.0.1" ) );
            engine->net->InitServer();
        #endif
    }

    Object* tmp = new Enemy( engine );
    engine->AddObject( tmp );
    tmp = new Enemy( engine );
    engine->AddObject( tmp );
    tmp = new Player( engine );
    engine->AddObject( tmp );
}
GameServer::~GameServer()
{
    engine->debug->PrintString( "destroying gameserver...\n" );
    delete engine;
}
void GameServer::Run()
{
    engine->text->PrintString( "================ server ===============:\n" );

    engine->text->PrintString( "checking the net for packtes\n" );
    engine->net->Update();

    while( !engine->net->InboxEmpty() )
    {
        Packet* pkt = engine->net->GetFirstPacketFromInbox();
        if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
        {
            Object newStatus( engine );
            newStatus.objectStats = *( ObjectStats* )pkt->data;
            newStatus.SetEngine( engine );

            engine->debug->PrintString( "   received Packet: UID:%i Type:%i Pos:%f:%f mov:%f:%f from:%i rewrite NetAddr to:%i\n", newStatus.GetUID(), newStatus.GetType(), newStatus.GetPos().x, newStatus.GetPos().y,newStatus.GetMovement().x, newStatus.GetMovement().y , pkt->sender, newStatus.GetEngine()->net->GetAddress() );

            Object* foundObject = engine->GetObjectByUID( newStatus.GetUID() );
            if( foundObject != NULL )
            {
                foundObject->Render();
                foundObject->LoadStatus( &newStatus );
                engine->debug->PrintString( "found object and update...\n" );
                foundObject->Render();
            }
            else
            {
                //Object is not already in the list, so create one
                if( newStatus.GetType() == OBJECT_TYPE_OBJECT )
                {
                    engine->text->PrintString( "Adding new Object" );
                    Object* newObject = new Object( engine );
                    newObject->LoadStatus( &newStatus );
                    engine->AddObject( newObject );
                }
                if( newStatus.GetType() == OBJECT_TYPE_PLAYER )
                {
                    engine->text->PrintString( "Adding new Object" );
                    Object* newObject = new Player( engine );
                    newObject->LoadStatus( &newStatus );
                    engine->AddObject( newObject );
                }
                if( newStatus.GetType() == OBJECT_TYPE_ENEMY )
                {
                    engine->text->PrintString( "Adding new Object" );
                    Object* newObject = new Enemy( engine );
                    newObject->LoadStatus( &newStatus );
                    engine->AddObject( newObject );
                }
            }
        }
        pkt->~Packet();
    }

    
    /*engine->text->PrintString( "these are my objects:\n" );
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->debug->PrintString( "   UID: %i\n", objects[i]->GetUID() );
    }*/

    //Game Logic for all Objects
    engine->UpdateAll();

    //create and send GameLogic complete packet
    Packet* ack = new Packet;
    ack->type = NET_PACKET_TYPE_SEND_COMPLETE;
    engine->net->Send( ack );

    engine->debug->PrintString( "======================================:\n\n\n" );

}