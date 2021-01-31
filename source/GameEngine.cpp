#include "GameEngine.h"

GameEngine::GameEngine()
{
    net = new NetEngineLocal;
    #ifdef dos
        text = new TextEngineSTDIO;
        debug = new TextEngineSTDIO;
    #else
        text = new TextEngineIOStream;
        debug = new TextEngineIOStream;
    #endif

    highestUID = 1;

    tickRate                    = 1;
    clientTicksSinceLogicTick   = 0;
}
void GameEngine::SetHighestUID( unsigned long int UID )
{
    highestUID = UID;
}
unsigned long int GameEngine::GetHighestUID()
{
    return highestUID;
}
unsigned long int GameEngine::GetHighestUIDAndInc()
{
    highestUID++;
    return highestUID - 1;
}
vector<Object*> GameEngine::GetAllObjects()
{
    return objects;
}
void GameEngine::AddObject( Object* object )
{
    objects.push_back( object );
}
void GameEngine::UpdateAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetActive() )
        {
            objects[i]->Update();
        }
    }
}
void GameEngine::ClientSideUpdateAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetClientActive() )
        {
            objects[i]->ClientSideUpdate();
        }
    }
}
void GameEngine::PredictAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetPredict() )
        {
            objects[i]->Predict( tickRate );
        }
    }
}
void GameEngine::RenderAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetVisible() )
        {
            objects[i]->Render();
        }
    }
}
void GameEngine::UpdateGamestateFromNet()
{
    debug->PrintString( "received %i packets\n", net->GetNumPacketsInInbox()  );

    if( net->InboxEmpty() )
    {
        clientTicksSinceLogicTick++;
    }
    else
    {
        tickRate = 1 / clientTicksSinceLogicTick;
        clientTicksSinceLogicTick = 0;
    }

    while( !net->InboxEmpty() )
    {
        Packet* pkt = net->GetFirstPacketFromInbox();
        Object* newStatus = ( Object* )pkt->data;
        newStatus->SetEngine( this );

        debug->PrintString( "   received Packet: UID:%i Type:%i Pos:%f:%f from:%i rewrite NetAddr to:%i\n", newStatus->GetUID(), newStatus->GetType(), newStatus->GetPos().x, newStatus->GetPos().y, pkt->sender, newStatus->GetEngine()->net->GetAddress() );

        
        bool found = false;
        for( unsigned int i = 0; i < objects.size(); i++ )
        {
            if( objects[i]->GetUID() == newStatus->GetUID() )
            {
                objects[i]->LoadStatus( newStatus );
                found = true;
                break;
            }
        }

        //Object is not already in the list, so create one
        if( newStatus->GetType() == OBJECT_TYPE_OBJECT && !found )
        {
            //text->PrintString( "Adding new Object" );
            Object* newObject = new Object( this );
            newObject->LoadStatus( newStatus );
            AddObject( newObject );
        }
        if( newStatus->GetType() == OBJECT_TYPE_PLAYER && !found )
        {
            //text->PrintString( "Adding new Object" );
            Object* newObject = new Player( this );
            newObject->LoadStatus( newStatus );
            AddObject( newObject );
        }
        if( newStatus->GetType() == OBJECT_TYPE_ENEMY && !found )
        {
            //text->PrintString( "Adding new Object" );
            Object* newObject = new Enemy( this );
            newObject->LoadStatus( newStatus );
            AddObject( newObject );
        }
    }
}