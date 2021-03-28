#include "TextEngineIOStream.h"

TextEngineIOStream::TextEngineIOStream()
{
    output = true;
}
void TextEngineIOStream::PrintString( string format, ... )
{
    va_list args;
    va_start( args, format );

    const char* formatCStr = format.c_str();

    if( output )
    {
        while (*formatCStr != '\0') 
        {
        	if (*formatCStr == '%')
        	{
        		++formatCStr;

		        if (*formatCStr == 'd' || *formatCStr == 'i' )
		        {
		            int i = va_arg(args, int);
		            std::cout << i;
		        }
		        else if (*formatCStr == 'c')
		        {
		            // note automatic conversion to integral type
		            int c = va_arg(args, int);
		            std::cout << static_cast<char>(c);
		        }
		        else if (*formatCStr == 'f')
		        {
		            double d = va_arg(args, double);
		            std::cout << d;
		        }
		    }
	        else
	        {
	        	cout<< (char)*formatCStr;
	        }
	        ++formatCStr;
	    }
    }
    va_end(args);
}
void TextEngineIOStream::EndLine()
{
    if( output )
    {
        cout<<endl;
    }
}
void TextEngineIOStream::DisableOutput()
{
    output = false;
}
void TextEngineIOStream::EnableOutput()
{
    output  = true;
}
bool TextEngineIOStream::GetOutput()
{
    return output;
}
void TextEngineIOStream::SetOutput( bool output )
{
    this->output = output;
}

int TextEngineIOStream::InputInt()
{
    if( output )
    {
        int out;
        cin>>out;
        return out;
    }
    return 0;
}
float TextEngineIOStream::InputFloat()
{
    if( output )
    {
        float out;
        cin>>out;
        return out;
    }
    return 0;
}
char TextEngineIOStream::InputChar()
{
    if( output )
    {
        char out;
        cin>>out;
        return out;
    }
    return 0;
}
string TextEngineIOStream::InputString()
{
	string out;
    if( output )
    {
        cin>>out;
        return out;
    }
    return out;
}
string TextEngineIOStream::SPrintString( string format, ... )
{
    va_list args;
    va_start( args, format );

    std::ostringstream out; 

    const char* formatCStr = format.c_str();

    if( output )
    {
        while (*formatCStr != '\0') 
        {
            if (*formatCStr == '%')
            {
                ++formatCStr;

                if (*formatCStr == 'd' || *formatCStr == 'i' )
                {
                    int i = va_arg(args, int);
                    out << i;
                }
                else if (*formatCStr == 'c')
                {
                    // note automatic conversion to integral type
                    int c = va_arg(args, int);
                    out << static_cast<char>(c);
                }
                else if (*formatCStr == 'f')
                {
                    double d = va_arg(args, double);
                    out << d;
                }
            }
            else
            {
                out<< (char)*formatCStr;
            }
            ++formatCStr;
        }
    }
    va_end(args);

    cout<<out.str();

    return out.str();
}