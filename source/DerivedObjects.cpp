//DerivedObjects.cpp

#include "DerivedObjects.h"
#include "GameEngine.h"

Player::Player( GameEngine* engine ) : Object( engine )
{
	type = OBJECT_TYPE_PLAYER;
}
void Player::GameLogic()
{
	engine->text->PrintString("Game Logic: Object UID:%i; Type:%i(Player); Pos:%f:%f (server)\n", uid, type, pos.x, pos.y );
}
void Player::ClientSideUpdate()
{
	engine->text->PrintString( "Player Menu:\n" );
	engine->text->PrintString( "   enter new xPos: " );
	pos.x = engine->text->InputFloat();
	engine->text->PrintString( "   enter new yPos: " );
	pos.y = engine->text->InputFloat();
}
void Player::Render()
{
	engine->text->PrintString("Render: Object UID:%i; Type:%i(Player); Pos:%f:%f (client)\n", uid, type, pos.x, pos.y );
}





Enemy::Enemy( GameEngine* engine ) : Object( engine )
{
	type = OBJECT_TYPE_ENEMY;
}
void Enemy::GameLogic()
{
	engine->text->PrintString("Game Logic: Object UID:%i; Type:%i(Enemy); Pos:%f:%f (server)\n", uid, type, pos.x, pos.y );
}
void Enemy::Render()
{
	engine->text->PrintString("Render: Object UID:%i; Type:%i(Enemy); Pos:%f:%f (client)\n", uid, type, pos.x, pos.y );
}