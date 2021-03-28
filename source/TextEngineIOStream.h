//Text Engine iostream

//========== include guard ===========
#ifndef TEXTENGINE_IOSTREAM
#define TEXTENGINE_IOSTREAM

//========== stdlib includes =========
#include <string>
#include <cstdarg>
#include <iostream>
#include <sstream> // for ostringstream
using namespace std;
//====================================

//========= galaxy includes ==========
#include "TextEngine.h"
//====================================

//======= forward declarations =======
//====================================


class TextEngineIOStream : public TextEngine
{
protected:
    bool output;
public:
    //------------------ Constructor / Destructor ----------------------
                    TextEngineIOStream  ();

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

    //------------------------ String Creation -------------------------
    virtual string  SPrintString    ( string format, ... );
};

//include Guard End
#endif