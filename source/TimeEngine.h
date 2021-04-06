//====================================
// TimeEngine.h
// Time Engine. Interface class for the time engine
// handles all timing related tasks
//====================================

//========== include guard ===========
#ifndef TIME_ENGINE
#define TIME_ENGINE
//====================================

//========== stdlib includes =========
#include <vector>
using namespace std;

//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
#define TIME_TYPE_DUMMY    0
#define TIME_TYPE_SDL      1
#define TIME_TYPE_DOS      2
//====================================

struct TimeStamp
{
    int                 id;
    unsigned long long  timeStamp;
};


class TimeEngine
{
protected:
    

public:
                                    TimeEngine              ( GameEngine* engine )          {};
    virtual                         ~TimeEngine             ()                              {};


    //Set
    virtual     void                SetInterruptFrequency   ( int newInterruptFrequency )   = 0;

    //Get
    virtual     int                 GetInterruptFrequency   ()                              = 0;
    virtual     int                 GetTicksPerSecond       ()                              = 0;

    //FrameTiming
    virtual     void                FrameStart              ()                              = 0;
    virtual     void                FrameEnd                ()                              = 0;
    virtual     int                 GetLastTime             ()                              = 0;
    virtual     int                 GetCurrentFrameTime     ()                              = 0;

    //generalTiming
    virtual     unsigned int        GetCurrentTicks         ()                              = 0;
    virtual     float               GetCurrentTimeInMS      ()                              = 0;

    //Conversion
    virtual     float               TicksToMilliSeconds     ( unsigned long long ticksIn )  = 0;
    virtual     float               TicksToSeconds          ( unsigned long long ticksIn )  = 0;
    virtual     float               GetFPS                  ()                              = 0;

    //time stamps:
    virtual     int                 AddTimeStamp            ()                              = 0;
    virtual     void                RemoveTimeStamp         ( int id )                      = 0;
    virtual     unsigned long long  GetTimeStamp            ( int id )                      = 0;
    virtual     unsigned long long  GetTimeSinceStamp       ( int id )                      = 0;
    virtual     void                ClearTimeStamps         ()                              = 0;
};

#endif