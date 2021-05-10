//GameNode.cpp

#include "GameNode.h"
#include "GameEngine.h"

GameNode::GameNode()
{
    engine = new GameEngine;
    engine->debug->PrintString( "gamenode constructor...\n" );
}
GameNode::~GameNode()
{
    engine->debug->PrintString( "destroying GameNode...\n" ); //cant print if its already deleted...
    delete engine; //cant delete it twice...
}
GameEngine* GameNode::GetEngine()
{
    return engine;
}
void GameNode::Run()
{
    
}
void GameNode::UpdateObjectFromNet( Packet* pkt )
{
    engine->debug->PrintString( " GameNode: UpdateObjectFromNet...\n" );
    NetStats* newStatus = (NetStats*)pkt->data;
             
    Object* foundObject = engine->objects->GetObjectByID( newStatus->uid );
    if( foundObject != NULL )
    {
        engine->debug->PrintString( "Gamenode: found object(%i) and update...\n", foundObject->GetUID() );
        foundObject->LoadStatus( newStatus );
    }
    else
    {
        //Object is not already in the list, so create one
        if( newStatus->type == OBJECT_TYPE_OBJECT )
        {
            engine->text->PrintString( "   Adding new Object\n" );
            Object* newObject = new Object( engine );
            newObject->LoadStatus( newStatus );
            engine->objects->AddObject( newObject );
        }
        if( newStatus->type == OBJECT_TYPE_PLAYER )
        {
            engine->text->PrintString( "   Adding new Player\n" );
            Object* newObject = new Player( engine );
            newObject->LoadStatus( newStatus );
            engine->objects->AddObject( newObject );
        }
        if( newStatus->type == OBJECT_TYPE_ENEMY )
        {
            engine->text->PrintString( "   Adding new Enemy\n" );
            Object* newObject = new Enemy( engine );
            newObject->LoadStatus( newStatus );
            engine->objects->AddObject( newObject );
        }
    }
    engine->debug->PrintString( " GameNode: UpdateObjectFromNet done!\n" );
}