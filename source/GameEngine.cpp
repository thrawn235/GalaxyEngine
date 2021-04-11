#include "GameEngine.h"

#include "TextEngineDummy.h"
#include "InputEngineDummy.h"
#include "NetEngineDummy.h"
#include "GraphicsEngineDummy.h"
#include "TimeEngineDummy.h"
#include "FileEngineDummy.h"
#include "DataEngineDummy.h"
#ifdef TARGET_WIN
    #include "NetEngineWinSocketsUDP.h"
    #include "NetEngineLocal.h"
    #include "TextEngineIOStream.h"
    #include "InputEngineSDL.h"
    #include "GraphicsEngineSDL.h"
    #include "TextEngineSTDIO.h"
    #include "TimeEngineSDL.h"
    #include "FileEngineSTDIO.h"
    #include "DataEngineNGR.h"
#endif
#ifdef TARGET_LINUX
    #include "NetEngineLinuxSocketsUDP.h"
    #include "NetEngineLinuxSocketsTCP.h"
    #include "NetEngineLocal.h"
    #include "TextEngineIOStream.h"
    #include "TextEngineSTDIO.h"
    #include "InputEngineSDL.h"
    #include "GraphicsEngineSDL.h"
    #include "TimeEngineSDL.h"
    #include "FileEngineSTDIO.h"
    #include "DataEngineNGR.h"
#endif
#ifdef TARGET_DOS
    #include "NetEngineLocal.h"
    #include "TextEngineSTDIO.h"
    #include "TextEngineIOStream.h"
    #include "InputEngineDOS.h"
    #include "GraphicsEngineVESA.h"
    #include "TimeEngineDOS.h"
    #include "FileEngineSTDIO.h"
    #include "DataEngineNGR.h"
#endif

//global list of all Game Engines. Its prmarily used for ungraceful program termination
vector<GameEngine*> engines;


GameEngine::GameEngine()
{
    //order is important!
    #ifdef TARGET_LINUX
        text        = new TextEngineSTDIO;
        debug       = new TextEngineSTDIO;
        input       = new InputEngineSDL( this );
        //net       = new NetEngineLinuxSocketsUDP( this );
        graphics    = new GraphicsEngineDummy( this );
        time        = new TimeEngineSDL( this );
        file        = new FileEngineSTDIO( this );
        data        = new DataEngineNGR( this );
    #endif
    #ifdef TARGET_WIN
        text        = new TextEngineIOStream;
        debug       = new TextEngineIOStream;
        input       = new InputEngineSDL( this );
        //net       = new NetEngineWinSocketsUDP( this );
        graphics    = new GraphicsEngineDummy( this );
        time        = new TimeEngineSDL( this );
        file        = new FileEngineSTDIO( this );
        data        = new DataEngineNGR( this );
    #endif
    #ifdef TARGET_DOS
        text        = new TextEngineIOStream;
        debug       = new TextEngineDummy;
        //net       = new NetEngineLocal( this );
        input       = new InputEngineDOS( this );
        graphics    = new GraphicsEngineDummy( this );
        time        = new TimeEngineDOS( this );
        file        = new FileEngineSTDIO( this );
        data        = new DataEngineNGR( this );
    #endif

    net = new NetEngineLocal( this );

    engines.push_back( this );

    highestUID = 1;
}
GameEngine::~GameEngine()
{
    debug->PrintString( "Purge all objects... \n" );
    PurgeAllObjects( true );
    debug->PrintString( "Clear deleted objects... \n" );
    ClearDeletedObjects();
    debug->PrintString( "erase this engine from engines list... \n" );
    for( unsigned int i = 0; i < engines.size(); i++ )
    {
        if( engines[i] == this )
        {
            engines.erase( engines.begin() + i );
            break;
        }
    }

    debug->PrintString( "delete graphics... \n" );
    delete graphics;
    debug->PrintString( "delete input... \n" );
    delete input;
    debug->PrintString( "delete net... \n" );
    delete net;
    debug->PrintString( "delete text... \n" );
    delete text;
    debug->PrintString( "delete debug... \n" );
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
    availableModes.push_back( NET_TYPE_DUMMY );
    
    #ifdef TARGET_LINUX
        availableModes.push_back( NET_TYPE_LINUX_SOCKETS_UDP );
        availableModes.push_back( NET_TYPE_LINUX_SOCKETS_TCP );
    #endif
    #ifdef TARGET_WIN
        availableModes.push_back( NET_TYPE_WIN_SOCKETS_UDP );
    #endif
    #ifdef TARGET_DOS
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
    if( netType == NET_TYPE_DUMMY )
    {
        net = new NetEngineDummy( this );
    }
    #ifdef TARGET_LINUX
        else if( netType == NET_TYPE_LINUX_SOCKETS_UDP )
        {
            net = new NetEngineLinuxSocketsUDP( this );
        }
        else if( netType == NET_TYPE_LINUX_SOCKETS_TCP )
        {
            net = new NetEngineLinuxSocketsTCP( this );   
        }
    #endif
    #ifdef TARGET_WIN
        else if( netType == NET_TYPE_WIN_SOCKETS_UDP )
        {
            net = new NetEngineWinSocketsUDP( this );
        }
    #endif
}
vector<int> GameEngine::GetAvailableTextTypes()
{
    vector<int> availableModes;

    availableModes.push_back( TEXT_TYPE_DUMMY );
    availableModes.push_back( TEXT_TYPE_IOSTREAM );
    availableModes.push_back( TEXT_TYPE_STDIO );

    return availableModes;
}
void GameEngine::SetTextType( int textType )
{
    delete text;

    if( textType == TEXT_TYPE_DUMMY )
    {
        text = new TextEngineDummy;
    }
    else if( textType == TEXT_TYPE_STDIO )
    {
        text = new TextEngineSTDIO;
    }
    else if( textType == TEXT_TYPE_IOSTREAM )
    {
        text = new TextEngineIOStream;
    }
}
void GameEngine::SetDebugType( int textType )
{
    delete debug;

    if( textType == TEXT_TYPE_DUMMY )
    {
        debug = new TextEngineDummy;
    }
    else if( textType == TEXT_TYPE_STDIO )
    {
        debug = new TextEngineSTDIO;
    }
    else if( textType == TEXT_TYPE_IOSTREAM )
    {
        debug = new TextEngineIOStream;
    }
}
vector<int> GameEngine::GetAvailableInputTypes()
{
    vector<int> availableModes;

    availableModes.push_back( INPUT_TYPE_DUMMY );

    #ifdef TARGET_DOS
        availableModes.push_back( INPUT_TYPE_DOS );
    #endif
    #ifdef TARGET_LINUX
        availableModes.push_back( INPUT_TYPE_SDL );
    #endif
    #ifdef TARGET_WIN
        availableModes.push_back( INPUT_TYPE_SDL );
    #endif
    

    return availableModes;
}
void GameEngine::SetInputType( int inputType )
{
    delete input;

    if( inputType == INPUT_TYPE_DUMMY )
    {
        input = new InputEngineDummy( this );
    }
    #if defined TARGET_WIN || TARGET_LINUX
        else if( inputType == INPUT_TYPE_SDL )
        {
            input = new InputEngineSDL( this );
        }
    #endif
    #ifdef TARGET_DOS
        if( inputType == INPUT_TYPE_DOS )
        {
            input = new InputEngineDOS( this );
        }
    #endif
}
vector<int> GameEngine::GetAvailableGraphicsTypes()
{
    vector<int> availableModes;

    availableModes.push_back( GRAPHICS_TYPE_DUMMY );
    availableModes.push_back( GRAPHICS_TYPE_SDL );

    return availableModes;
}
void GameEngine::SetGraphicsType( int graphicsType )
{
    delete graphics;

    if( graphicsType == GRAPHICS_TYPE_DUMMY )
    {
        graphics = new GraphicsEngineDummy( this );
    }
    #if defined TARGET_WIN || TARGET_LINUX
        else if( graphicsType == GRAPHICS_TYPE_SDL )
        {
            graphics = new GraphicsEngineSDL( this );
        }
    #endif
    #ifdef TARGET_DOS
        else if( graphicsType == GRAPHICS_TYPE_VESA )
        {
            graphics = new GraphicsEngineVESA( this );
        }
    #endif
}
vector<int> GameEngine::GetAvailableTimeTypes()
{
    vector<int> availableModes;

    availableModes.push_back( TIME_TYPE_DUMMY );
    #if defined TARGET_WIN || TARGET_LINUX
        availableModes.push_back( TIME_TYPE_SDL );
    #endif
    
    #ifdef TARGET_DOS
        availableModes.push_back( TIME_TYPE_DOS );
    #endif

    return availableModes;
}
void GameEngine::SetTimeType( int timeType )
{
    delete time;

    if( timeType == GRAPHICS_TYPE_DUMMY )
    {
        time = new TimeEngineDummy( this );
    }
    #if defined TARGET_WIN || TARGET_LINUX
        else if( timeType == TIME_TYPE_SDL )
        {
            time = new TimeEngineSDL( this );
        }
    #endif
    #ifdef TARGET_DOS
        else if( timeType == TIME_TYPE_DOS )
        {
            time = new TimeEngineDOS( this );
        }
    #endif
}
vector<int> GameEngine::GetAvailableFileTypes()
{
    vector<int> availableModes;

    availableModes.push_back( FILE_TYPE_DUMMY );
    availableModes.push_back( FILE_TYPE_STDIO );

    return availableModes;
}
void GameEngine::SetFileType( int fileType )
{
    delete file;

    if( fileType == FILE_TYPE_DUMMY )
    {
        file = new FileEngineDummy( this );
    }
    else if( fileType == FILE_TYPE_STDIO )
    {
        file = new FileEngineSTDIO( this );
    }
}
vector<int> GameEngine::GetAvailableDataTypes()
{
    vector<int> availableModes;

    availableModes.push_back( DATA_TYPE_DUMMY );
    availableModes.push_back( DATA_TYPE_NGR );

    return availableModes;
}
void GameEngine::SetDataType( int dataType )
{
    delete data;

    if( dataType == DATA_TYPE_DUMMY )
    {
        data = new DataEngineDummy( this );
    }
    else if( dataType == DATA_TYPE_NGR )
    {
        data = new DataEngineNGR( this );
    }
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
    debug->PrintString( "Get objects, i have %i\n", objects.size() );
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
    debug->PrintString( "Add object, i have %i\n", objects.size() );
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
            //text->PrintString("render...\n");
            objects[i]->Render();
        }
    }
}