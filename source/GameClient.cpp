//Client.cpp

#include "GameClient.h"

GameClient::GameClient()
{
    engine = new GameEngine;

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


    //count ticks (for prediction step)
    clientTicksSinceLogicTick++;


    //Get Input Data---------------------------------------------
    engine->input->Update();
    //-----------------------------------------------------------


    //Try to connect to server (if not connected already)--------
    if( !engine->net->GetIsConnected() )
    {
        ConnectToServer();
    }
    //-----------------------------------------------------------


    //Network----------------------------------------------------
    engine->net->Update();
    engine->debug->PrintString( "Ive got %i Packets\n", engine->net->GetNumPacketsInInbox() );

    while( !engine->net->InboxEmpty() )
    {
        engine->text->PrintString( "received Packet: " );

        Packet* pkt = engine->net->GetFirstPacketFromInbox();
        NetStats* newStatus = (NetStats*)pkt->data;
        if( pkt->type == NET_PACKET_TYPE_OBJECT_UPDATE )
        {
            UpdateObjectsFromNet( pkt );
        }
        else if( pkt->type == NET_PACKET_TYPE_SEND_COMPLETE )
        {
            engine->debug->PrintString( "   Packet: Gameround done!\n");
            waitingForUpdate = false;


            tickRate = 1.0 / clientTicksSinceLogicTick;
            engine->debug->PrintString( "       tickrate:%f clientTicks:%i!\n", tickRate, clientTicksSinceLogicTick );
            clientTicksSinceLogicTick = 0;
        }

        //clear memory for the packet
        pkt->~Packet();
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