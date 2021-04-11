#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class StringConverter
{
protected:
	long fileSize;
public:
	StringConverter()
	{

	}
	char* LoadFile( string filePath )
	{
		cout<<"Loading files..."<<endl;
		cout<<"open file..."<<endl;
		FILE* file = fopen( filePath.c_str(), "rb" );
		// obtain file size:
		cout<<"obtain size"<<endl;
		fseek ( file , 0 , SEEK_END );
		fileSize = ftell ( file );
		rewind ( file );
		cout<<"filesize = "<<fileSize<<endl;

		// allocate memory to contain the whole file:
		cout<<"allocate memory..."<<endl;
		char* buffer = (char*) malloc ( sizeof(char) * fileSize );
		if (buffer == NULL) 
		{
			printf( "Memory error! " );
		}

		// copy the file into the buffer:
		cout<<"reading file..."<<endl;
		fread( buffer, 1, fileSize, file );
		if (buffer == NULL) 
		{
			printf( "reading error! " );
		}
		fclose( file );
		return buffer;
	}
	char* Convert( char* buffer )
	{
		cout<<"convert..."<<endl;
		cout<<"allocate memory"<<endl;
		char* outBuffer = (char*)malloc( fileSize + 3 );
		cout<<"write file sig..."<<endl;
		outBuffer[0] = 'S';
		outBuffer[1] = 'T';
		outBuffer[2] = 'R';
		cout<<"copy buffer to outbuffer..."<<endl;
		memcpy( &outBuffer[3], buffer, fileSize );
		cout<<"done!"<<endl;
		return outBuffer;
	}
	void SaveFile( string filePath, char* buffer )
	{
		cout<<"save file..."<<endl;
		cout<<"open file..."<<endl;
		FILE* file = fopen( filePath.c_str(), "wb" );

		// copy the file into the buffer:
		cout<<"write..."<<endl;
		fwrite( buffer, 1, fileSize + 3, file );
		if (buffer == NULL) 
		{
			printf( "reading error! " );
		}
		fclose( file );
	}
};

int main( int argc, char *argv[] )
{
	if( argc != 3 )
	{
		cout<<"error - wrong number of arguments"<<endl;
		return 0;
	}
	StringConverter stringConverter;

	char* buffer = stringConverter.LoadFile( string( argv[1] ) );
	stringConverter.SaveFile( string( argv[2] ), stringConverter.Convert( buffer ) );

	return 0;
}