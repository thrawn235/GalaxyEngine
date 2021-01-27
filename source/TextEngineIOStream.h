//Text Engine iostream

//include Guard
#ifndef TEXTENGINEIOSTREAM
#define TEXTENGINEIOSTREAM

//stdlib:
#include <string>
#include <iostream>
using namespace std;

//Galaxy includes
#include "TextEngine.h"

//forward declaration:


class TextEngineIOStream : public TextEngine
{
protected:
public:
    TextEngineIOStream();
    virtual void PrintString    ( string in );
    virtual void PrintChar      ( char in );
    virtual void PrintInt       ( int in );
    virtual void PrintFloat     ( float in );
    virtual void EndLine        ();
};

//include Guard End
#endif