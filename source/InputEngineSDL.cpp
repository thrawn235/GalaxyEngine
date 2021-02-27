//InputEngineSDL.h

#include "InputEngineSDL.h"



InputEngineSDL::InputEngineSDL( GameEngine* engine ) : InputEngine( engine )
{
    this->engine = engine;
}
InputEngineSDL::~InputEngineSDL()
{

}


unsigned int InputEngineSDL::AddAction( unsigned int input )
{

}
void InputEngineSDL::DeleteAction( Action* action )
{

}
void InputEngineSDL::DeleteAction( unsigned int uid )
{

}
Action InputEngineSDL::GetAction( unsigned int uid )
{

}
vector<Action> InputEngineSDL::GetAllActions()
{

}
void InputEngineSDL::SetAction( unsigned int uid, Action* action )
{

}
bool InputEngineSDL::ActionActive( unsigned int uid )
{

}
bool InputEngineSDL::ActionActive( Action* action )
{

}


vector<Input> InputEngineSDL::GetAllInputs()
{

}
bool InputEngineSDL::KeyDown( unsigned char scancode )
{

}
bool InputEngineSDL::AnyKeyDown()
{

}


void InputEngineSDL::Update()
{

}