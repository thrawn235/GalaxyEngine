//DerivedObjects.cpp

#include "DerivedObjects.h"
#include "GameEngine.h"

Player::Player( GameEngine* engine ) : Object( engine )
{
	baseNetStats = (NetStats*)realloc( baseNetStats, sizeof( PlayerStats ) );
   
    netStats = (PlayerStats*)baseNetStats;
    netStats->size = sizeof( PlayerStats );

	netStats->type = OBJECT_TYPE_PLAYER;

	netStats->up = netStats->down = netStats->left = netStats->right = netStats->fire = false;

	engine->text->PrintString( "Player Constructor: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
}
void Player::GameLogic()
{
	netStats->movement.Zero();

	if( netStats->up )
	{
		netStats->movement.y = +1;
	}
	else if( netStats->down )
	{
		netStats->movement.y = -1;
	}
	else if( netStats->left )
	{
		netStats->movement.x = -1;
	}
	else if( netStats->right )
	{
		netStats->movement.x = + 1;
	}

	netStats->pos = netStats->pos + netStats->movement;

	engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i (server)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
}
void Player::ClientSideUpdate()
{
	netStats->up = netStats->down = netStats->left = netStats->right = netStats->fire = false;

	/*engine->text->PrintString( "Player Menu:\n" );
	engine->text->PrintString( "   Commands:\n" );
	engine->text->PrintString( "      move  = m\n" );
	engine->text->PrintString( "      fire  = f \n" );
	char input = engine->text->InputChar();
	if( input == 'm' )
	{
		engine->text->PrintString( "      up:   = u\n" );
		engine->text->PrintString( "      down  = d\n" );
		engine->text->PrintString( "      left  = l\n" );
		engine->text->PrintString( "      right = r\n" );
		char inputMove = engine->text->InputChar();
		if( inputMove == 'u')
		{
			netStats->up = true;
		}
		else if( inputMove == 'd' )
		{
			netStats->down = true;
		}
		else if( inputMove == 'l' )
		{
			netStats->left = true;
		}
		else if( inputMove == 'r' )
		{
			netStats->right = true;
		}
	}
	else if( input == 'f' )
	{
		engine->text->PrintString( "      enter target uid:   = u\n" );
		netStats->target = engine->text->InputInt();
		netStats->fire = true;
	}*/

	SendStatus();
}
void Player::Render()
{
	engine->text->PrintString( "Render: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i (client)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
	engine->graphics->DrawPixel( Vector2D( 5, 5 ), COLOR_RED );
}





Enemy::Enemy( GameEngine* engine ) : Object( engine )
{
	baseNetStats = (NetStats*)realloc( baseNetStats, sizeof( EnemyStats ) );

    netStats = (EnemyStats*)baseNetStats;
    netStats->size = sizeof( EnemyStats );

	netStats->type = OBJECT_TYPE_ENEMY;
}
void Enemy::GameLogic()
{
	engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (server)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );
}
void Enemy::Render()
{
	engine->text->PrintString( "Render: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (client)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );
}





MainMenu::MainMenu( GameEngine* engine ) : Object( engine )
{
	baseNetStats = (NetStats*)realloc( baseNetStats, sizeof( MainMenuStats ) );

    netStats = (MainMenuStats*)baseNetStats;
    netStats->size = sizeof( MainMenuStats );

	netStats->type = OBJECT_TYPE_MAIN_MENU;

	netStats->persistent = true;

	hidden = false;
	optionsMenu = false;
	netType = NET_TYPE_LOCAL_BUFFER;
}
MainMenu::~MainMenu()
{
	delete server;
}
void MainMenu::GameLogic()
{
	//Main menu is not supposed to even be replicated to the server
	//
}
void MainMenu::ClientSideUpdate()
{
	
}
void MainMenu::UpdateServerIndependend()
{
	if( !hidden )
	{
		engine->text->PrintString( "========== Galaxy Engine ==========\n" );
		engine->text->PrintString( "============ Main Menu ============\n" );
		engine->text->PrintString( "   0: Return to Game\n" );
		engine->text->PrintString( "   1: New Game\n" );
		engine->text->PrintString( "   2: Multiplayer\n" );
		engine->text->PrintString( "   3: Options\n" );
		engine->text->PrintString( "   4: Help\n" );
		engine->text->PrintString( "   5: Quit\n" );
		engine->text->PrintString( "===================================\n" );
		engine->text->PrintString( "  input> " );
		mainInput = engine->text->InputString();
		if( mainInput == "0" || mainInput == "New Game" )
		{
			//game already running ?

			//hide main menu
			hidden = true;
		}
		if( mainInput == "1" || mainInput == "New Game" )
		{
			//0. delete all client game objects (except the main menu)
			//1. create server
			//2. make sure it uses local buffer networking for single player
			//3. load all game objects
			//4. hide main menu
			engine->debug->PrintString( "purge...\n" );
			engine->PurgeAllObjectsExcept( this, true );

			//create server
			if( server != NULL )
			{
				engine->debug->PrintString( "disconnect...\n" );
				engine->net->Disconnect();
				delete server;
				engine->debug->PrintString( "server gone!\n" );
				server = NULL;
			}
			engine->debug->PrintString( "new server...\n" );
			server = new GameServer();

			//setting local buffer networking
			engine->debug->PrintString( "set client local buffer...\n" );
			server->GetEngine()->SetNetType( NET_TYPE_LOCAL_BUFFER );
			engine->debug->PrintString( "configure as server...\n" );
			server->GetEngine()->net->ConfigureAsServer();
			engine->debug->PrintString( "set server local buffer...\n" );
			engine->SetNetType( NET_TYPE_LOCAL_BUFFER );

			//hide main menu
			hidden = true;
		}
		else if( mainInput == "2" || mainInput == "Multiplayer" )
		{
			//0. delete all client game objects (except the main menu)
			//1. create server
			//2. make sure it uses the networking method specified by options
			//3. load all game objects
			//4. hide main menu

			engine->PurgeAllObjectsExcept( this, true );

			//create server
			if( server != NULL )
			{
				engine->net->Disconnect();
				delete server;
			}
			server = new GameServer();

			//setting networking
			server->GetEngine()->SetNetType( netType );
			server->GetEngine()->net->ConfigureAsServer();
			engine->SetNetType( netType );

			//hide main menu
			hidden = true;
		}
		else if( mainInput == "3" || mainInput == "Options" )
		{
			engine->text->PrintString( "entering options menu...\n" );
			optionsMenu = true;
			hidden = true;
		}
		else if( mainInput == "4" || mainInput == "Help" )
		{
			engine->text->PrintString( "help is not available right now! \n" );
		}
		else if( mainInput == "5" || mainInput == "Quit" )
		{
			engine->Quit();
		}
	}
	else if( optionsMenu )
	{
		engine->text->PrintString( "=========== Options Menu ==========\n" );
		engine->text->PrintString( "======= Choose Network Type: ======\n" );
		vector<int> netTypes = engine->GetAvailableNetTypes();
		for( unsigned int i = 0; i < netTypes.size(); i++ )
		{
			if( netTypes[i] == NET_TYPE_LOCAL_BUFFER )
			{
				engine->text->PrintString( "   %i: Local Buffer\n", i );
			}
			if( netTypes[i] == NET_TYPE_LINUX_SOCKETS_UDP )
			{
				engine->text->PrintString( "   %i: Linux UDP\n", i );
			}
			if( netTypes[i] == NET_TYPE_LINUX_SOCKETS_TCP )
			{
				engine->text->PrintString( "   %i: Linux TCP\n", i );
			}
			if( netTypes[i] == NET_TYPE_WIN_SOCKETS_UDP )
			{
				engine->text->PrintString( "   %i: Windows UDP\n", i );	
			}
			if( netTypes[i] == NET_TYPE_WIN_SOCKETS_TCP )
			{
				engine->text->PrintString( "   %i: Windows TCP\n", i );
			}
		}
		engine->text->PrintString( "===================================\n" );
		engine->text->PrintString( "  input> " );
		int optionsInput = engine->text->InputInt();
		if( optionsInput >= 0 && (unsigned int)optionsInput < netTypes.size() )
		{
			//GameServer* pServer = *server;
			netType = netTypes[optionsInput];
		}
		else
		{
			engine->text->PrintString( "invalid selection\n" );
		}
		optionsMenu = false;
		hidden = false;
	}
	else
	{
		/*engine->text->PrintString( "== Main Menu ==\n" );
		engine->text->PrintString( "  input m for menu > " );
		mainInput = engine->text->InputString();
		if( mainInput == "m" || mainInput == "Main Menu" )
		{
			hidden = false;
		}*/
		if( engine->input->AnyKeyDown() )
		{
			hidden = false;
		}
	}
}
void MainMenu::Render()
{
	
}