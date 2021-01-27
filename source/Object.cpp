#include "Object.h"

Object::Object( GameEngine* engine )
{
    this->engine = engine;
}
void Object::Talk()
{
    engine->text->PrintString( "I say: hack the planet!" );
    engine->text->EndLine();
    engine->text->PrintString( "And I have " );
    engine->text->PrintInt( engine->GetAllObjects().size() );
    engine->text->PrintString( " friends!" );
    engine->text->EndLine();
}