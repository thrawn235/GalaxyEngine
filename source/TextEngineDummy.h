//====================================
//Dummy implementation of text engine
//====================================

//========== include guard ===========
#ifndef TEXTENGINE_DUMMY
#define TEXTENGINE_DUMMY

//========== stdlib includes =========
#include <string>
#include <cstdarg>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "TextEngine.h"
//====================================

//======= forward declarations =======
//====================================


class TextEngineDummy : public TextEngine
{
protected:
    bool output;
public:
    //------------------ Constructor / Destructor ----------------------
                    TextEngineDummy     ();

    //------------------------ Set / Get -------------------------------
    virtual void    DisableOutput       ();
    virtual void    EnableOutput        ();
    virtual bool    GetOutput           ();
    virtual void    SetOutput           ( bool output );

    //------------------------- Text Output ----------------------------
    virtual void    PrintString         ( string format, ... );
    virtual void    EndLine             ();

    //------------------------ Text Input ------------------------------
    virtual int     InputInt            ();
    virtual float   InputFloat          ();
    virtual char    InputChar           ();
    virtual string  InputString         ();
};

//include Guard End
#endif