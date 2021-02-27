//====================================
// InputEngine.h
// handles all Input but primarily the keyboard
//====================================

//========== include guard ===========
#ifndef INPUT_ENGINE
#define INPUT_ENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GameEngine.h"
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
//====================================


struct Input
{
    unsigned int    uid;
    string          description;    //example: w,a,s,d,space,F1,left muse button
    bool            active;         //pressed ?
    float           value;          //joystick or mouse axis
};


struct Action
{
    unsigned int    uid;
    Input*          input;          //pointer to one of all possible inputs (keypress, mousebutton etc)
    string          description;    //example: jump, fire, duck
    bool            active;
};


class InputEngine
{
protected:
    GameEngine* engine;
public:
    //---------- Constructor / Destructor ------------
                                InputEngine     ( GameEngine* engine )                  {};
    virtual                     ~InputEngine    ()                                      {};

    //----------------- Events -----------------------
    virtual unsigned int        AddAction       ( unsigned int input )                  = 0;
    virtual void                DeleteAction    ( Action* action )                      = 0;
    virtual void                DeleteAction    ( unsigned int uid )                    = 0;
    virtual Action              GetAction       ( unsigned int uid )                    = 0;
    virtual vector<Action*>     GetAllActions   ()                                      = 0;
    virtual void                SetAction       ( unsigned int uid, Action* action )    = 0;
    virtual bool                ActionActive    ( unsigned int uid )                    = 0;
    virtual bool                ActionActive    ( Action* action )                      = 0;

    //----------------- Inputs -----------------------
    virtual vector<Input*>      GetAllInputs    ()                                      = 0;

    //---------------- Keyboard ----------------------
    virtual bool                KeyDown         ( unsigned char scancode )              = 0;
    virtual bool                AnyKeyDown      ()                                      = 0;

    virtual void                Update          ()                                      = 0;        //runs in every game loop
};

#endif