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
    PurgeAllObjects( true );
    ClearDeletedObjects();
    //engines.erase( this );

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
        availableModes.push_back( NET_TYPE_DOS_PACKET_DRIVER_UDP );
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
    }
    engines.clear();
    exit( EXIT_SUCCESS );
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


void GameEngine::DeleteObject( Object* object )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i] == object )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void GameEngine::DeleteObject( unsigned long uid )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetUID() == uid )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void GameEngine::DeleteObjects( vector<Object*> objects )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        for( unsigned int u = 0; u < this->objects.size(); u++ )
        {
            if( this->objects[i] == objects[u] )
            {
                deletedObjects.push_back( objects[i] );
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
void GameEngine::DeleteObjects( vector<unsigned long> uids )
{
    for( unsigned int i = 0; i < uids.size(); i++ )
    {
        for( unsigned int u = 0; u < objects.size(); u++ )
        {
            if( objects[u]->GetUID() == uids[i] )
            {
                deletedObjects.push_back( objects[i] );
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
void GameEngine::PurgeObject( Object* object )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i] == object )
        {
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void GameEngine::PurgeObject( unsigned long uid )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetUID() == uid )
        {
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void GameEngine::PurgeObjects( vector<Object*> objects )
{
    for( unsigned int u = 0; u < objects.size(); u++ )
    {
        for( unsigned int i = 0; i < this->objects.size(); i++ )
        {
            if( this->objects[i] == objects[u] )
            {
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
void GameEngine::PurgeObjects( vector<unsigned long> uids )
{
    for( unsigned int u = 0; u < uids.size(); u++ )
    {
        for( unsigned int i = 0; i < objects.size(); i++ )
        {
            if( objects[i]->GetUID() == uids[u] )
            {
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
void GameEngine::ClearDeletedObjects()     
{
    deletedObjects.clear();
}
void GameEngine::DeleteAllObjects( bool includePersistent )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void GameEngine::DeleteAllObjectsExcept( Object* object, bool includePersistent )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
        {
            if( objects[i] != object )
            {
                deletedObjects.push_back( objects[i] );
                objects.erase( objects.begin() + i );
                i--;
            }   
        }
    }
}
void GameEngine::PurgeAllObjects( bool includePersistent )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
        {
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void GameEngine::PurgeAllObjectsExcept( Object* object, bool includePersistent )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
        {
            if( objects[i] != object )
            {
                objects.erase( objects.begin() + i );
                i--;
            }   
        }
    }
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