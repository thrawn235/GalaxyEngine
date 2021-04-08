//FileEngineSTDIO.cpp

#include "FileEngineSTDIO.h"

FileEngineSTDIO::FileEngineSTDIO( GameEngine* engine ) : FileEngine( engine )
{

}
FileEngineSTDIO::~FileEngineSTDIO()
{

}
void FileEngineSTDIO::Update()
{

}
unsigned int FileEngineSTDIO::Open( string filePath )
{
    return 0;
}
void FileEngineSTDIO::Close( unsigned int fileID )
{

}
char* FileEngineSTDIO::ReadWholeFile( unsigned int fileID )
{
    return NULL;
}
char* FileEngineSTDIO::Read( unsigned int fileID )
{
    return NULL;
}
char* FileEngineSTDIO::Read( unsigned int fileID, unsigned int start, unsigned long length )
{
    return NULL;
}
void FileEngineSTDIO::Write( char* data, unsigned long length )
{

}
void FileEngineSTDIO::Write( char* data, unsigned long start, unsigned long length )
{

}
void FileEngineSTDIO::SetFilePos( unsigned int fileID, unsigned long pos )
{

}
void FileEngineSTDIO::Rewind( unsigned int fileID )
{

}
void FileEngineSTDIO::SetFilePosEnd( unsigned int fileID )
{

}
void FileEngineSTDIO::ChangeFilePos( unsigned int fileID, unsigned long delta )
{

}