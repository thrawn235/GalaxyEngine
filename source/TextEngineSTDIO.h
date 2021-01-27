//Text Engine iostream

//include Guard
#ifndef TEXTENGINESTDIO
#define TEXTENGINESTDIO

//stdlib:
#include <string>
#include <stdio.h>
using namespace std;

//Galaxy includes
#include "TextEngine.h"

//forward declaration:


class TextEngineSTDIO : public TextEngine
{
protected:
public:
    TextEngineSTDIO();
    virtual void PrintString    ( string in );
    virtual void PrintChar      ( char in );
    virtual void PrintInt       ( int in );
    virtual void PrintFloat     ( float in );
    virtual void EndLine        ();
};

//include Guard End
#endif