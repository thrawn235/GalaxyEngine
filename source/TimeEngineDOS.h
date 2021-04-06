//====================================
// TimeEngineDOS.h
// Time Engine. Interface class for the time engine
// handles all timing related tasks
// DOS Implementation
//====================================

//========== include guard ===========
#ifndef TIME_ENGINE_DOS
#define TIME_ENGINE_DOS
//====================================

//========== stdlib includes =========
#include <vector>
using namespace std;
//====================================

//======== other includes ============
#include <sys/nearptr.h>
#include <sys/farptr.h>
#include <dpmi.h>
#include <go32.h>
#include <pc.h>
//====================================

//========= galaxy includes ==========
#include "TimeEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
//====================================


class TimeEngineDOS : public TimeEngine
{
protected:
    GameEngine*         engine;

    unsigned long long  frameStart;
    unsigned long long  frameEnd;
    unsigned long long  frameTime;

    vector<TimeStamp>   timeStamps;
    int                 highestTimeStampID;

    int                 interruptFrequency;
    float               ticksPerSecond;

    bool                ticked;

    _go32_dpmi_seginfo  OldISR, NewISR;

public:
                        TimeEngineDOS           ( GameEngine* engine );
    virtual             ~TimeEngineDOS          ();

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

    //DOS Specific----------------------------------------
    //Set
    void                SetInterruptFrequency   ( int newInterruptFrequency );

    //Get
    int                 GetInterruptFrequency   ();
    
    //Interrupt
    void                InstallTimerInterrupt   ();
    void                RestoreTimerInterrupt   ();

    //Set
    void                SetTicked               ( bool newTicked );
    void                WaitForTicked           ();
};

#endif