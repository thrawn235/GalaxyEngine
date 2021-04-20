#include <iostream>
#include <filesystem>
#include <string>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <vector>
using namespace std;

int main( int argc, char* argv[] )
{
	char* fileName = NULL;

	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-filename") == 0)
		{
			if(i+1 <= argc)
			{
				fileName = argv[i+1];
			}
		}
	}

	FILE* file;
	file = fopen( fileName, "rw" );
	fseek( file, 0, SEEK_END );
	unsigned int filesize = ftell( file );
	rewind( file );

	char* buffer = (char*)malloc( filesize );

	fread( buffer, filesize, 1, file );
	fclose( file );

	printf("Filename: %s\n", fileName);
	char* withoutExtension = strtok(fileName, ".");
	printf("just filename: %s\n", withoutExtension);
	char oldName[100];
	strcpy(oldName, fileName);

	string name, number, extension;
	name = withoutExtension;
	extension = ".npal";
	string outName = name + number + extension;
	file = fopen( outName.c_str(), "wb+" );

	//write number of animation frames
	char magic[3] = {'P','A','L'};
	fwrite( magic, 1, 3, file );
	fwrite( buffer, 1, filesize, file );
	fclose( file );

	return 0;
}