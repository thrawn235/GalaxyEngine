//TimeEngineDummy.cpp

#include "TimeEngineDummy.h"
#include "GameEngine.h"


TimeEngineDummy::TimeEngineDummy( GameEngine* engine ) : TimeEngine( engine )
{

}
TimeEngineDummy::~TimeEngineDummy()
{

}

//FrameTiming
void TimeEngineDummy::FrameStart()
{

}
void TimeEngineDummy::FrameEnd()
{

}
int TimeEngineDummy::GetLastTime()
{
    return 0;
}
int TimeEngineDummy::GetCurrentFrameTime()
{
    return 0;
}

//generalTiming
unsigned int TimeEngineDummy::GetCurrentTicks()
{
    return 0;
}
float TimeEngineDummy::GetCurrentTimeInMS()
{
    return 0.0;
}

//Conversion
float TimeEngineDummy::TicksToMilliSeconds( unsigned long long ticksIn )
{
    return 0.0;
}
float TimeEngineDummy::TicksToSeconds( unsigned long long ticksIn )
{
    return 0.0;
}
float TimeEngineDummy::GetFPS()
{
    return 0.0;
}

//time stamps:
int TimeEngineDummy::AddTimeStamp()
{
    return 0;
}
void TimeEngineDummy::RemoveTimeStamp( int id )
{

}
unsigned long long TimeEngineDummy::GetTimeStamp( int id )
{
    return 0;
}
unsigned long long TimeEngineDummy::GetTimeSinceStamp( int id )
{
    return 0;
}
void TimeEngineDummy::ClearTimeStamps()
{

}