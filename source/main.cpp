//====================================
// main.cpp
// the Main Client contains a server and a client part
// the server part can be disabled in network play
//====================================

//========== stdlib includes =========
#include <iostream>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GameEngine.h"
#include "GameServer.h"
#include "GameClient.h"
//====================================

int main( int argc, char *argv[] )
{
    cout<<"Galaxy Engine: Main Client"<<endl<<endl;

    GameClient* client = NULL;
    GameServer* server = NULL;

    //server is NOT active at start bc main menu will create it

    //Client needs to know *server for network settings etc
    client = new GameClient( &server );

    
    //----------------- Main Loop --------------------
    long int rounds = 0;
    cout<<"entering main loop..."<<endl;
    while( !client->GetExit() )
    {
        if( client != NULL )
        {
            client->Run();
        }

        if( server != NULL )
        {
            server->Run();
        }

        rounds ++;
        cout<<"end of round "<<rounds<<endl;
    }
    //-------------------------------------------------

    delete client;

    cout<<"good bye!"<<endl;
    return 0;
}