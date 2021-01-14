#include "Object.h"

Object::Object(GameEngine* engine)
{
	this->engine = engine;
}
void Object::Talk()
{
	cout<<"I say: hack the planet!"<<endl;
	cout<<"And i have "<<engine->GetAllObjects().size()<<" Friends"<<endl;
}