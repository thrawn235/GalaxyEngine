#include "TextEngineSTDIO.h"

TextEngineSTDIO::TextEngineSTDIO()
{
    output = true;
}
void TextEngineSTDIO::PrintString( string format, ... )
{
    va_list args;
    va_start( args, format );
    const char* cstr = format.c_str();
    if( output )
    {
        printf( cstr, args );
    }

    va_end( args );
}
void TextEngineSTDIO::EndLine()
{
    if( output )
    {
        printf( "\n" );
    }
}
void TextEngineSTDIO::DisableOutput()
{
    output = false;
}
void TextEngineSTDIO::EnableOutput()
{
    output  = true;
}
bool TextEngineSTDIO::GetOutput()
{
    return output;
}
void TextEngineSTDIO::SetOutput( bool output )
{
    this->output = output;
}