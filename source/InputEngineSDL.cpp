//InputEngineSDL.h

#include "InputEngineSDL.h"
#include "GameEngine.h"



InputEngineSDL::InputEngineSDL( GameEngine* engine ) : InputEngine( engine )
{
    this->engine = engine;

    Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if( subsystem_init == 0 )
    {
        SDL_Init( 0 );
    }
    if( !(subsystem_init & SDL_INIT_EVENTS) )
    {
        SDL_InitSubSystem( SDL_INIT_EVENTS );
    }


    Input* input 		= new Input;
    input->uid 			= SDL_SCANCODE_0;
    input->description	= "0";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_1;
    input->description	= "1";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_2;
    input->description	= "2";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_3;
    input->description	= "3";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_4;
    input->description	= "4";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_5;
    input->description	= "5";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_6;
    input->description	= "6";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_7;
    input->description	= "7";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_8;
    input->description	= "8";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_9;
    input->description	= "9";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_A;
    input->description	= "A";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_B;
    input->description	= "B";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_C;
    input->description	= "C";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_D;
    input->description	= "D";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_E;
    input->description	= "E";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F;
    input->description	= "F";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_G;
    input->description	= "G";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_H;
    input->description	= "H";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_I;
    input->description	= "I";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_J;
    input->description	= "J";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_K;
    input->description	= "K";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_L;
    input->description	= "L";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_M;
    input->description	= "M";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_N;
    input->description	= "N";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_O;
    input->description	= "O";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_P;
    input->description	= "P";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_Q;
    input->description	= "Q";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_R;
    input->description	= "R";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_S;
    input->description	= "S";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_T;
    input->description	= "T";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_U;
    input->description	= "U";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_V;
    input->description	= "V";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_W;
    input->description	= "W";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_X;
    input->description	= "X";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_Y;
    input->description	= "Y";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_Z;
    input->description	= "Z";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F1;
    input->description	= "F1";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F2;
    input->description	= "F2";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F3;
    input->description	= "F3";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F4;
    input->description	= "F4";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F5;
    input->description	= "F5";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F6;
    input->description	= "F16";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F7;
    input->description	= "F7";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F8;
    input->description	= "F8";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F9;
    input->description	= "F9";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F10;
    input->description	= "F10";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F11;
    input->description	= "F11";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_F12;
    input->description	= "F12";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_UP;
    input->description	= "Up";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_DOWN;
    input->description	= "Down";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_LEFT;
    input->description	= "Left";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_RIGHT;
    input->description	= "Right";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_BACKSPACE;
    input->description	= "Backspace";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_CAPSLOCK;
    input->description	= "Capslock";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_ESCAPE;
    input->description	= "Escape";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_LALT;
    input->description	= "Left Alt";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_LCTRL;
    input->description	= "Left Ctrl";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_LSHIFT;
    input->description	= "left Shift";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_PAGEUP;
    input->description	= "Page Up";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_PAGEDOWN;
    input->description	= "Page Down";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_RALT;
    input->description	= "right Alt";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_RCTRL;
    input->description	= "right Ctrl";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_RETURN;
    input->description	= "RETURN";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_RSHIFT;
    input->description	= "right Shift";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_SPACE;
    input->description	= "Spacebar";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );

    input 				= new Input;
    input->uid 			= SDL_SCANCODE_TAB;
    input->description	= "Tab";
    input->active 		= false;
    input->value 		= 0.0;
    inputs.push_back( input );
}
InputEngineSDL::~InputEngineSDL()
{
    SDL_QuitSubSystem( SDL_INIT_EVENTS );

    // Clean up
    Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if( subsystem_init == 0 )
    {
        SDL_Quit();
    } 
}


void InputEngineSDL::AddAction( Action action )
{
	actions.push_back( &action );
}
void InputEngineSDL::DeleteAction( Action* action )
{
	for( unsigned int i = 0; i < actions.size(); i++ )
	{
		if( actions[i] == action )
		{
			actions.erase( actions.begin() + i );
		}
	}
}
void InputEngineSDL::DeleteAction( unsigned int uid )
{
	for( unsigned int i = 0; i < actions.size(); i++ )
	{
		if( actions[i]->uid == uid )
		{
			actions.erase( actions.begin() + i );
		}
	}
}
Action* InputEngineSDL::GetAction( unsigned int uid )
{
	for( unsigned int i = 0; i < actions.size(); i++ )
	{
		if( actions[i]->uid == uid )
		{
			return actions[i];
		}
	}
	return NULL;
}
vector<Action*> InputEngineSDL::GetAllActions()
{
	return actions;
}
bool InputEngineSDL::ActionActive( unsigned int uid )
{
	for( unsigned int i = 0; i < actions.size(); i++ )
	{
		if( actions[i]->uid == uid )
		{
			return actions[i]->active;
		}
	}
	return false;
}
bool InputEngineSDL::ActionActive( Action* action )
{
	for( unsigned int i = 0; i < actions.size(); i++ )
	{
		if( actions[i] == action )
		{
			return actions[i]->active;
		}
	}
	return false;
}


vector<Input*> InputEngineSDL::GetAllInputs()
{
	return inputs;
}
bool InputEngineSDL::KeyDown( unsigned char scancode )
{
	for( unsigned int i = 0; i < inputs.size(); i++ )
	{
		if( inputs[i]->uid == scancode )
		{
			if( inputs[i]->active == true )
			{
				return true;
			}
		}
	}
	return false;	
}
bool InputEngineSDL::AnyKeyDown()
{
	for( unsigned int i = 0; i < inputs.size(); i++ )
	{
		if( inputs[i]->active == true )
		{
			return true;
		}
	}
	return false;
}


void InputEngineSDL::Update()
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) != 0 )
	{
		if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			for( unsigned int i = 0; i < inputs.size(); i++ )
			{
				if( (unsigned int)event.key.keysym.sym == inputs[i]->uid )
				{
					if( event.type == SDL_KEYDOWN )
					{
						inputs[i]->active = true; 
					}
					else if( event.type == SDL_KEYUP )
					{
						inputs[i]->active = false;
					}
				}
			}
		}
	}
}