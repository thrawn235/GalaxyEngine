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
public:
    				TextEngineSTDIO	();
    virtual void    PrintString     ( string format, ... );
    virtual void    EndLine         ();
    virtual void	DisableOutput	();
    virtual void	EnableOutput	();
    virtual bool 	GetOutput		();
    virtual void	SetOutput		( bool output );
};

//include Guard End
#endif