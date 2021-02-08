#include "Object.h"
#include "GameEngine.h"

Object::Object( GameEngine* engine )
{
    this->engine                = engine;

    objectStats.uid             = engine->GetHighestUIDAndInc();

    objectStats.pos             = Vector2D( 0, 0 );
    objectStats.movement        = Vector2D( 0, 0 );

    objectStats.active          = true;
    objectStats.clientActive    = true;
    objectStats.predict         = true;
    objectStats.visible         = true;

    objectStats.type            = OBJECT_TYPE_OBJECT;

    sendBuffer                  = NULL;
}
void Object::SetEngine( GameEngine* engine )
{
    //
    this->engine = engine;
}
GameEngine* Object::GetEngine()
{
    //
    return engine;
}
unsigned long int Object::GetUID()
{
    //
    return objectStats.uid;
}
void Object::SetUID( unsigned long uid )
{
    //
    objectStats.uid = uid;
}
unsigned int Object::GetType()
{
    //
    return objectStats.type;
}
void Object::SetType( unsigned int type )
{
    //
    objectStats.type = type;
}
bool Object::GetVisible()
{
    //
    return objectStats.visible;
}
bool Object::GetActive()
{
    //
    return objectStats.active;
}
bool Object::GetPredict()
{
    //
    return objectStats.predict;
}
bool Object::GetClientActive()
{
    //
    return objectStats.active;
}
void Object::SetVisible( bool visible )
{
    //
    objectStats.visible = visible;
}
void Object::SetActive( bool active )
{
    //
    objectStats.active = active;
}
void Object::SetPredict( bool predict )
{
    //
    objectStats.predict = predict;
}
void Object::SetClientActive( bool clientActive )
{
    //
    objectStats.clientActive = clientActive;
}
Vector2D Object::GetPos()
{
    //
    return objectStats.pos;
}
void Object::SetPos( Vector2D pos )
{
    //
    objectStats.pos = pos;
}
Vector2D Object::GetMovement()
{
    //
    return objectStats.movement;
}
void Object::SetMovement( Vector2D movement )
{
    //
    objectStats.movement = movement;
}

void Object::SendStatus()
{ 
    if( sendBuffer == NULL )
    {
        sendBuffer = (char*)malloc( sizeof( ObjectStats ) );
    }

    memcpy( sendBuffer, &objectStats, sizeof( ObjectStats ) );

    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->dataLength = sizeof( ObjectStats );
    pkt->data       = sendBuffer;
    pkt->type       = NET_PACKET_TYPE_OBJECT_UPDATE;

    Object* pktDebug = (Object*)pkt->data;

    engine->debug->PrintString( "  sending packet UID:%i Type:%i Pos:%f:%f from:%i NetAddr:%i\n", pktDebug->GetUID(), pktDebug->GetType(), pktDebug->GetPos().x, pktDebug->GetPos().y, pkt->sender, engine->net->GetAddress() );

    engine->net->Send( pkt );
}
void Object::LoadStatus( void* data )
{
    //lets assume we know that data is of type Object
    memcpy( &objectStats, data, sizeof( ObjectStats ) );
}

void Object::Update()
{
    GameLogic();

    SendStatus();
}
void Object::GameLogic()
{
    //
    engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (server)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, engine->net->GetAddress() );
}
void Object::ClientSideUpdate()
{
    engine->text->PrintString( "ClientSide: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (client)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, engine->net->GetAddress() );

    //SendStatus();
}
void Object::Predict( float tickRate )
{
    engine->text->PrintString( "Predict: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (server)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, engine->net->GetAddress() );
    engine->text->PrintString( "   tickRate: %f\n", tickRate );
    objectStats.pos = objectStats.pos + objectStats.movement * tickRate;
}
void Object::Render()
{
    //
    engine->text->PrintString( "Render: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (client)\n", objectStats.uid, objectStats.type, objectStats.pos.x, objectStats.pos.y, engine->net->GetAddress() );
}