//DerivedObjects.cpp

#include "DerivedObjects.h"
#include "GameEngine.h"

Player::Player( GameEngine* engine ) : Object( engine )
{
	objectStats.type = OBJECT_TYPE_PLAYER;

	playerStats.up = playerStats.down = playerStats.left = playerStats.right = playerStats.fire = false;
}
void Player::GameLogic()
{
	objectStats.movement.Zero();

	if( playerStats.up )
	{
		objectStats.movement.y = +1;
	}
	else if( playerStats.down )
	{
		objectStats.movement.y = -1;
	}
	else if( playerStats.left )
	{
		objectStats.movement.x = -1;
	}
	else if( playerStats.right )
	{
		objectStats.movement.x = + 1;
	}

	objectStats.pos = objectStats.pos + objectStats.movement;

	engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i (server)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, objectStats.movement.x, objectStats.movement.y, engine->net->GetAddress() );
}
void Player::ClientSideUpdate()
{
	playerStats.up = playerStats.down = playerStats.left = playerStats.right = playerStats.fire = false;

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
			playerStats.up = true;
		}
		else if( inputMove == 'd' )
		{
			playerStats.down = true;
		}
		else if( inputMove == 'l' )
		{
			playerStats.left = true;
		}
		else if( inputMove == 'r' )
		{
			playerStats.right = true;
		}
	}
	else if( input == 'f' )
	{
		engine->text->PrintString( "      enter target uid:   = u\n" );
		playerStats.target = engine->text->InputInt();
		playerStats.fire = true;
	}

	SendStatus();
}
void Player::Render()
{
	engine->text->PrintString( "Render: Object UID:%i; Type:%i(Player); Pos:%f:%f Mov:%f:%f NetAddr:%i (client)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, objectStats.movement.x, objectStats.movement.y, engine->net->GetAddress() );
}
void Player::SendStatus()
{
	int sendSize = sizeof( ObjectStats ) + sizeof( PlayerStats );

    if( sendBuffer == NULL )
    {
        sendBuffer = (char*)malloc( sendSize );
    }

    memcpy( sendBuffer, &objectStats, sizeof( ObjectStats ) );
    memcpy( sendBuffer + sizeof( ObjectStats ), &playerStats, sizeof( PlayerStats ) );

    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->dataLength = sendSize;
    pkt->data       = sendBuffer;
    pkt->type       = NET_PACKET_TYPE_OBJECT_UPDATE;

    Object* pktDebug = (Object*)pkt->data;

    engine->debug->PrintString( "  sending packet UID:%i Type:%i Pos:%f:%f from:%i NetAddr:%i\n", pktDebug->GetUID(), pktDebug->GetType(), pktDebug->GetPos().x, pktDebug->GetPos().y, pkt->sender, engine->net->GetAddress() );

    engine->net->Send( pkt );
}
void Player::LoadStatus( void* data )
{
    //lets assume we know that data is of type Object
    memcpy( &objectStats, (char*)data, sizeof( ObjectStats ) );
    memcpy( &playerStats, (char*)data + sizeof( ObjectStats ), sizeof( PlayerStats ) );
}





Enemy::Enemy( GameEngine* engine ) : Object( engine )
{
	objectStats.type = OBJECT_TYPE_ENEMY;
}
void Enemy::GameLogic()
{
	engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (server)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, engine->net->GetAddress() );
}
void Enemy::Render()
{
	engine->text->PrintString( "Render: Object UID:%i; Type:%i(Enemy); Pos:%f:%f NetAddr:%i (client)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, engine->net->GetAddress() );
}
void Enemy::SendStatus()
{
	int sendSize = sizeof( ObjectStats ) + sizeof( PlayerStats );

    if( sendBuffer == NULL )
    {
        sendBuffer = (char*)malloc( sendSize );
    }

    memcpy( sendBuffer, &objectStats, sizeof( ObjectStats ) );
    memcpy( sendBuffer + sizeof( ObjectStats ), &enemyStats, sizeof( EnemyStats) );

    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->dataLength = sendSize;
    pkt->data       = sendBuffer;
    pkt->type       = NET_PACKET_TYPE_OBJECT_UPDATE;

    Object* pktDebug = (Object*)pkt->data;

    engine->debug->PrintString( "  sending packet UID:%i Type:%i Pos:%f:%f from:%i NetAddr:%i\n", pktDebug->GetUID(), pktDebug->GetType(), pktDebug->GetPos().x, pktDebug->GetPos().y, pkt->sender, engine->net->GetAddress() );

    engine->net->Send( pkt );
}
void Enemy::LoadStatus( void* data )
{
    memcpy( &objectStats, data, sizeof( ObjectStats) );
    memcpy( &enemyStats, data + sizeof( EnemyStats ), sizeof( EnemyStats ) );
}