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
			engine->text->PrintInt( subRounds );
			engine->text->EndLine();
		}

		engine->text->PrintString( "End of Round " );
		engine->text->PrintInt( rounds );
		engine->text->EndLine();
		engine->text->EndLine();
		char input = getchar();
		if( input == 'q' )
		{
			exit = true;
		}
		rounds ++;
		subRounds ++;
	}

	engine->text->EndLine();
	engine->text->PrintString( "Good Bye!" );
	engine->text->EndLine();

	return 0;
}