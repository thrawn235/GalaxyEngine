//Text Engine iostream

//========== include guard ===========
#ifndef TEXTENGINE_IOSTREAM
#define TEXTENGINE_IOSTREAM

//========== stdlib includes =========
#include <string>
#include <cstdarg>
#include <iostream>
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
    				TextEngineIOStream	();
    virtual void    PrintString     	( string format, ... );
    virtual void    EndLine         	();
    virtual void	DisableOutput		();
    virtual void	EnableOutput		();
    virtual bool 	GetOutput			();
    virtual void	SetOutput			( bool output );
};

//include Guard End
#endif