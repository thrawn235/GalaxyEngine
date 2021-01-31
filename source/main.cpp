#include <iostream>
#include <stdio.h>
using namespace std;

//Galaxy Includes:
#include "GameEngine.h"
#include "GameClient.h"
#include "GameServer.h"
#include "NetEngineLocal.h"

int main()
{
    GameEngine* engine = new GameEngine();

    GameClient* client = new GameClient();
    GameServer* server = new GameServer();

    
    long int rounds = 0;
    int subRounds = 0;
    bool exit = false;
    while( !exit )
    {
        client->Run();

        if( subRounds >= 3 )
        {
            server->Run();
            subRounds = 0;
        }

        engine->debug->PrintString( "End of Round %i\n", rounds );
        engine->debug->EndLine();
        if( engine->debug->InputChar() == 'q' )
        {
            exit = true;
        }
        rounds ++;
        subRounds ++;
    }

    engine->debug->EndLine();
    engine->debug->PrintString( "Good Bye!" );
    engine->debug->EndLine();

    return 0;
}