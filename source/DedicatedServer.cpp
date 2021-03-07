//====================================
// DedicatedServer.cpp
// the dedicated server is a stand alone program that implements the server part
// of the Galaxy engine only.
// it just has a text console interface
//====================================

//========== stdlib includes =========
#include <iostream>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GameEngine.h"
#include "GameServer.h"
//====================================

//======= forward declarations =======
//====================================

//============= globals ==============
GameServer* server = NULL;
//====================================

int main( int argc, char *argv[] )
{
    cout<<"Galaxy Engine: DedicatedServer"<<endl;
    cout<<"creatinig server..."<<endl;
    server = new GameServer();

    
    long int rounds = 0;
    bool exit = false;
    cout<<"entering main loop..."<<endl;
    while( !exit )
    {
        server->Run();


        cout<<"wating for input:";
        char input;
        cin>>input;
        if( input == 'q' )
        {
            exit = true;
        }
        cout<<endl;
        rounds ++;
        cout<<"end of round "<<rounds<<endl;
    }
    cout<<"good bye!"<<endl;
    return 0;
}