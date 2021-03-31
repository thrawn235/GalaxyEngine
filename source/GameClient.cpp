//Client.cpp

#include "GameClient.h"

GameClient::GameClient()
{
    #ifdef TARGET_DOS
        engine->SetGraphicsType( GRAPHICS_TYPE_VESA );
    #endif
    #ifdef TARGET_LINUX
        engine->SetGraphicsType( GRAPHICS_TYPE_SDL );
    #endif
    #ifdef TARGET_WIN
        engine->SetGraphicsType( GRAPHICS_TYPE_SDL );
    #endif
        
    engine->SetHighestUID( 100000 );
    
    //network variables
    waitingForUpdate            = false;

    //prediction variables
    tickRate                    = 1;
    clientTicksSinceLogicTick   = 0;

    //main communication
    exit = false;

    //initial game objects
    MainMenu* mainMenu = new MainMenu( engine );
    engine->AddObject( mainMenu );

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
    //debug:
    engine->debug->PrintString( "===================== client ==================\n" );

    engine->debug->PrintString( "these are my objects:\n" );
    vector<Object*> objects = engine->GetAllObjects();
    engine->debug->PrintString( "ive got %i objects\n", objects.size() );
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->debug->PrintString( "   UID: %i\n", objects[i]->GetUID() );
    }

    //count ticks (for prediction step)
    clientTicksSinceLogicTick++;


    //Get Input Data---------------------------------------------
    engine->input->Update();
    //-----------------------------------------------------------

    engine->graphics->Update();
    engine->graphics->Clear();

    //Try to connect to server (if not connected already)--------
    engine->debug->PrintString( "trying to connect... " );
    if( !engine->net->GetIsConnected() )
    {
        engine->debug->PrintString( "not connected yet, connecting...\n " );
        ConnectToServer();
    }
    else
    {
        engine->debug->PrintString( "already connected\n " );
    }
    //-----------------------------------------------------------


    //Network----------------------------------------------------
    engine->net->Update();
    engine->debug->PrintString( "Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

    while( !engine->net->InboxEmpty() )
    {
        engine->text->PrintString( "received Packet: " );

        Packet* pkt = engine->net->GetFirstPacketFromInbox();
        //NetStats* newStatus = (NetStats*)pkt->data;
        if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
        {
            engine->debug->PrintString( "GameObject update!\n");
            UpdateObjectFromNet( pkt );
        }
        else if( pkt->type == NET_PACKET_TYPE_SEND_COMPLETE )
        {
            engine->debug->PrintString( "Gameround done!\n");
            waitingForUpdate = false;


            tickRate = 1.0 / clientTicksSinceLogicTick;
            engine->debug->PrintString( "       tickrate:%f clientTicks:%i!\n", tickRate, clientTicksSinceLogicTick );
            clientTicksSinceLogicTick = 0;
        }

        //clear memory for the packet
        //pkt->~Packet();
        delete pkt;
    }
    //-----------------------------------------------------------


    //Update Game Logic------------------------------------------
    //only update if the server has send a Ack Packet
    if( !waitingForUpdate )
    {
        engine->ClientSideUpdateAll();
        waitingForUpdate = true;
    }
    //-----------------------------------------------------------


    //Update all Objects even if no connected to server----------
    engine->UpdateServerIndependend();
    //-----------------------------------------------------------


    //interpolate movement---------------------------------------
    engine->PredictAll( tickRate );
    //-----------------------------------------------------------


    //Render-----------------------------------------------------
    engine->RenderAll();
    //-----------------------------------------------------------

    //Graphics Flip----------------------------------------------
    engine->graphics->Flip();
    //-----------------------------------------------------------

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
        engine->debug->PrintString( "connecting to server (join request)...\n" );
        //the ifndef is needed because the local buffer doesnt know inet_addr
        #ifndef TARGET_DOS
            engine->net->Connect( inet_addr( "127.0.0.1" ) );
        #endif   
    }
}