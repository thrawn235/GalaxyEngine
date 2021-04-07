//TimeEngineSDL.cpp

#include "TimeEngineSDL.h"
#include "GameEngine.h"


TimeEngineSDL::TimeEngineSDL( GameEngine* engine ) : TimeEngine( engine )
{

	frameStart 	= 0;
	frameEnd  	= 10000;
	frameTime 	= 0;

	highestTimeStampID = 0;

	Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if( subsystem_init == 0 )
    {
        SDL_Init( 0 );
    }
    if( !(subsystem_init & SDL_INIT_TIMER) )
    {
        SDL_InitSubSystem( SDL_INIT_TIMER );
    }
}
TimeEngineSDL::~TimeEngineSDL()
{
	// Clean up
    Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if( subsystem_init == 0 )
    {
        SDL_Quit();
    } 
}

//FrameTiming
void TimeEngineSDL::FrameStart()
{
	frameStart = SDL_GetTicks();
	//
}
void TimeEngineSDL::FrameEnd()
{
	//frameEnd  = uclock();
	frameEnd = SDL_GetTicks();
	frameTime = frameEnd - frameStart;
}
int TimeEngineSDL::GetLastTime()
{
	return frameTime;
	//
}
int TimeEngineSDL::GetCurrentFrameTime()
{
	return SDL_GetTicks() - frameStart;
	//
}

//generalTiming
unsigned int TimeEngineSDL::GetCurrentTicks()
{
	//
	return SDL_GetTicks();
}
float TimeEngineSDL::GetCurrentTimeInMS()
{
	return SDL_GetTicks();
}

//Conversion
float TimeEngineSDL::TicksToMilliSeconds( unsigned long long ticksIn )
{
	//
	return ticksIn;
}
float TimeEngineSDL::TicksToSeconds( unsigned long long ticksIn )
{
	//
	return (float)ticksIn * 1000.0;
}
float TimeEngineSDL::GetFPS()
{
	if( TicksToMilliSeconds( frameTime ) > 0 )
	{
		return 1000.0 / TicksToMilliSeconds( frameTime ) ;
	}
	return 0;
}

//time stamps:
int TimeEngineSDL::AddTimeStamp()
{
	TimeStamp newTimeStamp;

	newTimeStamp.id = highestTimeStampID + 1;

	highestTimeStampID++;

	//newTimeStamp.timeStamp = uclock();
	newTimeStamp.timeStamp = SDL_GetTicks();

	timeStamps.push_back( newTimeStamp );
	
	return newTimeStamp.id;
}
void TimeEngineSDL::RemoveTimeStamp( int id )
{
	for( unsigned int i = 0; i < timeStamps.size(); i++ )
	{
		if( timeStamps[i].id == id )
		{
			timeStamps.erase( timeStamps.begin() + i );
		}
	}
}
unsigned long long TimeEngineSDL::GetTimeStamp( int id )
{
	for( unsigned int i = 0; i < timeStamps.size(); i++ )
	{
		if( timeStamps[i].id == id )
		{
			return timeStamps[i].timeStamp;
		}
	}
	return 0;
}
unsigned long long TimeEngineSDL::GetTimeSinceStamp( int id )
{
	for( unsigned int i = 0; i < timeStamps.size(); i++ )
	{
		if( timeStamps[i].id == id )
		{
			//return uclock() - timeStamps[i].timeStamp;
			return SDL_GetTicks() - timeStamps[i].timeStamp;
		}
	}
	return 0;
}
void TimeEngineSDL::ClearTimeStamps()
{
	timeStamps.clear();
	//
}