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

//========= global variables =========
//client needs to know server because GameMenu needs to be able to create it. one of the rare cases where a global is justified imho
GameClient* client = NULL;
//server is NOT active at start bc main menu will create it
GameServer* server = NULL;
//====================================

int main( int argc, char *argv[] )
{
    cout<<"Galaxy Engine: Main Client"<<endl<<endl;

    client = new GameClient();
    
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
    if( server != NULL )
    {
        delete server;
    }

    cout<<"good bye!"<<endl;
    return 0;
}