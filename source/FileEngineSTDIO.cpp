//FileEngineSTDIO.cpp

#include "FileEngineSTDIO.h"
#include "GameEngine.h"

FileEngineSTDIO::FileEngineSTDIO( GameEngine* engine ) : FileEngine( engine )
{
	this->engine = engine;
	this->engine->debug->PrintString( "file Engine STDIO constructor...\n" );


	highestID = 1;
}
FileEngineSTDIO::~FileEngineSTDIO()
{

}
void FileEngineSTDIO::Update()
{

}
unsigned int FileEngineSTDIO::Open( string filePath )
{
	this->engine->debug->PrintString( "open file %s...\n", filePath.c_str() );

	FileHandle file;
	file.filePointer = NULL;
	file.filePointer = fopen( filePath.c_str(), "rw" );
	this->engine->debug->PrintString( "file ID: %i..\n", highestID );

	if( file.filePointer != NULL )
	{
		this->engine->debug->PrintString( "file opend...\n" );
	}
	else
	{
		this->engine->debug->PrintString( "error couldnt open file error %i...\n", errno );
		return 0;
	}

	file.ID = highestID;
	highestID++;
	files.push_back( file );
    return highestID - 1;
}
void FileEngineSTDIO::Close( unsigned int fileID )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			fclose( files[i].filePointer );
			files.erase( files.begin() + i );
			break;
		}
	}
}
void FileEngineSTDIO::ReadWholeFile( unsigned int fileID, char* buffer )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			// obtain file size:
			

			// allocate memory to contain the whole file:
			/*buffer = (char*) malloc ( sizeof(char) * fileSize );
			if (buffer == NULL) 
			{
				engine->debug->PrintString( "Memory error! " );
				engine->Quit();
			}*/

			// copy the file into the buffer:
			fread( buffer, 1, GetFileSize( files[i].ID ), files[i].filePointer );
			if (buffer == NULL) 
			{
				engine->debug->PrintString( "reading error! " );
				engine->Quit();
			}
			return;
		}
	}
}
void FileEngineSTDIO::Read( unsigned int fileID, char* buffer, unsigned long length )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			/*buffer = (char*) malloc ( sizeof(char) * length );
			if (buffer == NULL) 
			{
				engine->debug->PrintString( "Memory error! " );
				engine->Quit();
			}*/

			// copy the file into the buffer:
			fread( buffer, 1, length, files[i].filePointer );
			if (buffer == NULL) 
			{
				engine->debug->PrintString( "reading error! " );
				engine->Quit();
			}
			return;
		}
	}
}
void FileEngineSTDIO::Read( unsigned int fileID, char* buffer, unsigned int start, unsigned long length )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			/*buffer = (char*) malloc ( sizeof(char) * length );
			if (buffer == NULL) 
			{
				engine->debug->PrintString( "Memory error! " );
				engine->Quit();
			}*/

			fseek ( files[i].filePointer , start , SEEK_SET );

			// copy the file into the buffer:
			fread( buffer, 1, length, files[i].filePointer );
			if (buffer == NULL) 
			{
				engine->debug->PrintString( "reading error! " );
				engine->Quit();
			}
			return;
		}
	}
}
void FileEngineSTDIO::Write( unsigned int fileID, char* data, unsigned long length )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			// copy the buffer into the file:
			fwrite( data, sizeof(char), length, files[i].filePointer );
			
			break;
		}
	}
}
void FileEngineSTDIO::Write( unsigned int fileID, char* data, unsigned long start, unsigned long length )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			fseek ( files[i].filePointer , start , SEEK_SET );

			// copy the buffer into the file:
			fwrite( data, sizeof(char), length, files[i].filePointer );
			
			break;
		}
	}
}
void FileEngineSTDIO::SetFilePos( unsigned int fileID, unsigned long pos )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			fseek ( files[i].filePointer, pos ,SEEK_SET );
			this->engine->debug->PrintString(" filepos set to %i\n", ftell( files[i].filePointer ) );
			return;
		}
	}
}
unsigned long FileEngineSTDIO::GetFilePos( unsigned int fileID )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			return ftell( files[i].filePointer );
		}
	}
	return 0;
}
unsigned long FileEngineSTDIO::GetFileSize( unsigned int fileID )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			// obtain file size:
			unsigned int pos = ftell( files[i].filePointer );

			fseek ( files[i].filePointer , 0 , SEEK_END );
			unsigned int fileSize = ftell ( files[i].filePointer );
			fseek( files[i].filePointer, pos, SEEK_SET );
			return fileSize;
		}
	}
	return 0;
}
void FileEngineSTDIO::Rewind( unsigned int fileID )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			rewind( files[i].filePointer );

			break;
		}
	}
}
void FileEngineSTDIO::SetFilePosEnd( unsigned int fileID )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			fseek ( files[i].filePointer , 0 , SEEK_END );

			break;
		}
	}
}
void FileEngineSTDIO::ChangeFilePos( unsigned int fileID, unsigned long delta )
{
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		if( files[i].ID == fileID )
		{
			fseek ( files[i].filePointer , delta , SEEK_CUR );

			break;
		}
	}
}