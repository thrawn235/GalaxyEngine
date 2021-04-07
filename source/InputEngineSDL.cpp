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
	/*for( unsigned int i = 0; i < inputs.size(); i++ )
	{
		if( inputs[i]->uid == scancode )
		{
			if( inputs[i]->active == true )
			{
				return true;
			}
		}
	}
	return false;*/

    for( unsigned int i = 0; i < keys.size(); i++ )
    {
        if( keys[i] == scancode )
        {
            return true;
        }
    }
    return false;
}
bool InputEngineSDL::AnyKeyDown()
{
	/*for( unsigned int i = 0; i < inputs.size(); i++ )
	{
		if( inputs[i]->active == true )
		{
			return true;
		}
	}
	return false;*/

    if( keys.size() != 0 )
    {
        return true;
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
            if( event.type == SDL_KEYDOWN )
            {
            	bool found = false;
            	for( unsigned int i = 0; i < keys.size(); i++ )
                {
                    if( keys[i] == event.key.keysym.scancode )
                    {
                    	found = true;
                    }
                }
                if( !found )
                {
	                keys.push_back( event.key.keysym.scancode );
	                //engine->text->PrintString( "KeyDown:%x\n", event.key.keysym.scancode );
	            }
            }
            else if( event.type == SDL_KEYUP )
            {
                for( unsigned int i = 0; i < keys.size(); i++ )
                {
                    if( keys[i] == event.key.keysym.scancode )
                    {
                        keys.erase( keys.begin() + i );
                        //engine->text->PrintString( "KeyUp:%x\n", event.key.keysym.scancode );
                        break;
                    }
                }
            }

			/*for( unsigned int i = 0; i < inputs.size(); i++ )
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
			}*/
		}
	}
}