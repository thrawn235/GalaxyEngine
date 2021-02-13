#include "Object.h"
#include "GameEngine.h"

Object::Object( GameEngine* engine )
{
    engine->debug->PrintString( "object constructor...\n" );
    if( baseNetStats != NULL )
    {
        delete baseNetStats;   
    }
    baseNetStats = new ObjectStats;
    netStats = (ObjectStats*)baseNetStats;
    netStats->size = sizeof( ObjectStats );

    this->engine              = engine;

    netStats->uid             = engine->GetHighestUIDAndInc();

    netStats->pos             = Vector2D( 0, 0 );
    netStats->movement        = Vector2D( 0, 0 );

    netStats->active          = true;
    netStats->clientActive    = true;
    netStats->predict         = true;
    netStats->visible         = true;

    netStats->type            = OBJECT_TYPE_OBJECT;
}
Object::~Object()
{
    delete baseNetStats;
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
    return netStats->uid;
}
void Object::SetUID( unsigned long uid )
{
    //
    netStats->uid = uid;
}
unsigned int Object::GetType()
{
    //
    return netStats->type;
}
void Object::SetType( unsigned int type )
{
    //
    netStats->type = type;
}
bool Object::GetVisible()
{
    //
    return netStats->visible;
}
bool Object::GetActive()
{
    //
    return netStats->active;
}
bool Object::GetPredict()
{
    //
    return netStats->predict;
}
bool Object::GetClientActive()
{
    //
    return netStats->active;
}
void Object::SetVisible( bool visible )
{
    //
    netStats->visible = visible;
}
void Object::SetActive( bool active )
{
    //
    netStats->active = active;
}
void Object::SetPredict( bool predict )
{
    //
    netStats->predict = predict;
}
void Object::SetClientActive( bool clientActive )
{
    //
    netStats->clientActive = clientActive;
}
Vector2D Object::GetPos()
{
    //
    return netStats->pos;
}
void Object::SetPos( Vector2D pos )
{
    //
    netStats->pos = pos;
}
Vector2D Object::GetMovement()
{
    //
    return netStats->movement;
}
void Object::SetMovement( Vector2D movement )
{
    //
    netStats->movement = movement;
}

void Object::SendStatus()
{ 
    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->dataLength = netStats->size;
    pkt->data       = netStats;
    pkt->type       = NET_PACKET_TYPE_OBJECT_UPDATE;

    engine->debug->PrintString( "  sending packet UID:%i Type:%i Pos:%f:%f \n", GetUID(), GetType(), GetPos().x, GetPos().y );

    engine->net->Send( pkt );
}
void Object::LoadStatus( void* data )
{
    //lets assume we know that data is of type Object
    NetStats* tmp = (NetStats*)data;
    engine->debug->PrintString( "received UID:%i Type:%i size:%i\n", tmp->uid, tmp->type, tmp->size );
    memcpy( &netStats, data, netStats->size );
}

void Object::Update()
{
    GameLogic();

    SendStatus();
}
void Object::GameLogic()
{
    //
    engine->text->PrintString( "Game Logic: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (server)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );
}
void Object::ClientSideUpdate()
{
    engine->text->PrintString( "ClientSide: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (client)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );

    //SendStatus();
}
void Object::Predict( float tickRate )
{
    engine->text->PrintString( "Predict: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (server)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );
    engine->text->PrintString( "   tickRate: %f\n", tickRate );
    netStats->pos = netStats->pos + netStats->movement * tickRate;
}
void Object::Render()
{
    //
    engine->text->PrintString( "Render: Object UID:%i; Type:%i(Object); Pos:%f:%f NetAddr:%i (client)\n", netStats->uid, netStats->type, netStats->pos.x, netStats->pos.y, engine->net->GetAddress() );
}