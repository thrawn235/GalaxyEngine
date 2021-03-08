//InputEngineDummy.h

#include "InputEngineDummy.h"



InputEngineDummy::InputEngineDummy( GameEngine* engine ) : InputEngine( engine )
{
    
}
InputEngineDummy::~InputEngineDummy()
{

}


void InputEngineDummy::AddAction( Action action )
{
	
}
void InputEngineDummy::DeleteAction( Action* action )
{
	
}
void InputEngineDummy::DeleteAction( unsigned int uid )
{
	
}
Action* InputEngineDummy::GetAction( unsigned int uid )
{
	return NULL;
}
vector<Action*> InputEngineDummy::GetAllActions()
{
    vector<Action*> act;
	return act;
}
bool InputEngineDummy::ActionActive( unsigned int uid )
{
	return false;
}
bool InputEngineDummy::ActionActive( Action* action )
{
	return false;
}


vector<Input*> InputEngineDummy::GetAllInputs()
{
    vector<Input*> inp;
	return inp;
}
bool InputEngineDummy::KeyDown( unsigned char scancode )
{
	return false;	
}
bool InputEngineDummy::AnyKeyDown()
{
	return false;
}


void InputEngineDummy::Update()
{
    
}