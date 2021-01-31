//====================================
// TextEnginen.h
// Interface for Text output
// Used to print Text to the console, a file or serial. Depending on the implementation
// Its used in engine for Textoutput and debug output
// Planned implementations are a wrapper around printf or cout
//====================================

//========== include guard ===========
#ifndef TEXTENGINE
#define TEXTENGINE

//========== stdlib includes =========
#include <string>
#include <cstdarg>
using namespace std;
//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
//====================================


class TextEngine
{
protected:
public:
    //------------------ Constructor / Destructor ----------------------
                    TextEngine()                            {};

    //------------------------ Set / Get -------------------------------
    virtual void    DisableOutput   ()                      = 0;
    virtual void    EnableOutput    ()                      = 0;
    virtual bool    GetOutput       ()                      = 0;
    virtual void    SetOutput       ( bool output )         = 0;

    //------------------------- Text Output ----------------------------
    virtual void    PrintString     ( string format, ... )  = 0;
    virtual void    EndLine         ()                      = 0;

    //------------------------ Text Input ------------------------------
    virtual int     InputInt        ()                      = 0;
    virtual float   InputFloat      ()                      = 0;
    virtual char    InputChar       ()                      = 0;
    virtual string  InputString     ()                      = 0;
};

//include Guard End
#endif