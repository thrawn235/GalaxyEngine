#include "Object.h"

Object::Object( GameEngine* engine )
{
    this->engine    = engine;

    uid             = engine->GetHighestUIDAndInc();

    active          = true;
    clientActive    = true;
    predict         = true;
    visible         = true;

    type            = OBJECT_TYPE_OBJECT;

    test = 0;
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

void Object::SendStatus()
{
    Packet* pkt     = new Packet;
    pkt->sender     = engine->net->GetAddress();
    pkt->sequence   = 0;                      //set to 0 for debugging for now!
    pkt->dataLength = sizeof( this );
    pkt->data       = this;

    //Object* tmp = (Object*)pkt->data;
    /*engine->text->PrintString( "sending Packet: \n");
    engine->text->PrintString( " UID: ");
    engine->text->PrintInt( tmp->GetUID() );
    engine->text->EndLine();*/

    engine->net->Send( pkt );
}
void Object::LoadStatus( void* data )
{
    /*Object* tmp = (Object*)data;
    engine->text->PrintString(" receiving Packet: \n");
    engine->text->PrintString( "UID: ");
    engine->text->PrintInt( tmp->GetUID() );
    engine->text->EndLine();*/

    //lets assume we know that data is of type Object
    memcpy( this, data, sizeof( Object ) );

    /*Object* newStatus = ( Object* )data;
    this->uid           = newStatus->GetUID();
    this->type          = newStatus->GetType();
    this->visible       = newStatus->GetVisible();
    this->active        = newStatus->GetActive();
    this->predict       = newStatus->GetPredict();
    this->clientActive  = newStatus->GetActive();*/
}

void Object::Update()
{
    GameLogic();

    SendStatus();
}
void Object::GameLogic()
{
    test++;
    if( test >= uid )
    {
        visible = false;
    }

    engine->text->PrintString("this is Object: ");
    engine->text->PrintInt( GetUID() );
    engine->text->EndLine();
    engine->text->PrintString(" this is the GameLogic Method (Server): ");
    engine->text->PrintString(" Type: ");
    engine->text->PrintInt( GetType() );
    engine->text->EndLine();
    engine->text->PrintString(" visible: ");
    engine->text->PrintInt( GetVisible() );
    engine->text->EndLine();
    engine->text->PrintString(" active: ");
    engine->text->PrintInt( GetActive() );
    engine->text->EndLine();
    engine->text->PrintString(" predict: ");
    engine->text->PrintInt( GetPredict() );
    engine->text->EndLine();
    engine->text->PrintString(" clientActive: ");
    engine->text->PrintInt( GetClientActive() );
    engine->text->EndLine();
}
void Object::ClientSideUpdate()
{
    engine->text->PrintString("this is Object: ");
    engine->text->PrintInt( GetUID() );
    engine->text->EndLine();
    engine->text->PrintString(" this is the ClientSideUpdate Method (Client): ");
    engine->text->PrintString(" Type: ");
    engine->text->PrintInt( GetType() );
    engine->text->EndLine();
    engine->text->PrintString(" visible: ");
    engine->text->PrintInt( GetVisible() );
    engine->text->EndLine();
    engine->text->PrintString(" active: ");
    engine->text->PrintInt( GetActive() );
    engine->text->EndLine();
    engine->text->PrintString(" predict: ");
    engine->text->PrintInt( GetPredict() );
    engine->text->EndLine();
    engine->text->PrintString(" clientActive: ");
    engine->text->PrintInt( GetClientActive() );
    engine->text->EndLine();
}
void Object::Predict()
{

}
void Object::Render()
{

}