//DerivedObjects.cpp

#include "DerivedObjects.h"
#include "GameEngine.h"

Player::Player( GameEngine* engine ) : Object( engine )
{
	type = OBJECT_TYPE_PLAYER;

	up = down = left = right = fire = false;
}
void Player::GameLogic()
{
	movement.Zero();

	if( up )
	{
		movement.y = +1;
	}
	else if( down )
	{
		movement.y = -1;
	}
	else if( left )
	{
		movement.x = -1;
	}
	else if( right )
	{
		movement.x = + 1;
	}

	pos = pos + movement;

	engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Player); Pos:%f:%f NetAddr:%i (server)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );
}
void Player::ClientSideUpdate()
{
	up = down = left = right = fire = false;

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
			up = true;
		}
		else if( inputMove == 'd' )
		{
			down = true;
		}
		else if( inputMove == 'l' )
		{
			left = true;
		}
		else if( inputMove == 'r' )
		{
			right = true;
		}
	}
	else if( input == 'f' )
	{
		engine->text->PrintString( "      enter target uid:   = u\n" );
		target = engine->text->InputInt();
		fire = true;
	}

	SendStatus();
}
void Player::Render()
{
	engine->text->PrintString( "Client Side: Object UID:%i; Type:%i(Player); Pos:%f:%f NetAddr:%i (client)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );
}
void Player::LoadStatus( void* data )
{
	memcpy( this, data, sizeof( Player ) );
}
void Player::SendStatus()
{
    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->sequence   = 0;                      //set to 0 for debugging for now!
    pkt->dataLength = sizeof( Player );
    pkt->data       = this;

    Object* pktDebug = (Object*)pkt->data;

    engine->debug->PrintString( "  sending packet UID:%i Type:%i Pos:%f:%f from:%i NetAddr:%i\n", pktDebug->GetUID(), pktDebug->GetType(), pktDebug->GetPos().x, pktDebug->GetPos().y, pkt->sender, engine->net->GetAddress() );

    engine->net->Send( pkt );
}





Enemy::Enemy( GameEngine* engine ) : Object( engine )
{
	type = OBJECT_TYPE_ENEMY;
}
void Enemy::GameLogic()
{
	engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (server)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );
}
void Enemy::Render()
{
	engine->text->PrintString( "Render: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (client)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );
}
void Enemy::LoadStatus( void* data )
{
	memcpy( this, data, sizeof( Enemy ) );
}
void Enemy::SendStatus()
{
    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->sequence   = 0;                      //set to 0 for debugging for now!
    pkt->dataLength = sizeof( Enemy );
    pkt->data       = this;

    Object* pktDebug = (Object*)pkt->data;

    engine->debug->PrintString( "  sending packet UID:%i Type:%i Pos:%f:%f from:%i NetAddr:%i\n", pktDebug->GetUID(), pktDebug->GetType(), pktDebug->GetPos().x, pktDebug->GetPos().y, pkt->sender, engine->net->GetAddress() );

    engine->net->Send( pkt );
}