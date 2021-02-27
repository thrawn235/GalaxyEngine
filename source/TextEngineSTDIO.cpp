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
        vprintf( cstr, args );
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

int TextEngineSTDIO::InputInt()
{
    if( output )
    {
        int out;
        scanf( "%i", &out );
        return out;
    }
    return 0;
}
float TextEngineSTDIO::InputFloat()
{
    if( output )
    {
        float out;
        scanf( "%f", &out );
        return out;
    }
    return 0;
}
char TextEngineSTDIO::InputChar()
{
    if( output )
    {
        char out;
        scanf( "%c", &out );
        return out;
    }
    return 0;
}
string TextEngineSTDIO::InputString()
{
    printf("input string...\n");
    string out;
    if( output )
    {
        scanf( "%s", stringInputBuffer );
        printf("read%s\n", stringInputBuffer );
        out.assign(stringInputBuffer);
        //printf("read%sjhjh\n", out.c_str() );
    }
    return out;
}