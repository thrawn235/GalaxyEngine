//====================================
// TimeEngineSDL.h
// Time Engine. Interface class for the time engine
// handles all timing related tasks
// DOS Implementation
//====================================

//========== include guard ===========
#ifndef TIME_ENGINE_SDL
#define TIME_ENGINE_SDL
//====================================

//========== stdlib includes =========
#include <vector>
using namespace std;
//====================================

//======== other includes ============
#include <SDL2/SDL.h>
//====================================

//========= galaxy includes ==========
#include "TimeEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
//====================================


class TimeEngineSDL : public TimeEngine
{
protected:
    GameEngine*         engine;

    unsigned long long  frameStart;
    unsigned long long  frameEnd;
    unsigned long long  frameTime;

    vector<TimeStamp>   timeStamps;
    int                 highestTimeStampID;

public:
                        TimeEngineSDL           ( GameEngine* engine );
    virtual             ~TimeEngineSDL          ();

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

    //SDL Specific----------------------------------------
};

#endif