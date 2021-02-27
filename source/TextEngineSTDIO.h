//Text Engine stdio

//========== include guard ===========
#ifndef TEXTENGINESTDIO
#define TEXTENGINESTDIO

//========== stdlib includes =========
#include <string>
#include <cstdarg>
#include <stdio.h>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "TextEngine.h"
//====================================

//======= forward declarations =======
//====================================


class TextEngineSTDIO : public TextEngine
{
protected:
    bool output;
    char stringInputBuffer[64];
public:
    //------------------ Constructor / Destructor ----------------------
                    TextEngineSTDIO ();

    //------------------------ Set / Get -------------------------------
    virtual void    DisableOutput   ();
    virtual void    EnableOutput    ();
    virtual bool    GetOutput       ();
    virtual void    SetOutput       ( bool output );

    //------------------------- Text Output ----------------------------
    virtual void    PrintString     ( string format, ... );
    virtual void    EndLine         ();

    //------------------------ Text Input ------------------------------
    virtual int     InputInt        ();
    virtual float   InputFloat      ();
    virtual char    InputChar       ();
    virtual string  InputString     ();
};

//include Guard End
#endif