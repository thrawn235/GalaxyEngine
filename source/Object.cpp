#include "Object.h"
#include "GameEngine.h"

Object::Object( GameEngine* engine )
{ 
    this->engine              = engine;

    baseNetStats = new ObjectStats;
    netStats = (ObjectStats*)baseNetStats;
    netStats->size = sizeof( ObjectStats );

    netStats->uid             = engine->GetHighestUIDAndInc();

    netStats->pos             = Vector2D( 0, 0 );
    netStats->movement        = Vector2D( 0, 0 );

    netStats->active          = true;
    netStats->clientActive    = true;
    netStats->predict         = true;
    netStats->visible         = true;
    netStats->persistent      = false;

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
bool Object::GetPersistent()
{
    //
    return netStats->persistent;
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
void Object::SetPersistent( bool persistent )
{
    //
    netStats->persistent = persistent;
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

void Object::PrintStats()
{
    engine->debug->PrintString( "UID:%i Type:%i Pos:%f:%f stats-size:%i\n", GetUID(), GetType(), GetPos().x, GetPos().y, netStats->size );
}

void Object::SendStatus()
{ 
    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->dataLength = netStats->size;
    pkt->data       = netStats;
    pkt->type       = NET_PACKET_TYPE_OBJECT_UPDATE;

    engine->debug->PrintString( "sending Status: ");
    PrintStats();

    engine->net->Send( pkt );
}
void Object::LoadStatus( void* data )
{
    //lets assume we know that data is of type Object
    NetStats* tmp = (NetStats*)data;
    engine->debug->PrintString( "received UID:%i Type:%i size:%i\n", tmp->uid, tmp->type, tmp->size );
    memcpy( netStats, data, netStats->size );
}

void Object::Update()
{
    GameLogic();

    SendStatus();
}
void Object::GameLogic()
{
    //
    engine->text->PrintString( "Game Logic: " );
    PrintStats();
}
void Object::ClientSideUpdate()
{
    engine->text->PrintString( "Client Side: " );
    PrintStats();

    //SendStatus();
}
void Object::UpdateServerIndependend()
{
    
}
void Object::Predict( float tickRate )
{
    engine->text->PrintString( "Predict: " );
    PrintStats();
    engine->text->PrintString( "   tickRate: %f\n", tickRate );
    netStats->pos = netStats->pos + netStats->movement * tickRate;
}
void Object::Render()
{
    //
    engine->text->PrintString( "Render: " );
    PrintStats();
}