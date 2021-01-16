#include "TextEngineSTDIO.h"

TextEngineSTDIO::TextEngineSTDIO()
{
}
void TextEngineSTDIO::PrintString( string in )
{
	printf( "%s", in.c_str() );
}
void TextEngineSTDIO::PrintChar( char in )
{
	printf( "%c", in );
}
void TextEngineSTDIO::PrintInt( int in )
{
	printf( "%i", in );
}
void TextEngineSTDIO::PrintFloat( float in )
{
	printf( "%f", in );
}
void TextEngineSTDIO::EndLine()
{
	printf( "\n" );
}