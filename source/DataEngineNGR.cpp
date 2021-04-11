//DataEngineNGR.h

#include "DataEngineNGR.h"
#include "GameEngine.h"

DataEngineNGR::DataEngineNGR( GameEngine* engine ) : DataEngine( engine )
{
	this->engine = engine;

}
DataEngineNGR::~DataEngineNGR()
{
	//close all files on exit
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		fclose( files[i] );
	}
}
void DataEngineNGR::Update()
{

}
void DataEngineNGR::LoadArchiveFile( string filePath )
{
	FILE* file;
	file = fopen( filePath.c_str(), "rb" );
	files.push_back( file );
}
void* DataEngineNGR::GetData( unsigned long id )
{
	//data already loaded ?
	for( unsigned int i = 0; i < dataBlocks.size(); i++ )
	{
		if( dataBlocks[i].id == id )
		{
			//yes
			return dataBlocks[i].data;
		}
	}

	//no
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		//goto TOC
		NGRHeader header;
		fread( &header, sizeof(NGRHeader), 1, files[i] );
		fseek( files[i], header.offsetTOC, SEEK_SET );

		//read TOC
		//vector<TOCEntry> newEntries;
		for( unsigned int u = 0; u < header.numItems; u++ )
		{
			TOCEntry entry;
			fread( &entry, sizeof(TOCEntry), 1, files[i] );
			//newEntries.push_back( entry );
			if( entry.id == id )
			{
				//cout<<"TOCEntry: "<<u<<" offset: "<<entry.id<<entry.offset<<" size: "<<entry.size<<" Name: "<<entry.name<<endl;
				engine->debug->PrintString( "TOCEntry: %i id: %i offset: %i size: %i name: %s\n", u, entry.id, entry.offset, entry.size, entry.name );
				DataBlock newBlock;
				newBlock.id = entry.id;
				fseek( files[i], entry.offset + 3, SEEK_SET );
				fread( newBlock.data, entry.size - 3, 1, files[i] );
				dataBlocks.push_back( newBlock );
				return newBlock.data;
			}
		}
	}

	//not found at all...
	return NULL;
}
void DataEngineNGR::FreeData( unsigned long id )
{
	for( unsigned int i = 0; i < dataBlocks.size(); i++ )
	{
		if( dataBlocks[i].id == id )
		{
			free( dataBlocks[i].data );
			dataBlocks.erase( dataBlocks.begin() + i );
			return;
		}
	}
}