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

	engine->text->PrintString( "Player Menu:\n" );
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
	}

	SendStatus();
}
void Player::Render()
{
	engine->text->PrintString( "Render: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i (client)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, netStats->movement.x, netStats->movement.y, engine->net->GetAddress() );
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