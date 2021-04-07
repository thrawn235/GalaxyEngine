//TimeEngineDOS.cpp

#include "TimeEngineDOS.h"
#include "GameEngine.h"


//============= global Variables for the Interrupt Service Routine ========
unsigned long long timeCount = 0;
TimeEngineDOS* globalPTime;
//=========================================================================

//============ global Function that is to be installed as ISR =============
void TimerInterruptRoutine()
{
	timeCount = timeCount + 1;
	globalPTime->SetTicked( true );
}
//unused dummy functions. meant to calculate the size of TimerInterruptRoutine()
void TimerInterruptRoutineEnd() {} 
//======================================================================



TimeEngineDOS::TimeEngineDOS( GameEngine* engine ) : TimeEngine( engine )
{
	globalPTime = this;

	frameStart 	= 0;
	frameEnd  	= 10000;
	frameTime 	= 0;

	ticked = false;
	

	//start timer:
	SetInterruptFrequency( 700 );
	//uclock();

	InstallTimerInterrupt();

	highestTimeStampID = 0;

	WaitForTicked();
}
TimeEngineDOS::~TimeEngineDOS()
{
	_go32_dpmi_set_protected_mode_interrupt_vector( 0x08, &OldISR );
	//
}

//FrameTiming
void TimeEngineDOS::FrameStart()
{
	//frameStart = uclock();
	frameStart = timeCount;
	//
}
void TimeEngineDOS::FrameEnd()
{
	//frameEnd  = uclock();
	frameEnd = timeCount;
	frameTime = frameEnd - frameStart;
}
int TimeEngineDOS::GetLastTime()
{
	return frameTime;
	//
}
int TimeEngineDOS::GetCurrentFrameTime()
{
	//return uclock() - frameStart;
	return timeCount - frameStart;
	//
}

//generalTiming
unsigned int TimeEngineDOS::GetCurrentTicks()
{
	//
	//return uclock();
	return timeCount;
}
float TimeEngineDOS::GetCurrentTimeInMS()
{
	//
	//return uclock() / ( UCLOCKS_PER_SEC / 1000 );
	float temp = ( (float)ticksPerSecond / 1000 );
	return (float)timeCount / temp;
}

//Conversion
float TimeEngineDOS::TicksToMilliSeconds( unsigned long long ticksIn )
{
	//
	//return ticksIn / ( UCLOCKS_PER_SEC / 1000 );
	float temp = ( (float)ticksPerSecond / 1000.0 );
	return (float)ticksIn / temp ;
}
float TimeEngineDOS::TicksToSeconds( unsigned long long ticksIn )
{
	//
	//return ticksIn / UCLOCKS_PER_SEC;
	return (float)ticksIn / (float)ticksPerSecond;
}
float TimeEngineDOS::GetFPS()
{
	if( TicksToMilliSeconds( frameTime ) > 0 )
	{
		return 1000.0 / TicksToMilliSeconds( frameTime ) ;
	}
	return 0;
}

//time stamps:
int TimeEngineDOS::AddTimeStamp()
{
	TimeStamp newTimeStamp;

	newTimeStamp.id = highestTimeStampID + 1;

	highestTimeStampID++;

	//newTimeStamp.timeStamp = uclock();
	newTimeStamp.timeStamp = timeCount;

	timeStamps.push_back( newTimeStamp );
	
	return newTimeStamp.id;
}
void TimeEngineDOS::RemoveTimeStamp( int id )
{
	for( unsigned int i = 0; i < timeStamps.size(); i++ )
	{
		if( timeStamps[i].id == id )
		{
			timeStamps.erase( timeStamps.begin() + i );
		}
	}
}
unsigned long long TimeEngineDOS::GetTimeStamp( int id )
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
unsigned long long TimeEngineDOS::GetTimeSinceStamp( int id )
{
	for( unsigned int i = 0; i < timeStamps.size(); i++ )
	{
		if( timeStamps[i].id == id )
		{
			//return uclock() - timeStamps[i].timeStamp;
			return timeCount - timeStamps[i].timeStamp;
		}
	}
	return 0;
}
void TimeEngineDOS::ClearTimeStamps()
{
	timeStamps.clear();
	//
}

//DOS Specific----------------------------------------
//Set
void TimeEngineDOS::SetInterruptFrequency( int newInterruptFrequency )
{
	interruptFrequency  = newInterruptFrequency;

	ticksPerSecond 		= interruptFrequency;

	//set programmable interrupt timer to specific frequency
	int freq = 1193182 / interruptFrequency;
	outportb( 0x43, 0x34 );
	outportb( 0x40, freq & 0xFF );
	outportb( 0x40, ( freq >> 8 ) & 0xFF );
}

//Get
int TimeEngineDOS::GetInterruptFrequency()
{
	return interruptFrequency;
}

//Interrupt
void TimeEngineDOS::InstallTimerInterrupt()
{
	_go32_dpmi_lock_data( ( void* )timeCount, ( long )sizeof( timeCount ) );
 	_go32_dpmi_get_protected_mode_interrupt_vector( 0x08, &OldISR );
	
	NewISR.pm_offset = ( int )TimerInterruptRoutine;
	NewISR.pm_selector = _go32_my_cs();

	_go32_dpmi_chain_protected_mode_interrupt_vector( 0x08, &NewISR );
}
void TimeEngineDOS::RestoreTimerInterrupt()
{
	_go32_dpmi_set_protected_mode_interrupt_vector( 0x08, &OldISR );
	//
}

//Set
void TimeEngineDOS::SetTicked( bool newTicked )
{
	ticked = newTicked;
	//
}
void TimeEngineDOS::WaitForTicked()
{
	int i = 0;
	while( ticked == false )
	{
		i++;
	}
	ticked = false;
}