//GameNode.cpp

#include "GameNode.h"
#include "GameEngine.h"

GameNode::GameNode()
{
    engine = new GameEngine;
}
GameNode::~GameNode()
{
    engine->debug->PrintString( "destroying GameNode...\n" );
    delete engine;
}
GameEngine* GameNode::GetEngine()
{
    return engine;
}
void GameNode::Run()
{
    
}
void GameNode::UpdateObjectsFromNet( Packet* pkt )
{
    engine->debug->PrintString( "packet type: update...\n" );
    NetStats* newStatus = (NetStats*)pkt->data;
             
    Object* foundObject = engine->GetObjectByUID( newStatus->uid );
    if( foundObject != NULL )
    {
        engine->debug->PrintString( "   found object and update...\n" );
        foundObject->LoadStatus( newStatus );
        foundObject->Render();
    }
    else
    {
        //Object is not already in the list, so create one
        if( newStatus->type == OBJECT_TYPE_OBJECT )
        {
            engine->text->PrintString( "   Adding new Object" );
            Object* newObject = new Object( engine );
            newObject->LoadStatus( newStatus );
            engine->AddObject( newObject );
        }
        if( newStatus->type == OBJECT_TYPE_PLAYER )
        {
            engine->text->PrintString( "   Adding new Player" );
            Object* newObject = new Player( engine );
            newObject->LoadStatus( newStatus );
            engine->AddObject( newObject );
        }
        if( newStatus->type == OBJECT_TYPE_ENEMY )
        {
            engine->text->PrintString( "   Adding new Enemy" );
            Object* newObject = new Enemy( engine );
            newObject->LoadStatus( newStatus );
            engine->AddObject( newObject );
        }
    }
}