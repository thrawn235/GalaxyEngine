//Client.cpp

#include "GameClient.h"

GameClient::GameClient()
{
    engine->debug->PrintString("GameClient:  loading NGR Assets - File\n ");
    #ifdef TARGET_DOS
        engine->data->LoadArchiveFile( "./assets.ngr" );
        engine->SetGraphicsType( GRAPHICS_TYPE_VESA );
    #endif
    #ifdef TARGET_LINUX
        engine->data->LoadArchiveFile( "./assets/linux/assets.ngr" );
        engine->SetGraphicsType( GRAPHICS_TYPE_SDL );
        //engine->SetDebugType( TEXT_TYPE_DUMMY );
    #endif
    #ifdef TARGET_WIN
        engine->data->LoadArchiveFile( "./assets/win/assets.ngr" );
        engine->SetGraphicsType( GRAPHICS_TYPE_SDL );
    #endif
        
    engine->objects->SetHighestUID( 100000 );
    
    //network variables
    waitingForUpdate            = false;

    //prediction variables
    tickRate                    = 1;
    clientTicksSinceLogicTick   = 0;

    //main communication
    exit = false;

    //initial game objects
    engine->objects->LoadMap( DATA_E1M1 );
    engine->debug->PrintString( "GameClient: create MainMenu...\n" );
    MainMenu* mainMenu = new MainMenu( engine );
    engine->debug->PrintString( "GameClient: add MainMenu...\n" );
    engine->objects->AddObject( mainMenu );
    

    engine->debug->PrintString( "\n\n" );
}
GameClient::~GameClient()
{
    engine->debug->PrintString( "destroying gameclient...\n" );
    delete engine;
}

bool GameClient::GetExit()
{
    return exit;
}

void GameClient::Run()
{
    engine->time->FrameStart();

    //debug:
    engine->debug->PrintString( "===================== client ==================\n" );

    engine->debug->PrintString( "client: these are my objects:\n" );
    vector<Object*> objects = engine->objects->GetAllObjects();
    engine->debug->PrintString( "client: ive got %i objects\n", objects.size() );
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->debug->PrintString( "client:   UID: %i\n", objects[i]->GetUID() );
    }

    //count ticks (for prediction step)
    clientTicksSinceLogicTick++;


    //Get Input Data---------------------------------------------
    engine->input->Update();
    //-----------------------------------------------------------

    engine->graphics->PreFrame();

    //Try to connect to server (if not connected already)--------
    engine->debug->PrintString( "client: trying to connect... " );
    if( !engine->net->GetIsConnected() )
    {
        engine->debug->PrintString( "client: not connected yet, connecting...\n " );
        ConnectToServer();
    }
    else
    {
        engine->debug->PrintString( "client: already connected\n " );
    }
    //-----------------------------------------------------------


    //Network----------------------------------------------------
    int networkTimer = engine->time->AddTimeStamp();
    engine->net->Update();
    engine->debug->PrintString( "client: Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

    while( !engine->net->InboxEmpty() )
    {
        engine->debug->PrintString( "client: received Packet: " );

        Packet* pkt = engine->net->GetFirstPacketFromInbox();
        //NetStats* newStatus = (NetStats*)pkt->data;
        if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
        {
            engine->debug->PrintString( "client: GameObject update!\n");
            UpdateObjectFromNet( pkt );
        }
        else if( pkt->type == NET_PACKET_TYPE_SEND_COMPLETE )
        {
            engine->debug->PrintString( "client: Gameround done!\n");
            waitingForUpdate = false;


            tickRate = 1.0 / clientTicksSinceLogicTick;
            //engine->text->PrintString( "       tickrate:%f clientTicks:%i!\n", tickRate, clientTicksSinceLogicTick );
            clientTicksSinceLogicTick = 0;
        }

        //clear memory for the packet
        //pkt->~Packet();
        delete pkt;
    }
    networkUpdateTime = engine->time->TicksToMilliSeconds( engine->time->GetTimeSinceStamp( networkTimer ) );
    //-----------------------------------------------------------

    //engine->text->PrintString( "       tickrate:%f clientTicks:%i!\n", tickRate, clientTicksSinceLogicTick );

    //Update Objects------------------------------------------------------
    int updateTimer = engine->time->AddTimeStamp();
    objects = engine->objects->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !waitingForUpdate && objects[i]->GetClientActive() )
        {
            objects[i]->ClientSideUpdate();
        }
        objects[i]->UpdateServerIndependend();
        if( objects[i]->GetPredict() )
        {
            objects[i]->Predict( tickRate );
        }
    }
    updateTime = engine->time->TicksToMilliSeconds( engine->time->GetTimeSinceStamp( updateTimer ) );
    //--------------------------------------------------------------------



    //render objects------------------------------------------------------
    int renderTimer = engine->time->AddTimeStamp();
    for( unsigned char currentDrawOrder = 0; currentDrawOrder < 64; currentDrawOrder++ )
    {
        if( objects.size() == 0 )
        {
            //list empty
            break;
        }
        for( unsigned int i = 0; i < objects.size(); i++ )
        {
            if( objects[i]->GetVisible() && objects[i]->GetDrawOrder() == currentDrawOrder )
            {
                objects[i]->Render();
                objects.erase( objects.begin() + i );   //remove from list. needs only be drawn once!
            }
        }
    }
    renderTime = engine->time->TicksToMilliSeconds( engine->time->GetTimeSinceStamp( renderTimer ) );
    //--------------------------------------------------------------------


    //did we hear from the server that he is done? -----------------------
    if( !waitingForUpdate )
    {
        //if yes, we have done our updates and we will wait until we hear from the server again:
        waitingForUpdate = true;
    }
    //--------------------------------------------------------------------


    //Graphics Flip----------------------------------------------
    engine->graphics->PostFrame();
    //-----------------------------------------------------------
    
    engine->time->FrameEnd();

    engine->debug->PrintString( "===============================================\n\n\n" );
}


void GameClient::ConnectToServer()
{
    if( engine->net->GetType() == NET_TYPE_LOCAL_BUFFER )
    {
        engine->net->Connect( 0 );  //0 is the default server address for local buffer
    }
    if( engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_UDP || engine->net->GetType() == NET_TYPE_LINUX_SOCKETS_TCP || engine->net->GetType() == NET_TYPE_WIN_SOCKETS_TCP )
    {
        engine->debug->PrintString( "client: connecting to server (join request)...\n" );
        //the ifndef is needed because the local buffer doesnt know inet_addr
        #ifndef TARGET_DOS
            engine->net->Connect( inet_addr( "127.0.0.1" ) );
        #endif   
    }
}

//peformance meassurements--------------------------
float GameClient::GetNetworkUpdateTime()
{
    return networkUpdateTime;
}
float GameClient::GetUpdateTime()
{
    return updateTime;
}
float GameClient::GetRenderTime()
{
    return renderTime;
}
//---------------------------------------------------