#include "GameEngine.h"

GameEngine::GameEngine()
{
    #ifdef linux
        net = new NetEngineLinuxSocketsUDP;
    #else
        net = new NetEngineLocal;
    #endif

    #ifdef dos
        text = new TextEngineSTDIO;
        debug = new TextEngineSTDIO;
    #else
        text = new TextEngineIOStream;
        debug = new TextEngineIOStream;
    #endif

    highestUID = 1;
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
Object* GameEngine::GetObjectByUID( unsigned long int uid )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetUID() == uid )
        {
            return objects[i];
        }
    }
    return NULL;
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
void GameEngine::PredictAll( float tickRate )
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