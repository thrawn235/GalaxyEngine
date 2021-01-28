#include "Object.h"

Object::Object( GameEngine* engine )
{
    this->engine = engine;

    uid = engine->GetHighestUIDAndInc();

    active = true;
    clientActive = true;
    predict = true;
    visible = true;

    type = OBJECT_TYPE_OBJECT;
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
    return uid;
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

}
void Object::LoadStatus( void* data )
{

}

void Object::Update()
{

}
void Object::ClientSideUpdate()
{

}
void Object::Predict()
{

}
void Object::Render()
{

}