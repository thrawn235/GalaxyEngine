#include "Object.h"
#include "GameEngine.h"

Object::Object( GameEngine* engine )
{
    this->engine    = engine;

    uid             = engine->GetHighestUIDAndInc();

    pos             = Vector2D( 0, 0 );
    movement        = Vector2D( 0, 0 );

    active          = true;
    clientActive    = true;
    predict         = true;
    visible         = true;

    type            = OBJECT_TYPE_OBJECT;

    test            = 0;
}
void Object::SetEngine( GameEngine* engine )
{
    this->engine = engine;
}
GameEngine* Object::GetEngine()
{
    return engine;
}
unsigned long int Object::GetUID()
{
    return uid;
}
void Object::SetUID( unsigned long uid )
{
    this->uid = uid;
}
unsigned int Object::GetType()
{
    return type;
}
void Object::SetType( unsigned int type )
{
    this->type = type;
}
bool Object::GetVisible()
{
    return visible;
}
bool Object::GetActive()
{
    return active;
}
bool Object::GetPredict()
{
    return predict;
}
bool Object::GetClientActive()
{
    return active;
}
void Object::SetVisible( bool visible )
{
    this->visible = visible;
}
void Object::SetActive( bool active )
{
    this->active = active;
}
void Object::SetPredict( bool predict )
{
    this->predict = predict;
}
void Object::SetClientActive( bool clientActive )
{
    this->clientActive = clientActive;
}
Vector2D Object::GetPos()
{
    return pos;
}
void Object::SetPos( Vector2D pos )
{
    this->pos = pos;
}
Vector2D Object::GetMovement()
{
    return movement;
}
void Object::SetMovement( Vector2D movement )
{
    this->movement = movement;
}

void Object::SendStatus()
{
    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->sequence   = 0;                      //set to 0 for debugging for now!
    pkt->dataLength = sizeof( this );
    pkt->data       = this;
    pkt->type       = NET_PACKET_TYPE_OBJECT_UPDATE;

    Object* pktDebug = (Object*)pkt->data;

    engine->debug->PrintString( "  sending packet UID:%i Type:%i Pos:%f:%f from:%i NetAddr:%i\n", pktDebug->GetUID(), pktDebug->GetType(), pktDebug->GetPos().x, pktDebug->GetPos().y, pkt->sender, engine->net->GetAddress() );

    engine->net->Send( pkt );
}
void Object::LoadStatus( void* data )
{
    //lets assume we know that data is of type Object
    memcpy( this, data, sizeof( Object ) );
}

void Object::Update()
{
    GameLogic();

    SendStatus();
}
void Object::GameLogic()
{
    engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (server)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );
}
void Object::ClientSideUpdate()
{
    engine->text->PrintString( "ClientSide: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (client)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );

    //SendStatus();
}
void Object::Predict( float tickRate )
{
    engine->text->PrintString( "Predict: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (server)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );
    pos = pos + movement * tickRate;
}
void Object::Render()
{
    engine->text->PrintString( "Render: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (client)\n", uid, type, pos.x, pos.y, engine->net->GetAddress() );
}