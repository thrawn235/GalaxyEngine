//FileEngineDummy.cpp

#include "FileEngineDummy.h"

FileEngineDummy::FileEngineDummy( GameEngine* engine ) : FileEngine( engine )
{

}
FileEngineDummy::~FileEngineDummy()
{

}
void FileEngineDummy::Update()
{

}
unsigned int FileEngineDummy::Open( string filePath )
{
    return 0;
}
void FileEngineDummy::Close( unsigned int fileID )
{

}
char* FileEngineDummy::ReadWholeFile( unsigned int fileID )
{
    return NULL;
}
char* FileEngineDummy::Read( unsigned int fileID, unsigned long length )
{
    return NULL;
}
char* FileEngineDummy::Read( unsigned int fileID, unsigned int start, unsigned long length )
{
    return NULL;
}
void FileEngineDummy::Write( unsigned int fileID, char* data, unsigned long length )
{

}
void FileEngineDummy::Write( unsigned int fileID, char* data, unsigned long start, unsigned long length )
{

}
void FileEngineDummy::SetFilePos( unsigned int fileID, unsigned long pos )
{

}
void FileEngineDummy::Rewind( unsigned int fileID )
{

}
void FileEngineDummy::SetFilePosEnd( unsigned int fileID )
{

}
void FileEngineDummy::ChangeFilePos( unsigned int fileID, unsigned long delta )
{

}