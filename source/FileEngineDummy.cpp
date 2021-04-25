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
void FileEngineDummy::CloseAll()
{

}
void FileEngineDummy::ReadWholeFile( unsigned int fileID, char* buffer )
{

}
void FileEngineDummy::Read( unsigned int fileID, char* buffer, unsigned long length )
{

}
void FileEngineDummy::Read( unsigned int fileID, char* buffer, unsigned int start, unsigned long length )
{

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
unsigned long FileEngineDummy::GetFilePos( unsigned int fileID )
{
	return 0;
}
unsigned long FileEngineDummy::GetFileSize( unsigned int fileID )
{
	return 0;
}
void FileEngineDummy::ChangeFilePos( unsigned int fileID, unsigned long delta )
{

}