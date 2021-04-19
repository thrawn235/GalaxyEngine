//DataEngineNGR.h

#include "DataEngineNGR.h"
#include "GameEngine.h"

DataEngineNGR::DataEngineNGR( GameEngine* engine ) : DataEngine( engine )
{
	this->engine = engine;
	this->engine->debug->PrintString( "DataEngine NGR - Consructor...\n" );
}
DataEngineNGR::~DataEngineNGR()
{
	//close all files on exit
	this->engine->debug->PrintString( "DataEngine NGR - Destructor...\n" );
	this->engine->debug->PrintString( "Closing all files...\n" );
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		this->engine->debug->PrintString( "close %i ...\n", i );
		this->engine->file->Close( files[i] );
	}
}
void DataEngineNGR::Update()
{

}
void DataEngineNGR::LoadArchiveFile( string filePath )
{
	this->engine->debug->PrintString( "load asset file - %s...\n", filePath.c_str() );
	int file = engine->file->Open( filePath );
	if( file != 0 )
	{
		files.push_back( file );
	}
}
void* DataEngineNGR::GetData( unsigned long id )
{
	this->engine->debug->PrintString( "loading id: %i...\n", id );
	//data already loaded ?
	for( unsigned int i = 0; i < dataBlocks.size(); i++ )
	{
		if( dataBlocks[i].id == id )
		{
			//yes
			this->engine->debug->PrintString( "ID found asset already loaaded...\n" );
			return dataBlocks[i].data;
		}
	}

	//no
	this->engine->debug->PrintString( "asset not found. looking in file...\n" );
	for( unsigned int i = 0; i < files.size(); i++ )
	{
		//goto TOC
		NGRHeader header;
		this->engine->debug->PrintString( "read NGR Header...\n" );
		engine->file->Read( files[i], (char*)&header, sizeof(NGRHeader) );
		//fread( &header, sizeof(NGRHeader), 1, files[i] );
		//fseek( files[i], header.offsetTOC, SEEK_SET );
		this->engine->debug->PrintString( "jump to TOC at %i...\n", header.offsetTOC );
		engine->file->SetFilePos( files[i], header.offsetTOC );

		//read TOC
		//vector<TOCEntry> newEntries;
		this->engine->debug->PrintString( "read TOC...\n" );
		for( unsigned int u = 0; u < header.numItems; u++ )
		{
			this->engine->debug->PrintString( "TOC Entry %i...\n", u );
			this->engine->debug->PrintString( "current offset %i\n", header.offsetTOC );
			this->engine->debug->PrintString( "read...\n" );
			TOCEntry entry;
			engine->file->Read( files[i], (char*)&entry, sizeof(TOCEntry) );
			engine->debug->PrintString( "TOCEntry: %i id: %i offset: %i size: %i name: %s\n", u, entry.id, entry.offset, entry.size, entry.name );

			//fread( &entry, sizeof(TOCEntry), 1, files[i] );
			//newEntries.push_back( entry );
			if( entry.id == id )
			{
				this->engine->debug->PrintString( "asset found in TOC...\n" );
				//cout<<"TOCEntry: "<<u<<" offset: "<<entry.id<<entry.offset<<" size: "<<entry.size<<" Name: "<<entry.name<<endl;
				engine->debug->PrintString( "TOCEntry: %i id: %i offset: %i size: %i name: %s\n", u, entry.id, entry.offset, entry.size, entry.name );
				DataBlock newBlock;
				newBlock.id = entry.id;
				this->engine->debug->PrintString( "reading Data...\n" );
				engine->file->SetFilePos( files[i], entry.offset /*+ 3 */ );
				//fseek( files[i], entry.offset + 3, SEEK_SET );
				newBlock.data = (char*)malloc( entry.size /*- 3*/ );
				engine->file->Read( files[i], newBlock.data, entry.size /*- 3*/ );
				//fread( newBlock.data, entry.size - 3, 1, files[i] );
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