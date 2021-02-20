#include "GameEngine.h"

//global list of all Game Engines. Its prmarily used for ungraceful program termination
vector<GameEngine*> engines;


GameEngine::GameEngine()
{
    #ifdef linux
        text = new TextEngineIOStream;
        debug = new TextEngineIOStream;
        //net = new NetEngineLinuxSocketsUDP( this );
    #endif
    #ifdef win
        text = new TextEngineIOStream;
        debug = new TextEngineIOStream;
        //net = new NetEngineWinSocketsUDP( this );
    #endif
    #ifdef dos
        text = new TextEngineSTDIO;
        debug = new TextEngineSTDIO;
        //net = new NetEngineLocal( this );
    #endif

    net = new NetEngineLocal( this );

    engines.push_back( this );

    highestUID = 1;
}
GameEngine::~GameEngine()
{
    delete net;
    delete text;
    delete debug;
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
vector<int> GameEngine::GetAvailableNetTypes()
{
    vector<int> availableModes;

    availableModes.push_back( NET_TYPE_LOCAL_BUFFER );
    
    #ifdef linux
        availableModes.push_back( NET_TYPE_LINUX_SOCKETS_UDP );
        availableModes.push_back( NET_TYPE_LINUX_SOCKETS_TCP );
    #endif
    #ifdef win
        availableModes.push_back( NET_TYPE_WIN_SOCKETS_UDP );
    #endif
    #ifdef dos
    #endif

    return availableModes;
}
void GameEngine::SetNetType( int netType )
{
    if( net != NULL )
    {
        delete net;
    }

    if( netType == NET_TYPE_LOCAL_BUFFER )
    {
        net = new NetEngineLocal( this );
    }
    #ifdef linux
        else if( netType == NET_TYPE_LINUX_SOCKETS_UDP )
        {
            net = new NetEngineLinuxSocketsUDP( this );
        }
        else if( netType == NET_TYPE_LINUX_SOCKETS_TCP )
        {
            net = new NetEngineLinuxSocketsTCP( this );   
        }
    #endif
    #ifdef win
        else if( netType == NET_TYPE_WIN_SOCKETS_UDP )
        {
            net = new NetEngineWinSocketsUDP( this );
        }
    #endif
}

void GameEngine::Quit()
{
    for( unsigned int i = 0; i < engines.size(); i++ )
    {
        delete engines[i];
        i++;
    }
    exit( EXIT_FAILURE );
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

void GameEngine::UpdateServerIndependend()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetClientActive() )
        {
            objects[i]->UpdateServerIndependend();
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