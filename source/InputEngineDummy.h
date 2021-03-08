//====================================
// InputEngineDummy.h
// Dummy Implementation of InputEngine
//====================================

//========== include guard ===========
#ifndef INPUT_ENGINE_DUMMY
#define INPUT_ENGINE_DUMMY
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
//====================================

//======= forward declarations =======
//====================================

//============= defines ==============
//====================================


class InputEngineDummy : public InputEngine
{
protected:

public:
    //---------- Constructor / Destructor ------------
                        InputEngineDummy    ( GameEngine* engine );
                        ~InputEngineDummy   ();

    //----------------- Events -----------------------
    void                AddAction           ( Action action );
    void                DeleteAction        ( Action* action );
    void                DeleteAction        ( unsigned int uid );
    Action*             GetAction           ( unsigned int uid );
    vector<Action*>     GetAllActions       ();
    bool                ActionActive        ( unsigned int uid );
    bool                ActionActive        ( Action* action );

    //----------------- Inputs -----------------------
    vector<Input*>      GetAllInputs        ();

    //---------------- Keyboard ----------------------
    bool                KeyDown             ( unsigned char scancode );
    bool                AnyKeyDown          ();

    void                Update              ();                                     //runs in every game loop
};

#endif