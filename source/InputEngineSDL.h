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
#define ESC         SDL_SCANCODE_ESCAPE
#define KEY_1       SDL_SCANCODE_1
#define KEY_2       SDL_SCANCODE_2
#define KEY_3       SDL_SCANCODE_3
#define KEY_4       SDL_SCANCODE_4
#define KEY_5       SDL_SCANCODE_5
#define KEY_6       SDL_SCANCODE_6
#define KEY_7       SDL_SCANCODE_7
#define KEY_8       SDL_SCANCODE_8
#define KEY_9       SDL_SCANCODE_9
#define KEY_0       SDL_SCANCODE_0
#define SPACE       SDL_SCANCODE_SPACE
#define ENTER       SDL_SCANCODE_RETURN
#define LCTRL       SDL_SCANCODE_LCTRL
#define LSHIFT      SDL_SCANCODE_LSHIFT
#define LALT        SDL_SCANCODE_LALT
#define TAB         SDL_SCANCODE_TAB
#define KEY_W       SDL_SCANCODE_W
#define KEY_A       SDL_SCANCODE_A
#define KEY_S       SDL_SCANCODE_S
#define KEY_D       SDL_SCANCODE_D
#define KEY_Q       SDL_SCANCODE_Q
#define KEY_E       SDL_SCANCODE_E
#define KEY_R       SDL_SCANCODE_R
#define KEY_F       SDL_SCANCODE_F
#define KEY_UP      SDL_SCANCODE_UP
#define KEY_DOWN    SDL_SCANCODE_DOWN
#define KEY_LEFT    SDL_SCANCODE_LEFT
#define KEY_RIGHT   SDL_SCANCODE_RIGHT
#define KEY_F1      SDL_SCANCODE_F1
#define KEY_F2      SDL_SCANCODE_F2
#define KEY_F3      SDL_SCANCODE_F3
#define KEY_F4      SDL_SCANCODE_F4
#define KEY_F5      SDL_SCANCODE_F5
#define KEY_F6      SDL_SCANCODE_F6
#define KEY_F7      SDL_SCANCODE_F7
#define KEY_F8      SDL_SCANCODE_F8
#define KEY_F9      SDL_SCANCODE_F9
#define KEY_F10     SDL_SCANCODE_F10
//====================================



class InputEngineSDL : public InputEngine
{
protected:
    
    vector<Action*>         actions;
    vector<Input*>          inputs;
    vector<unsigned char>    keys;

public:
    //---------- Constructor / Destructor ------------
                        InputEngineSDL  ( GameEngine* engine );
                        ~InputEngineSDL ();

    //----------------- Events -----------------------
    void                AddAction       ( Action action );
    void                DeleteAction    ( Action* action );
    void                DeleteAction    ( unsigned int uid );
    Action*             GetAction       ( unsigned int uid );
    vector<Action*>     GetAllActions   ();
    bool                ActionActive    ( unsigned int uid );
    bool                ActionActive    ( Action* action );

    //----------------- Inputs -----------------------
    vector<Input*>      GetAllInputs    ();

    //---------------- Keyboard ----------------------
    bool                KeyDown         ( unsigned char scancode );
    bool                AnyKeyDown      ();

    void                Update          ();                                     //runs in every game loop
};

#endif