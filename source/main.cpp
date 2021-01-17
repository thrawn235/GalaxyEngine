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
	NetBuffer localNetBuffer;

	GameEngine* engine = new GameEngine( &localNetBuffer );

	GameClient* client = new GameClient( &localNetBuffer );
	GameServer* server = new GameServer( &localNetBuffer );

	
	long int rounds = 0;
	int subRounds = 0;
	bool exit = false;
	while( !exit )
	{
		client->Run();
		engine->net->SendLayer1( rounds );
		engine->text->PrintString( "netsize: " );
		engine->text->PrintInt( engine->net->GetLayer1Unread() );
		engine->text->EndLine();

		if( subRounds >= 3 )
		{
			server->Run();
			subRounds = 0;
			unsigned char rec = engine->net->ReceiveLayer1();
			engine->text->PrintString( "received from net: " );
			engine->text->PrintInt( rec );
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