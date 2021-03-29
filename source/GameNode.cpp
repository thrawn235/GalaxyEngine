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
void GameNode::UpdateObjectFromNet( Packet* pkt )
{
    NetStats* newStatus = (NetStats*)pkt->data;
             
    Object* foundObject = engine->GetObjectByUID( newStatus->uid );
    if( foundObject != NULL )
    {
        engine->debug->PrintString( "   found object(%i) and update...\n", foundObject->GetUID() );
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
            engine->AddObject( newObject );
        }
        if( newStatus->type == OBJECT_TYPE_PLAYER )
        {
            engine->text->PrintString( "   Adding new Player\n" );
            Object* newObject = new Player( engine );
            newObject->LoadStatus( newStatus );
            engine->AddObject( newObject );
        }
        if( newStatus->type == OBJECT_TYPE_ENEMY )
        {
            engine->text->PrintString( "   Adding new Enemy\n" );
            Object* newObject = new Enemy( engine );
            newObject->LoadStatus( newStatus );
            engine->AddObject( newObject );
        }
    }
}