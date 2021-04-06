//====================================
// TimeEngineDummy.h
// Time Engine. Interface class for the time engine
// handles all timing related tasks
// Dummy Implementation
//====================================

//========== include guard ===========
#ifndef TIME_ENGINE_DUMMY
#define TIME_ENGINE_DUMMY
//====================================

//========== stdlib includes =========
#include <vector>
using namespace std;

//====================================

//========= galaxy includes ==========
#include "TimeEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
//====================================


class TimeEngineDummy : public TimeEngine
{
protected:
    

public:
                        TimeEngineDummy         ( GameEngine* engine );
    virtual             ~TimeEngineDummy        ();


    //Set
    void                SetInterruptFrequency   ( int newInterruptFrequency );

    //Get
    int                 GetInterruptFrequency   ();
    int                 GetTicksPerSecond       ();

    //FrameTiming
    void                FrameStart              ();
    void                FrameEnd                ();
    int                 GetLastTime             ();
    int                 GetCurrentFrameTime     ();

    //generalTiming
    unsigned int        GetCurrentTicks         ();
    float               GetCurrentTimeInMS      ();

    //Conversion
    float               TicksToMilliSeconds     ( unsigned long long ticksIn );
    float               TicksToSeconds          ( unsigned long long ticksIn );
    float               GetFPS                  ();

    //time stamps:
    int                 AddTimeStamp            ();
    void                RemoveTimeStamp         ( int id );
    unsigned long long  GetTimeStamp            ( int id );
    unsigned long long  GetTimeSinceStamp       ( int id );
    void                ClearTimeStamps         ();
};

#endif