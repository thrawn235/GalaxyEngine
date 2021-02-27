//====================================
// InputEngineSDL.h
// handles all Input but primarily the keyboard
// This Implementation uses SDL and should work on Windows an Linux
//====================================

//========== include guard ===========
#ifndef INPUT_ENGINE_SDL
#define INPUT_ENGINE_SDL
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "InputEngine.h"
//====================================

//========= other includes ===========
#include <SDL2/SDL.h>
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
//====================================


class InputEngineSDL : public InputEngine
{
protected:
    
    vector<Action*>     actions;
    vector<Input*>      inputs;

public:
    //---------- Constructor / Destructor ------------
                        InputEngineSDL  ( GameEngine* engine );
                        ~InputEngineSDL ();

    //----------------- Events -----------------------
    unsigned int        AddAction       ( unsigned int input );
    void                DeleteAction    ( Action* action );
    void                DeleteAction    ( unsigned int uid );
    Action              GetAction       ( unsigned int uid );
    vector<Action>      GetAllActions   ();
    void                SetAction       ( unsigned int uid, Action* action );
    bool                ActionActive    ( unsigned int uid );
    bool                ActionActive    ( Action* action );

    //----------------- Inputs -----------------------
    vector<Input>       GetAllInputs    ();

    //---------------- Keyboard ----------------------
    bool                KeyDown         ( unsigned char scancode );
    bool                AnyKeyDown      ();

    void                Update          ();                                     //runs in every game loop
};

#endif