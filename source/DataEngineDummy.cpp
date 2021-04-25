//DataEngineDummy.h

#include "DataEngineDummy.h"
#include "GameEngine.h"

DataEngineDummy::DataEngineDummy( GameEngine* engine ) : DataEngine( engine )
{

}
DataEngineDummy::~DataEngineDummy()
{

}
void DataEngineDummy::Update()
{

}
void DataEngineDummy::LoadArchiveFile( string filePath )
{
	
}
void* DataEngineDummy::GetData( unsigned long id )
{
	return NULL;
}
void DataEngineDummy::FreeData( unsigned long id )
{

}
unsigned int DataEngineDummy::GetNumData()
{
	return 0;
} 
void DataEngineDummy::FreeAllData()
{

}