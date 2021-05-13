//DerivedObjects.cpp

#include "DerivedObjects.h"
#include "GameServer.h"
#include "GameClient.h"
#include "GameEngine.h"


Player::Player( GameEngine* engine ) : Object( engine )
{
	baseNetStats = (NetStats*)realloc( baseNetStats, sizeof( PlayerStats ) );
   
    netStats = (PlayerStats*)baseNetStats;
    netStats->size = sizeof( PlayerStats );

	netStats->type = OBJECT_TYPE_PLAYER;

	netStats->up = netStats->down = netStats->left = netStats->right = netStats->fire = false;

	netStats->drawOrder = 1;

	//engine->text->PrintString( "Player Constructor: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
}
void Player::GameLogic()
{
	netStats->movement.Zero();

	if( netStats->up )
	{
		netStats->movement.y = -3;
	}
	if( netStats->down )
	{
		netStats->movement.y = +3;
	}
	if( netStats->left )
	{
		netStats->movement.x = -3;
	}
	if( netStats->right )
	{
		netStats->movement.x = +3;
	}
	

	netStats->pos = netStats->pos + netStats->movement;


	engine->debug->PrintString( "Game Logic: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i (server)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
}
void Player::ClientSideUpdate()
{
	netStats->up = netStats->down = netStats->left = netStats->right = netStats->fire = false;

	if( engine->input->KeyDown( KEY_LEFT ) )
	{
		netStats->left = true;
		//engine->text->PrintString( "game logic - right key down\n" );
	}
	if( engine->input->KeyDown( KEY_RIGHT ) )
	{
		netStats->right = true;
		//engine->text->PrintString( "game logic - right key down\n" );
	}
	if( engine->input->KeyDown( KEY_UP ) )
	{
		netStats->up = true;
		//engine->text->PrintString( "game logic - right key down\n" );
	}
	if( engine->input->KeyDown( KEY_DOWN ) )
	{
		netStats->down = true;
		//engine->text->PrintString( "game logic - right key down\n" );
	}
	if( engine->input->KeyDown( SPACE ) )
	{
		netStats->fire = true;
	}

	SendStatus();
}
void Player::Render()
{
	//engine->text->PrintString( "Render: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i (client)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
	engine->graphics->DrawRect( netStats->pos, 16, 16, COLOR_RED );
	if( netStats->fire )
	{
		//engine->text->PrintString( (char*)engine->data->GetData( DATA_STRING ) );
		engine->graphics->DrawSprite( DATA_TREEHOUSE, Vector2D( 50, 50 ) );
		engine->graphics->DrawString( DATA_SONIC_FONT, "test\nhello world!", Vector2D( 5, 20 ) );
		engine->graphics->DrawString( DATA_SONIC_FONT, "another test that is a bit more useless bla\nand of course something behind a linebreak", 10, Vector2D( 100,100 ) );
	}

	engine->graphics->SetCamPos( netStats->pos );
}





Tile::Tile( GameEngine* engine ) : Object( engine )
{
	baseNetStats = (NetStats*)realloc( baseNetStats, sizeof( TileStats ) );
   
    netStats = (TileStats*)baseNetStats;
    netStats->size = sizeof( TileStats );

	netStats->type = OBJECT_TYPE_TILE;

	netStats->tileSetID = 0;
	netStats->tileIndex = 0;

	engine->text->PrintString( "Tile Constructor: Object UID:%i; Type:%i(Tile); Pos:%f:%f Mov:%f:%f NetAddr:%i\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
}
void Tile::SetTileSet( unsigned int tileSetID, unsigned char tileIndex )
{
	netStats->tileSetID = tileSetID;
	netStats->tileIndex = tileIndex;
	engine->text->PrintString( "Tile: SetTileSet ID:%i Index:%i\n", netStats->tileSetID, netStats->tileIndex );
	sprite = engine->graphics->GetSpriteInCollection( netStats->tileSetID, netStats->tileIndex );
}
unsigned int Tile::GetTileSetID()
{
	return netStats->tileSetID;
}
unsigned char Tile::GetTileIndex()
{
	return netStats->tileIndex;
}
void Tile::GameLogic()
{

}
void Tile::ClientSideUpdate()
{
	
}
void Tile::Render()
{
	engine->graphics->DrawSprite( sprite, netStats->pos );
	//engine->graphics->DrawRect( netStats->pos, 32, 32, COLOR_RED );
	//engine->text->PrintString( "tileDrawPos:%f/%f\n", netStats->pos.x, netStats->pos.y );
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
	//engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (server)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );
}
void Enemy::Render()
{
	//engine->text->PrintString( "Render: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (client)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );
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
			engine->debug->PrintString( "delete...\n" );
			engine->objects->DeleteAllObjectsExcept( this, true );

			engine->debug->PrintString( "GameClient: create Performance Overlay...\n" );
		    PerformanceOverlay* performanceOverlay = new PerformanceOverlay( engine );
		    engine->debug->PrintString( "GameClient: add PerformanceOverlay...\n" );
		    engine->objects->AddObject( performanceOverlay );
		    engine->debug->PrintString( "GameClient: load map...\n" );
		    engine->objects->LoadMap( DATA_E1M1 );
		    engine->debug->PrintString( "GameClient: map loaded!\n" );

			//create server
			if( server != NULL )
			{
				engine->debug->PrintString( "disconnect...\n" );
				engine->net->Disconnect();
				engine->debug->PrintString( "disconnected...\n" );
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
			engine->debug->PrintString( "server creation done!\n" );

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

			engine->objects->PurgeAllObjectsExcept( this, true );

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
		if( engine->input->KeyDown( ESC ) )
		{
			hidden = false;
		}
	}
}
void MainMenu::Render()
{
	
}






PerformanceOverlay::PerformanceOverlay( GameEngine* engine ) : Object( engine )
{
	baseNetStats = (NetStats*)realloc( baseNetStats, sizeof( PerformanceOverlayStats ) );

    netStats = (PerformanceOverlayStats*)baseNetStats;
    netStats->size = sizeof( PerformanceOverlayStats );

	netStats->type = OBJECT_TYPE_PERFORMANCE_OVERLAY;

	netStats->persistent = true;
	netStats->drawOrder = 15; //draw on top of almost everything
}
PerformanceOverlay::~PerformanceOverlay()
{

}
void PerformanceOverlay::GameLogic()
{
	//Performance Overlay is not supposed to even be replicated to the server
	//
}
void PerformanceOverlay::ClientSideUpdate()
{
	
}
void PerformanceOverlay::UpdateServerIndependend()
{

}
void PerformanceOverlay::Render()
{
	if( client != NULL && server != NULL )
	{
		GameClient* pClient = (GameClient*)client;
		engine->graphics->DrawString( DATA_SONIC_FONT, engine->text->SPrintString( "Objects %i/%i\nMemory\nFPS %f(%i)/%f(%i)\nrender time:%f\nnetwork time:%f\nupdate time:%f", client->GetEngine()->objects->GetAllObjects().size(), server->GetEngine()->objects->GetAllObjects().size(), client->GetEngine()->time->GetFPS(), client->GetEngine()->time->GetLastTime(), server->GetEngine()->time->GetFPS(), server->GetEngine()->time->GetLastTime(), pClient->GetRenderTime(), client->GetNetworkUpdateTime(), client->GetUpdateTime() ), Vector2D( 0, 0 ) );
	}
}