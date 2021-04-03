//====================================
// InputEngineDOS.h
// handles all Input but primarily the keyboard
// This Implementation uses the DOS BIOS
//====================================

//========== include guard ===========
#ifndef INPUT_ENGINE_DOS
#define INPUT_ENGINE_DOS
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
#include <sys/nearptr.h>
#include <sys/farptr.h>
#include <dpmi.h>
#include <go32.h>
#include <pc.h>
//====================================

//======= forward declarations =======
//====================================

//==================== defines ==========================
#define ESC         0x01
#define KEY_1       0x02
#define KEY_2       0x03
#define KEY_3       0x04
#define KEY_4       0x05
#define KEY_5       0x06
#define KEY_6       0x07
#define KEY_7       0x08
#define KEY_8       0x09
#define KEY_9       0x0A
#define KEY_0       0x0B
#define SPACE       0x39
#define ENTER       0x1C
#define LCTRL       0x1D
#define LSHIFT      0x2A
#define LALT        0x38
#define TAB         0x0f
#define KEY_W       0x11
#define KEY_A       0x1E
#define KEY_S       0x1f
#define KEY_D       0x20
#define KEY_Q       0x10
#define KEY_E       0x12
#define KEY_R       0x13
#define KEY_F       0x21
#define KEY_UP      0x48
#define KEY_DOWN    0x50
#define KEY_LEFT    0x4b
#define KEY_RIGHT   0x4d
#define KEY_F1      0x3b
#define KEY_F2      0x3c
#define KEY_F3      0x3d
#define KEY_F4      0x3e
#define KEY_F5      0x3f
#define KEY_F6      0x40
#define KEY_F7      0x41
#define KEY_F8      0x42
#define KEY_F9      0x43
#define KEY_F10     0x44
//=======================================================


class InputEngineDOS : public InputEngine
{
protected:
    
    vector<Action*>     actions;
    vector<Input*>      inputs;

    _go32_dpmi_seginfo OldISR, NewISR;

public:
    //---------- Constructor / Destructor ------------
                        InputEngineDOS              ( GameEngine* engine );
                        ~InputEngineDOS             ();

    //----------------- Events -----------------------
    void                AddAction                   ( Action action );
    void                DeleteAction                ( Action* action );
    void                DeleteAction                ( unsigned int uid );
    Action*             GetAction                   ( unsigned int uid );
    vector<Action*>     GetAllActions               ();
    bool                ActionActive                ( unsigned int uid );
    bool                ActionActive                ( Action* action );

    //----------------- Inputs -----------------------
    vector<Input*>      GetAllInputs                ();

    //---------------- Keyboard ----------------------
    bool                KeyDown                     ( unsigned char scancode );
    bool                AnyKeyDown                  ();

    void                Update                      ();                                     //runs in every game loop

    //DOS specific------------------------------------
    void                InstallKeyboardInterrupt    ();
    void                RestoreKeyboardInterrupt    ();

    void                ClearBiosKeyBuffer          ();
};

#endif