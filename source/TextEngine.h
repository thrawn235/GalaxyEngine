//Text Engine

//include Guard
#ifndef TEXTENGINE
#define TEXTENGINE

//stdlib:
#include <string>
using namespace std;

//Galaxy includes

//forward declaration:


class TextEngine
{
protected:
public:
	 				TextEngine() 	{};
	virtual void 	PrintString		( string in ) 	= 0;
	virtual void 	PrintChar		( char in ) 	= 0;
	virtual void 	PrintInt		( int in ) 		= 0;
	virtual void 	PrintFloat		( float in ) 	= 0;
	virtual void 	EndLine			() 				= 0;
};

//include Guard End
#endif