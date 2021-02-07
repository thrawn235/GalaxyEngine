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

int main()
{
    cout<<"Galaxy Engine: Main Client"<<endl;

    bool serverActive = false;
    bool clientActive = true;

    GameClient* client = NULL;
    GameServer* server = NULL;

    if( serverActive )
    {
        cout<<"creatinig server..."<<endl;
        server = new GameServer();
    }
    if( clientActive )
    {
        cout<<"creatinig client..."<<endl;
        client = new GameClient();
    }

    
    long int rounds = 0;
    int subRounds = 0;
    bool exit = false;
    cout<<"entering main loop..."<<endl;
    while( !exit )
    {
        if( client != NULL )
        {
            client->Run();
        }

        if( subRounds >= 3 )
        {
            if( server != NULL )
            {
                server->Run();
            }
            subRounds = 0;
        }

       
        cout<<"wating for input:";
        char input;
        cin>>input;
        if( input == 'q' )
        {
            exit = true;
        }
        cout<<endl;
        rounds ++;
        subRounds ++;
        cout<<"end of round "<<rounds<<endl;
    }

    delete client;
    delete server;

    cout<<"good bye!"<<endl;
    return 0;
}