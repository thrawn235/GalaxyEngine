#include <vector>
#include <stdio.h>
#include <iostream>
//#include <conio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <string>

using namespace std;

#include "Vector2D.h"
#include "TMXStructs.h"


struct XMLValuePair
{
	string name;
	string value;
};

struct XMLLine
{
	char 					firstChar;
	string 					tag;
	vector<XMLValuePair> 	pairs;
	bool 					closing;
};


void PrintXMLLine( XMLLine line )
{
	printf("<%c%s ", line.firstChar, line.tag.c_str() );
	for( unsigned int i = 0; i < line.pairs.size(); i++ )
	{
		printf( "%s=\"%s\" ", line.pairs[i].name.c_str(), line.pairs[i].value.c_str() );
	}
	printf( "> closing=%i\n", line.closing );
}

XMLLine ExtractXMLLine( FILE* file )
{
	XMLLine line;

	//first character in line
	fscanf( file, "<%c", &line.firstChar );
	if( line.firstChar == '?' )
	{
		
	}
	else if( line.firstChar == '/' )
	{
		line.closing = true;
	}
	else
	{
		line.firstChar = ' ';
		fseek( file, -1, SEEK_CUR );
	}
	fscanf( file, "%s ", line.tag.c_str() );
	printf("%s\n", line.tag.c_str() );

	XMLValuePair pair;
	char whitespace = ' ';
	
	bool done = false;
	while( !done )
	{
		//printf("test\n");
		fscanf( file, "%[^=]=", pair.name.c_str() );
		printf("%s\n", pair.name.c_str() );
		fscanf( file, "\"%[^\"]\"", pair.value.c_str() );
		printf("%s\n", pair.value.c_str() );
		line.pairs.push_back( pair );
		fscanf( file, "%c", &whitespace );
		if( whitespace == '?' )
		{
			fscanf( file, "%c>\n", &whitespace );
			done = true;
			line.closing = true;
		}
		if( whitespace == '/' )
		{
			fscanf( file, "%c>\n", &whitespace );
			line.closing = true;
			done = true;
		}
		if( whitespace == '>' )
		{
			fscanf( file, "\n" );
			done =  true;
			line.closing = false;
		}
	}

	PrintXMLLine( line );
	return line;
}


class TMXConverter
{
protected:
public:
	TMXConverter()
	{
		//filter();
		//newterm( NULL, NULL, NULL );
	}

	//==================== Level Methods =======================
	TMXMap LoadTMXMap( const char* filePath )
	{
		/*	The Method loads a tmx file in xml format (no json file etc).
			It does not do any error checking. Program will crash if File is inconsistent
			It can only handle square grids. no hex or isometric stuff
			it doesnt do text or polyline objects
			it cant handle groups (restructuring in subfunctions would be neccesary)
			lots of stuff is untested, like files withoud embedded tileset data or empty tilesets
			Its rather slow too...
			Use with caution 
		*/


		TMXMap newTMXMap;

		bool debug = true;





		char XMLTag[30];

		//open File, read only (txt mode)
		FILE* file = fopen( filePath, "r" );
		if( file == NULL )
		{
			Quit( "Error opening TMX File" );
		}

		XMLLine line = ExtractXMLLine( file );
		PrintXMLLine( line );
		getch();


		/*//read XML Data
		fscanf( file, "<?xml version=\"%f\" encoding=\"%[^\"]\"?>\n", &newTMXMap.XMLVersion, newTMXMap.encoding );
		if(debug)
		{
			printf( "xml version 	= %f \n", newTMXMap.XMLVersion 	);
			printf( "xml encoding 	= %s \n", newTMXMap.encoding 	);
			getch();
		}

		//read map data:
		fscanf( file, "<%[^> ]", XMLTag );
		if( debug )
		{
			printf( "XMLTag= %s \n", XMLTag );
		}
		if( strcmp( XMLTag, "map" ) != 0 )
		{
			Quit( "couldnt find map XML tag. Invalid TMX File" );
		}
		getch();

		fscanf(	file, " version=\"%f\" tiledversion=\"%[^\"]\" orientation=\"%[^\"]\" renderorder=\"%[^\"]\" width=\"%i\" height=\"%i\" tilewidth=\"%i\" tileheight=\"%i\" infinite=\"%i\" nextlayerid=\"%i\" nextobjectid=\"%i\">\n", 
		       	&newTMXMap.version, newTMXMap.tiledVersion, newTMXMap.orientation, newTMXMap.renderOrder, &newTMXMap.width, &newTMXMap.height, &newTMXMap.tileWidth, &newTMXMap.tileHeight, &newTMXMap.infinite, &newTMXMap.nextLayerID, &newTMXMap.nextObjectID );

		if( debug )
		{
			printf( "version 		= %f \n", newTMXMap.version 		);
			printf( "tiledVersion 	= %s \n", newTMXMap.tiledVersion 	);
			printf( "orientation 	= %s \n", newTMXMap.orientation 	);
			printf( "renderOrder 	= %s \n", newTMXMap.renderOrder 	);
			printf( "width 			= %i \n", newTMXMap.width 			);
			printf( "height 		= %i \n", newTMXMap.height 			);
			printf( "tileWidth 		= %i \n", newTMXMap.tileWidth 		);
			printf( "tileheight 	= %i \n", newTMXMap.tileHeight 		);
			printf( "infinite 		= %i \n", newTMXMap.infinite		);
			printf( "nextLayerID 	= %i \n", newTMXMap.nextLayerID 	);
			printf( "nextObjectID 	= %i \n", newTMXMap.nextObjectID 	);
			getch();
		}


		while( strcmp( XMLTag, "/map" ) != 0 )
		{
			fscanf( file, "<%[^> ]", XMLTag );
			if( debug )
			{
				printf( "	XMLTag= %s \n", XMLTag );
			}


			if( strcmp( XMLTag, "properties" ) == 0 )
			{
				fscanf( file, ">\n" );

				while( strcmp( XMLTag, "/properties" ) != 0 )
				{
					fscanf( file, "<%[^> ]", XMLTag );
					if( debug )
					{
						printf( "		XMLTag= %s \n", XMLTag );
						getch();
					}


					if( strcmp( XMLTag, "property" ) == 0 )
					{
						TMXProperty newProperty;
						fscanf( file, " name=\"%[^\"]\" type=\"%[^\"]\" value=\"%[^\"]\"/>\n", newProperty.name, newProperty.type, newProperty.stringValue );
						newTMXMap.properties.push_back( newProperty );
						if( debug )
						{
							printf( "			name 	= %s \n", newTMXMap.properties.back().name			);
							printf( "			type 	= %s \n", newTMXMap.properties.back().type 			);
							printf( "			value 	= %s \n", newTMXMap.properties.back().stringValue 	);
							getch();
						}
						
					}

					if(strcmp( XMLTag, "/properties" ) == 0 )
					{
						fscanf(file, ">\n");
					}
				}
			}
			if( strcmp(XMLTag, "tileset") == 0 )
			{
				TMXTileSet newTileSet;
				newTileSet.tileHeight 	= 0;
				newTileSet.tileWidth 	= 0;
				newTileSet.tileCount 	= 0;
				newTileSet.columns 		= 0;

				char whitespace = ' ';
				fscanf( file, "%c", &whitespace );
				printf( "whitespace = %c;", whitespace );
				
				while( whitespace != '>' )
				{
					//printf("test\n");
					char name[30];
					fscanf( file, "%[^=]=", name );

					printf("name= %s;", name );

					if( strcmp( name, "firstgid" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTileSet.firstGID );
						printf("firstgid= %i ", newTileSet.firstGID);
					}
					if( strcmp( name, "source" ) == 0 )
					{
						fscanf( file, "\"%[^\"]\"", newTileSet.name );
						printf("name= %s ", newTileSet.name);
					}
					if( strcmp( name, "tilewidth" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTileSet.tileHeight );
						printf("tilewidth= %i ", &newTileSet.tileHeight);
					}
					if( strcmp( name, "tileheight" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTileSet.tileWidth );
						printf("tileheight= %i ", &newTileSet.tileWidth);
					}
					if( strcmp( name, "tilecount" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTileSet.tileCount );
						printf("tilecount= %i ", &newTileSet.tileCount);
					}
					if( strcmp( name, "columns" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTileSet.columns );
						printf("columns= %i ", &newTileSet.columns);
					}
					if( whitespace == '/' )
					{
						printf("whitespace = / \n");
					}
					fscanf( file, "%c", &whitespace );
					if( debug )
					{
						//printf( "whitespace = %c;", whitespace );
						getch();
					}
				}

				//fscanf( file, " firstgid=\"%i\" name=\"%[^\"]\" tilewidth=\"%i\" tileheight=\"%i\" tilecount=\"%i\" columns=\"%i\">\n", &newTileSet.firstGID, newTileSet.name, &newTileSet.tileHeight, &newTileSet.tileWidth, &newTileSet.tileCount, &newTileSet.columns );
				//fscanf( file, " firstgid=\"%i\" source=\"%[^\"]\" />\n", &newTileSet.firstGID, newTileSet.name );
				
				newTileSet.tileSetID = -1;
				newTMXMap.tileSets.push_back(newTileSet);

				if(debug)
				{
					printf( "		firtGD 			= %i \n", newTMXMap.tileSets.back().firstGID 		);
					printf( "		name 			= %s \n", newTMXMap.tileSets.back().name 			);
					printf( "		tileWidth 		= %i \n", newTMXMap.tileSets.back().tileHeight 		);
					printf( "		tileHeight 		= %i \n", newTMXMap.tileSets.back().tileWidth 		);
					printf( "		tileCount 		= %i \n", newTMXMap.tileSets.back().tileCount 		);
					printf( "		columns 		= %i \n", newTMXMap.tileSets.back().columns 		);
					printf( "		source 			= %s \n", newTMXMap.tileSets.back().source 			);
					printf( "		sourceWidth 	= %i \n", newTMXMap.tileSets.back().sourceWidth 	);
					printf( "		sourceHeight 	= %i \n", newTMXMap.tileSets.back().sourceHeight 	);
					getch();
				}

				while( strcmp(XMLTag, "/tileset") != 0 )
				{
					fscanf( file, "<%[^> ]", XMLTag );
					if( debug )
					{
						printf( "		XMLTag= %s \n", XMLTag );
						getch();
					}

					if( strcmp( XMLTag, "image" ) == 0 )
					{
						fscanf( file, " source=\"%[^\"]\" width=\"%i\" height=\"%i\"/>\n", newTMXMap.tileSets.back().source, &newTMXMap.tileSets.back().sourceHeight, &newTMXMap.tileSets.back().sourceWidth );
					}

					if( strcmp( XMLTag, "/tileset" ) == 0 )
					{
						fscanf( file, ">\n" );
					}

					if( strcmp( XMLTag, "tile" ) == 0 )
					{
						TMXTile newTile;
						fscanf( file, " id=\"%i\">\n", &newTile.id );
						newTMXMap.tileSets.back().tiles.push_back( newTile );
						newTile.typeID = -1;
						if( debug )
						{
							printf( "			tileID= %i \n", newTile.id );
							//getch();
						}

						while( strcmp( XMLTag, "/tile" ) != 0 )
						{
							fscanf( file, "<%[^> ]", XMLTag );
							if( debug )
							{
								printf( "			XMLTag= %s \n", XMLTag );
								//getch();
							}

							if( strcmp( XMLTag, "/tile" ) == 0 )
							{
								fscanf( file, ">\n" );
							}

							if( strcmp( XMLTag, "properties" ) == 0 )
							{
								fscanf( file, ">\n" );

								while( strcmp( XMLTag, "/properties" ) != 0 )
								{
									fscanf( file, "<%[^> ]", XMLTag );
									if( debug )
									{
										printf( "				XMLTag= %s \n", XMLTag );
										//getch();
									}


									if( strcmp( XMLTag, "property" ) == 0 )
									{
										TMXProperty newProperty;
										fscanf( file, " name=\"%[^\"]\" type=\"%[^\"]\" value=\"%[^\"]\"/>\n", newProperty.name, newProperty.type, newProperty.stringValue );
										newTMXMap.tileSets.back().tiles.back().properties.push_back( newProperty );
										if(debug)
										{
											printf( "					name 	= %s \n", newTMXMap.tileSets.back().tiles.back().properties.back().name 		);
											printf( "					type 	= %s \n", newTMXMap.tileSets.back().tiles.back().properties.back().type 		);
											printf( "					value 	= %s \n", newTMXMap.tileSets.back().tiles.back().properties.back().stringValue 	);
											//getch();
										}
										if( strcmp(newProperty.name, "typeID") == 0 )
										{
											newTMXMap.tileSets.back().tiles.back().typeID = atoi(newProperty.stringValue);
										}
										
									}

									if( strcmp( XMLTag, "/properties" ) == 0 )
									{
										fscanf( file, ">\n" );
										//printf("jo");
									}
								}
							}
						}
					}


					if( strcmp( XMLTag, "properties" ) == 0 )
					{
						fscanf( file, ">\n" );

						while( strcmp( XMLTag, "/properties" ) != 0 )
						{
							fscanf( file, "<%[^> ]", XMLTag );
							if( debug )
							{
								printf( "		XMLTag= %s \n", XMLTag );
								getch();
							}


							if( strcmp( XMLTag, "property" ) == 0 )
							{
								TMXProperty newProperty;
								fscanf( file, " name=\"%[^\"]\" type=\"%[^\"]\" value=\"%[^\"]\"/>\n", newProperty.name, newProperty.type, newProperty.stringValue );
								newTMXMap.tileSets.back().properties.push_back( newProperty );
								if(debug)
								{
									printf( "			name 	= %s \n", newTMXMap.tileSets.back().properties.back().name 			);
									printf( "			type 	= %s \n", newTMXMap.tileSets.back().properties.back().type 			);
									printf( "			value 	= %s \n", newTMXMap.tileSets.back().properties.back().stringValue 	);
									getch();
								}
								if( strcmp(newProperty.name, "tileSetID") == 0 )
								{
									newTMXMap.tileSets.back().tileSetID = atoi(newProperty.stringValue);
								}
								
							}

							if( strcmp( XMLTag, "/properties" ) == 0 )
							{
								fscanf( file, ">\n" );
							}
						}
					}
				}
			}

			if( strcmp( XMLTag, "layer" ) == 0 )
			{
				TMXLayer newTMXLayer;
				//fscanf(file, " id=\"%i\" name=\"%[^\"]\" width=\"%i\" height=\"%i\">\n", &newTMXLayer.id, newTMXLayer.name, &newTMXLayer.width, &newTMXLayer.height);
				
				//dealing with visible, locked and offsets
				newTMXLayer.visible 	= true;
				newTMXLayer.locked 		= false;
				newTMXLayer.offsetX 	= 0;
				newTMXLayer.offsetY 	= 0;

				char whitespace = ' ';
				fscanf( file, "%c", &whitespace );
				while( whitespace != '>' )
				{
					char name[30];

					fscanf( file, "%[^=]=", name );
					if( strcmp( name, "id" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTMXLayer.id );
						//printf("id= %i ", newTMXLayer.id);
					}
					if( strcmp( name, "name" ) == 0 )
					{
						fscanf( file, "\"%[^\"]\"", newTMXLayer.name );
						//printf("name= %s ", newTMXLayer.name);
					}
					if( strcmp( name, "width" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTMXLayer.width );
						//printf("width= %i ", newTMXLayer.width);
					}
					if( strcmp( name, "height" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTMXLayer.height );
						//printf("height= %i ", newTMXLayer.height);
					}
					if( strcmp( name, "visible" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTMXLayer.visible );
						//printf("visible= %i ", newTMXLayer.visible);
					}
					if( strcmp( name, "locked" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTMXLayer.locked );
						//printf("locked= %i ", newTMXLayer.locked);
					}
					if( strcmp( name, "offsetx") == 0 )
					{
						fscanf( file, "\"%i\"", &newTMXLayer.offsetX );
						//printf("offsetx= %i ", newTMXLayer.offsetX);
					}
					if( strcmp( name, "offsety" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newTMXLayer.offsetY );
						//printf("offsety= %i ", newTMXLayer.offsetY);
					}
					fscanf( file, "%c", &whitespace );
					if( debug )
					{
						printf( "whitespace = %c;", whitespace );
						//getch();
					}
				}
				fscanf( file, "\n" );
				if( debug )
				{
					printf( "\n" );
				}

				newTMXMap.layers.push_back( newTMXLayer );
				if( debug )
				{
					printf( "		id 			= %i \n", newTMXMap.layers.back().id 		);
					printf( "		name		= %s \n", newTMXMap.layers.back().name 		);
					printf( "		Width 		= %i \n", newTMXMap.layers.back().width 	);
					printf( "		Height 		= %i \n", newTMXMap.layers.back().height 	);
					printf( "		visible		= %i \n", newTMXMap.layers.back().visible 	);
					printf( "		locked		= %i \n", newTMXMap.layers.back().locked 	);
					printf( "		offsetX		= %i \n", newTMXMap.layers.back().offsetX 	);
					printf( "		offsetY		= %i \n", newTMXMap.layers.back().offsetY 	);
					getch();
				}

				while( strcmp( XMLTag, "/layer" ) != 0 )
				{

					fscanf( file, "<%[^> ]", XMLTag );
					if( debug )
					{
						printf( "		XMLTag= %s \n", XMLTag );
						getch();
					}

					if( strcmp( XMLTag, "/layer" ) == 0 )
					{
						fscanf( file, ">\n" );
					}

					if( strcmp( XMLTag, "properties" ) == 0 )
					{
						fscanf(file, ">\n");

						while( strcmp( XMLTag, "/properties" ) != 0 )
						{
							fscanf( file, "<%[^> ]", XMLTag );
							if( debug )
							{
								printf( "			XMLTag= %s \n", XMLTag );
								getch();
							}


							if( strcmp( XMLTag, "property" ) == 0 )
							{
								TMXProperty newProperty;
								fscanf( file, " name=\"%[^\"]\" type=\"%[^\"]\" value=\"%[^\"]\"/>\n", newProperty.name, newProperty.type, newProperty.stringValue );
								newTMXMap.layers.back().properties.push_back(newProperty);
								if( debug )
								{
									printf( "				name 	= %s \n", newTMXMap.layers.back().properties.back().name 			);
									printf( "				type 	= %s \n", newTMXMap.layers.back().properties.back().type 			);
									printf( "				value 	= %s \n", newTMXMap.layers.back().properties.back().stringValue 	);
									getch();
								}
							}

							if(strcmp( XMLTag, "/properties" ) == 0 )
							{
								fscanf( file, ">\n" );
							}
						}
					}

					if( strcmp( XMLTag, "data" ) == 0 )
					{
						fscanf( file, " encoding=\"%[^\"]\">\n", newTMXLayer.dataEncoding );
						if( debug )
						{
							printf( "			encoding 	= %s \n", newTMXLayer.dataEncoding );
							getch();
						}

						newTMXMap.layers.back().data = ( int* )malloc( newTMXLayer.height * newTMXLayer.width * sizeof( int ) );
						for( unsigned int y = 0; y < newTMXLayer.height; y++ )
						{
							for( unsigned int x = 0; x < newTMXLayer.width; x++ )
							{
								fscanf( file, "%i,", &newTMXMap.layers.back().data[y * newTMXLayer.width + x] );
								//printf( "%i,", newTMXLayer.data[y * newTMXLayer.width + x] );
							}
							fscanf( file, "\n" );
						}

						if( debug )
						{
							for( unsigned int y = 0; y < newTMXLayer.height; y++ )
							{
								for( unsigned int x = 0; x < newTMXLayer.width; x++ )
								{
									printf( "%i,", newTMXMap.layers.back().data[y * newTMXLayer.width + x] );
								}
								printf( "\n" );
							}
						}

						fscanf( file, "</data>\n" );
					}
				}
			}

			if(strcmp( XMLTag, "objectgroup" ) == 0 )
			{
				TMXObjectGroup newObjectGroup;
				//fscanf( file, " id=\"%i\" name=\"%[^\"]\" width=\"%i\" height=\"%i\">\n", &newTMXLayer.id, newTMXLayer.name, &newTMXLayer.width, &newTMXLayer.height );
				
				//dealing with visible, locked and offsets
				newObjectGroup.visible = true;
				newObjectGroup.locked  = false;
				newObjectGroup.offsetX = 0;
				newObjectGroup.offsetY = 0;
				newObjectGroup.opacity = 1;

				char whitespace = ' ';
				fscanf( file, "%c", &whitespace );
				while( whitespace != '>' )
				{
					char name[30];

					fscanf( file, "%[^=]=", name );
					if( strcmp( name, "id" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newObjectGroup.id );
						//printf( "id= %i ", newObjectGroup.id );
					}
					if( strcmp( name, "name" ) == 0 )
					{
						fscanf( file, "\"%[^\"]\"", newObjectGroup.name );
						//printf( "name= %s ", newObjectGroup.name );
					}
					if( strcmp(name, "visible") == 0 )
					{
						fscanf( file, "\"%i\"", &newObjectGroup.visible );
						//printf( "visible= %i ", newObjectGroup.visible );
					}
					if( strcmp( name, "locked" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newObjectGroup.locked );
						//printf( "locked= %i ", newObjectGroup.locked );
					}
					if( strcmp( name, "offsetx" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newObjectGroup.offsetX );
						//printf( "offsetx= %i ", newObjectGroup.offsetX );
					}
					if( strcmp( name, "offsety" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newObjectGroup.offsetY );
						//printf( "offsety= %i ", newObjectGroup.offsetY );
					}
					fscanf( file, "%c", &whitespace );
					if( debug )
					{
						printf( "whitespace = %c;", whitespace );
						//getch();
					}
				}
				fscanf( file, "\n" );
				if( debug )
				{
					printf( "\n" );
				}

				newTMXMap.objectGroups.push_back( newObjectGroup );
				if( debug )
				{
					printf( "		id 			= %i \n", newTMXMap.objectGroups.back().id 		);
					printf( "		name		= %s \n", newTMXMap.objectGroups.back().name 	);
					printf( "		visible		= %i \n", newTMXMap.objectGroups.back().visible );
					printf( "		locked		= %i \n", newTMXMap.objectGroups.back().locked 	);
					printf( "		offsetX		= %i \n", newTMXMap.objectGroups.back().offsetX );
					printf( "		offsetY		= %i \n", newTMXMap.objectGroups.back().offsetY );
					getch();
				}

				while( strcmp( XMLTag, "/objectgroup" ) != 0 )
				{

					fscanf( file, "<%[^> ]", XMLTag );
					if( debug )
					{
						printf( "		XMLTag= %s \n", XMLTag );
						getch();
					}

					if( strcmp( XMLTag, "/objectgroup" ) == 0 )
					{
						fscanf( file, ">\n" );
					}

					if( strcmp( XMLTag, "properties" ) == 0 )
					{
						fscanf( file, ">\n" );

						while( strcmp( XMLTag, "/properties" ) != 0 )
						{
							fscanf( file, "<%[^> ]", XMLTag );
							if( debug )
							{
								printf( "			XMLTag= %s \n", XMLTag );
								getch();
							}


							if( strcmp( XMLTag, "property" ) == 0 )
							{
								TMXProperty newProperty;
								fscanf( file, " name=\"%[^\"]\" type=\"%[^\"]\" value=\"%[^\"]\"/>\n", newProperty.name, newProperty.type, newProperty.stringValue );
								newTMXMap.objectGroups.back().properties.push_back( newProperty );
								if( debug )
								{
									printf( "				name 	= %s \n", newTMXMap.objectGroups.back().properties.back().name	 		);
									printf( "				type 	= %s \n", newTMXMap.objectGroups.back().properties.back().type 			);
									printf( "				value 	= %s \n", newTMXMap.objectGroups.back().properties.back().stringValue 	);
									getch();
								}
								
							}

							if( strcmp( XMLTag, "/properties" ) == 0 )
							{
								fscanf( file, ">\n" );
							}
						}
					}

					//read objects
					if( strcmp( XMLTag, "object" ) == 0 )
					{
						TMXObject newObject;
						
						//dealing with visible, locked and offsets
						newObject.visible 	= true;
						newObject.width 	= 0;
						newObject.height 	= 0;
						newObject.rotation 	= 0;
						newObject.gid 		= 0;
						newObject.typeID 	= -1;
						strcpy(newObject.type, "point"); //a rect is also a point. just with aditional with and height


						char whitespace = ' ';
						fscanf( file, "%c", &whitespace );
						bool objectEnd = false; //ugly -.-
						while( whitespace != '>' )
						{
							char name[30];

							fscanf( file, "%[^=]=", name );
							if( strcmp( name, "id" ) == 0 )
							{
								fscanf( file, "\"%i\"", &newObject.id );
							}
							if( strcmp( name, "x" ) == 0 )
							{
								fscanf( file, "\"%f\"", &newObject.pos.x );
							}
							if( strcmp(name, "y" ) == 0 )
							{
								fscanf( file, "\"%f\"", &newObject.pos.y );
							}
							if( strcmp( name, "width" ) == 0 )
							{
								fscanf( file, "\"%i\"", &newObject.width );
							}
							if( strcmp( name, "height" ) == 0 )
							{
								fscanf( file, "\"%i\"", &newObject.height );
							}
							if( strcmp( name, "name" ) == 0 )
							{
								fscanf( file, "\"%[^\"]\"", newObject.name );
							}
							if( strcmp( name, "gid" ) == 0 )
							{
								fscanf( file, "\"%i\"", &newObject.gid );
							}
							if( strcmp( name, "rotation" ) == 0 )
							{
								fscanf( file, "\"%f\"", &newObject.rotation );
							}
							fscanf( file, "%c", &whitespace );
							if( whitespace == '/' )
							{
								fscanf( file, "%c", &whitespace );
								objectEnd = true;
							}
							if( debug )
							{
								printf( "whitespace = %c;", whitespace );
								//getch();
							}
						}
						fscanf( file, "\n" );
						if( debug )
						{
							printf( "\n" );
						}

						newTMXMap.objectGroups.back().objects.push_back( newObject );
						if(debug)
						{
							printf( "		id 			= %i \n", newTMXMap.objectGroups.back().objects.back().id 		);
							printf( "		X			= %f \n", newTMXMap.objectGroups.back().objects.back().pos.x 	);
							printf( "		Y			= %f \n", newTMXMap.objectGroups.back().objects.back().pos.y 	);
							printf( "		name		= %s \n", newTMXMap.objectGroups.back().objects.back().name 	);
							printf( "		visible		= %i \n", newTMXMap.objectGroups.back().objects.back().visible 	);
							printf( "		width		= %i \n", newTMXMap.objectGroups.back().objects.back().width 	);
							printf( "		height		= %i \n", newTMXMap.objectGroups.back().objects.back().height 	);
							getch();
						}

						while( strcmp( XMLTag, "/object" ) != 0 && !objectEnd )
						{
							fscanf( file, "<%[^> ]", XMLTag );
							if( debug )
							{
								printf( "			XMLTag= %s \n", XMLTag );
								getch();
							}

							if( strcmp( XMLTag, "/object" ) == 0 )
							{
								fscanf( file, ">\n" );
							}

							if( strcmp( XMLTag, "properties" ) == 0 )
							{
								fscanf( file, ">\n" );

								while( strcmp( XMLTag, "/properties" ) != 0 )
								{
									fscanf( file, "<%[^> ]", XMLTag );
									if( debug )
									{
										printf( "				XMLTag= %s \n", XMLTag );
										getch();
									}


									if( strcmp( XMLTag, "property" ) == 0 )
									{
										TMXProperty newProperty;
										fscanf( file, " name=\"%[^\"]\"", newProperty.name );

										char nextWord[30];
										fscanf( file, " %[^=]=", nextWord );
										if( debug )
											printf("nextWord=%s\n", nextWord );
										
										if( strcmp( nextWord, "value") == 0 )
										{
											if( debug )
												printf("in value section\n" );

											strcpy( newProperty.type, "string" );
											if( strcmp( newProperty.type, "string" ) == 0 )
											{
												fscanf( file, "\"%[^\"]\"/>\n", newProperty.stringValue );
											}

										}
										if(strcmp( nextWord, "type") == 0 )
										{
											fscanf( file, "\"%[^\"]\"", newProperty.type);

											if( strcmp( newProperty.type, "int" ) == 0 )
											{
												fscanf( file, " value=\"%i\"/>\n", &newProperty.intValue );
											}
											if( strcmp( newProperty.type, "float" ) == 0 )
											{
												fscanf( file, " value=\"%f\"/>\n", &newProperty.floatValue );
											}
											if( strcmp( newProperty.type, "bool" ) == 0 )
											{
												fscanf( file, " value=\"%i\"/>\n", &newProperty.boolValue );
											}
											if( strcmp( newProperty.type, "file" ) == 0 )
											{
												fscanf( file, " value=\"%[^\"]\"/>\n", newProperty.fileValue );
											}
											if( strcmp( newProperty.type, "string" ) == 0 )
											{
												fscanf( file, " value=\"%[^\"]\"/>\n", newProperty.stringValue );
											}
										}




										newTMXMap.objectGroups.back().objects.back().properties.push_back( newProperty );
										if( debug )
										{
											printf( "					name 			= %s \n", newTMXMap.objectGroups.back().objects.back().properties.back().name 		);
											printf( "					type 			= %s \n", newTMXMap.objectGroups.back().objects.back().properties.back().type 		);
											printf( "					intvalue 		= %i \n", newTMXMap.objectGroups.back().objects.back().properties.back().intValue 	);
											printf( "					floatvalue 		= %f \n", newTMXMap.objectGroups.back().objects.back().properties.back().floatValue );
											printf( "					boolvalue 		= %i \n", newTMXMap.objectGroups.back().objects.back().properties.back().boolValue 	);
											printf( "					filevalue 		= %s \n", newTMXMap.objectGroups.back().objects.back().properties.back().fileValue 	);
											printf( "					stringvalue 	= %s \n", newTMXMap.objectGroups.back().objects.back().properties.back().stringValue);
											
											//getch();
										}
										if( strcmp( newProperty.name, "typeID" ) == 0 )
										{
											//newTMXMap.objectGroups.back().objects.back().typeID = atoi( newProperty.stringValue );
											newTMXMap.objectGroups.back().objects.back().typeID = newProperty.intValue;
										}
										
									}

									if( strcmp( XMLTag, "/properties" ) == 0 )
									{
										fscanf(file, ">\n");
										//printf("jo");
									}
								}
							}

							if( strcmp( XMLTag, "ellipse/" ) == 0 )
							{
								strcpy( newObject.type, "ellipse" );
								fscanf( file, ">\n" );
							}

							if( strcmp( XMLTag, "point/" ) == 0 )
							{
								strcpy( newObject.type, "point" );
								fscanf( file, ">\n" );
							}


							//text (complicated to parse...)
						}
					}
				}
			}

			if( strcmp( XMLTag, "imagelayer" ) == 0 )
			{
				TMXImageLayer newImageLayer;
				//dealing with visible, locked and offsets
				newImageLayer.visible = true;
				newImageLayer.offsetX = 0;
				newImageLayer.offsetY = 0;
				newImageLayer.opacity = 1;



				char whitespace = ' ';
				bool objectEnd = false; //ugly -.-
				fscanf( file, "%c", &whitespace );
				while( whitespace != '>' )
				{
					char name[30];

					fscanf( file, "%[^=]=", name );
					if(strcmp( name, "id") == 0 )
					{
						fscanf( file, "\"%i\"", &newImageLayer.id );
						//printf( "id= %i ", newObjectGroup.id );
					}
					if( strcmp( name, "name" ) == 0 )
					{
						fscanf( file, "\"%[^\"]\"", newImageLayer.name );
						//printf( "name= %s ", newObjectGroup.name );
					}
					if( strcmp( name, "visible" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newImageLayer.visible );
						//printf( "visible= %i ", newObjectGroup.visible );
					}
					if( strcmp( name, "offsetx" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newImageLayer.offsetX );
						//printf( "offsetx= %i ", newObjectGroup.offsetX );
					}
					if( strcmp( name, "offsety" ) == 0 )
					{
						fscanf( file, "\"%i\"", &newImageLayer.offsetY );
						//printf( "offsety= %i ", newObjectGroup.offsetY );
					}
					if( strcmp( name, "opacity" ) == 0 )
					{
						fscanf( file, "\"%f\"", &newImageLayer.opacity );
						//printf( "offsety= %i ", newObjectGroup.offsetY );
					}
					fscanf( file, "%c", &whitespace );
					if( whitespace == '/' )
					{
						fscanf( file, "%c", &whitespace );
						objectEnd = true;
					}
					if( debug )
					{
						printf( "whitespace = %c;", whitespace );
						//getch();
					}
				}
				fscanf( file, "\n" );
				if( debug )
				{
					printf( "\n" );
				}

				newTMXMap.imageLayers.push_back( newImageLayer );
				if(debug)
				{
					printf( "		id 			= %i \n", newTMXMap.imageLayers.back().id 		);
					printf( "		name		= %s \n", newTMXMap.imageLayers.back().name 	);
					printf( "		visible		= %i \n", newTMXMap.imageLayers.back().visible 	);
					printf( "		offsetX		= %i \n", newTMXMap.imageLayers.back().offsetX 	);
					printf( "		offsetY		= %i \n", newTMXMap.imageLayers.back().offsetY 	);
					printf( "		opacity		= %f \n", newTMXMap.imageLayers.back().opacity 	);
					getch();
				}

				while( strcmp(XMLTag, "/imagelayer" ) != 0 && !objectEnd )
				{
					fscanf( file, "<%[^> ]", XMLTag );
					if( debug )
					{
						printf( "		XMLTag= %s \n", XMLTag );
						getch();
					}

					if( strcmp( XMLTag, "/imagelayer" ) == 0 )
					{
						fscanf(file, ">\n");
					}

					if( strcmp( XMLTag, "properties" ) == 0 )
					{
						fscanf( file, ">\n" );

						while( strcmp( XMLTag, "/properties" ) != 0 )
						{
							fscanf( file, "<%[^> ]", XMLTag );
							if( debug )
							{
								printf( "			XMLTag= %s \n", XMLTag );
								getch();
							}


							if( strcmp( XMLTag, "property" ) == 0 )
							{
								TMXProperty newProperty;
								fscanf( file, " name=\"%[^\"]\" type=\"%[^\"]\" value=\"%[^\"]\"/>\n", newProperty.name, newProperty.type, newProperty.stringValue );
								newTMXMap.imageLayers.back().properties.push_back(newProperty);
								if(debug)
								{
									printf( "				name 	= %s \n", newTMXMap.imageLayers.back().properties.back().name 		);
									printf( "				type 	= %s \n", newTMXMap.imageLayers.back().properties.back().type 		);
									printf( "				value 	= %s \n", newTMXMap.imageLayers.back().properties.back().stringValue);
									getch();
								}
								
							}

							if( strcmp( XMLTag, "/properties" ) == 0 )
							{
								fscanf( file, ">\n" );
							}
						}
					}

					if( strcmp( XMLTag, "image" ) == 0 )
					{
						TMXImage newImage;

						//char format[30];
						//char trans[30];
					
						fscanf( file, " source=\"%[^\"]\" width=\"%i\" height=\"%i\"/>\n", newImage.source, &newImage.width, &newImage.height );
					 	newTMXMap.imageLayers.back().image = newImage;
					 	if( debug )
						{
							printf( "				source 	= %s \n", newTMXMap.imageLayers.back().image.source 	);
							printf( "				width 	= %i \n", newTMXMap.imageLayers.back().image.width 		);
							printf( "				height 	= %i \n", newTMXMap.imageLayers.back().image.height 	);
							getch();
						}
					 	
					}
				}
			}		
		}
		fscanf( file, ">\n" );

		if( debug )
		{
			printf( "done reading tmx file!\n" );
			getch();
		}*/

		return newTMXMap;
	}
	TMXProperty GetProperty( vector<TMXProperty> properties, const char* name )
	{
		TMXProperty dummy;
		dummy.intValue = 0;
		strcpy(dummy.stringValue, "");
		dummy.boolValue = false;

		for( unsigned int i = 0; i < properties.size(); i ++ )
		{
			if( strcmp( properties[i].name, name ) == 0 )
			{
				return properties[i];
			}
		}

		return dummy;
	}
	int GetFirstGid( TMXMap* in, int tileSetID )
	{
		return in->tileSets[tileSetID].firstGID;
		//
	}
	int GetTypeID( TMXMap* in, int mapValue, int TMXTileSetIndex )
	{
		mapValue = mapValue - GetFirstGid( in, TMXTileSetIndex );

		for( unsigned int u = 0; u < in->tileSets[TMXTileSetIndex].tiles.size(); u++ )
		{
			if( in->tileSets[TMXTileSetIndex].tiles[u].id == mapValue )
			{
				return in->tileSets[TMXTileSetIndex].tiles[u].typeID;
			}
		}

		return -1;
	}
	int GetTMXTileSetIndex( TMXMap* in, int mapValue )
	{
		//gets the TileSetIndex in the TMX File

		//printf( " tilesets %i \n ", in->tileSets.size() );
		for(int i = (int)in->tileSets.size()-1; i >= 0; i-- )
		{
			//printf( "index= %i, gid=%i checking for=%i \n ", i, in->tileSets[i].firstGID, mapValue - in->tileSets[i].firstGID );
			//getch();
			if( mapValue - in->tileSets[i].firstGID >= 0 )
			{
				//printf( "found at %i checked for %i \n", in->tileSets[i].firstGID, mapValue - in->tileSets[i].firstGID  );
				return i;
			}
		}

		return -1;
	}
	int GetTileSetID( TMXMap* in, int TMXTileSetIndex )
	{
		return in->tileSets[TMXTileSetIndex].tileSetID;
		//
	}
	int GetTileID( TMXMap* in, int mapValue, int TMXTileSetIndex )
	{
		return mapValue - GetFirstGid(in, TMXTileSetIndex);
		//
	}
	//void CreateObjectsFromMap( TMXMap* in )
	//{
		/*unsigned int width, height;
		unsigned int tileWidth, tileHeight;
		vector<TMXTileSet> tileSets;
		vector<TMXLayer> layers;
		vector<TMXObjectGroup> objectGroups;*/

		/*for( unsigned int i = 0; i < in->layers.size(); i++ )
		{
			for( unsigned int y = 0; y < in->layers[i].height; y++ )
			{
				for( unsigned int x = 0; x < in->layers[i].width; x++ )
				{
					int mapValue = in->layers[i].data[y * in->layers[i].width + x];
					//printf( "mapValue = %i\n", mapValue );
					if( mapValue > 0 )
					{
						GameObject* newObject = NULL;

						
						//int tileSetID 	= GetTileSetID( in, mapValue );
						int tileSetIndexInTMX  	= GetTMXTileSetIndex( in, mapValue );
						int tileSetID 			= GetTileSetID( in, tileSetIndexInTMX );
						int typeID 				= GetTypeID( in, mapValue, tileSetIndexInTMX );
						int tileID 				= GetTileID( in, mapValue, tileSetIndexInTMX );
						int tileHeight 			= in->tileSets[tileSetIndexInTMX].tileHeight;
						int tileWidth 			= in->tileSets[tileSetIndexInTMX].tileWidth;
						
						Vector2D newPos;
						newPos.x 	= ( x * tileWidth ) + in->layers[i].offsetX;
						newPos.y 	= ( y * tileHeight ) + in->layers[i].offsetY;
						//newPos 		= newPos + offset;	//additional offset from paramteer list

						//printf("O %i:%i:%i mapValue=%i tileSetTMX=%i TMXSource=%s tileSetID=%i tileID=%i typeID=%i pos=%f:%f\n", i, y, x, mapValue, tileSetIndexInTMX, in->tileSets[tileSetIndexInTMX].source, tileSetID, tileID, typeID, newPos.x, newPos.y);

						if( typeID == TYPE_PLAYER )
						{
							newObject = new Player( this );
						}
						else if( typeID == TYPE_SOLID )
						{
							newObject = new Solid( this );
						}
						else if( typeID == TYPE_SOLID_TOP )
						{
							newObject = new SolidTop( this );
						}
						else if( typeID == TYPE_BACK_GROUND ) 
						{
							newObject = new BackGround( this );
						}
						else if( typeID == TYPE_BACK_GROUND_ANIMATION ) 
						{
							newObject = new BackGroundAnimation( this );
						}
						else if( typeID == TYPE_TRAP ) 
						{
							newObject = new Trap( this );
						}
						else if( typeID == TYPE_EXIT ) 
						{
							newObject = new Exit( this );
						}
						else if( typeID == TYPE_TREASURE ) 
						{
							newObject = new Treasure( this );
						}
						else if( typeID == TYPE_BATTERY ) 
						{
							newObject = new Battery( this );
						}
						else if( typeID == TYPE_SHIP_WREK ) 
						{
							newObject = new ShipWrek( this );
						}
						else if( typeID == TYPE_DOOR ) 
						{
							newObject = new Door( this );
						}
						else if( typeID == TYPE_KEY ) 
						{
							newObject = new Key( this );
						}
						else if( typeID == TYPE_SYNTH_STATION ) 
						{
							newObject = new SynthStation( this );
						}
						else
						{
							//printf("create!\n");
							if(tileID != -1)
							{
								newObject = new GameObject( this );
						
							}
						}
						if( newObject != NULL )
						{
							//newObject->SetTypeID	( typeID );
							newObject->SetPos		( newPos );
							newObject->SetDimensions( tileWidth, tileHeight );
							newObject->SetTileSetID	( tileSetID );
							newObject->SetTileIndex	( tileID );
							newObject->SetDrawOrder	( i );

							AddObject( newObject );
						}
						//getch();
					}
				}
			}
		}

		for( unsigned int i = 0; i < in->objectGroups.size(); i++ )
		{
			for( unsigned int u = 0; u < in->objectGroups[i].objects.size(); u++ )
			{
				TMXObject* object;
				object = &in->objectGroups[i].objects[u];

				if( object->typeID != -1 )
				{
					GameObject* newObject = NULL;

					Vector2D newPos = object->pos;
					newPos.x 	= newPos.x + in->layers[i].offsetX;
					newPos.y 	= newPos.y + in->layers[i].offsetY;
					//newPos 		= newPos + offset;	//additional offset from paramteer list
							
					if( object->typeID == TYPE_PLAYER ) //placeholder
					{
						//printf("create!\n");
						newObject = new Player( this );
						

					}

					if( object->typeID == TYPE_PLAYER_TOP_DOWN ) //placeholder
					{
						//printf("create!\n");
						newObject = new PlayerTopDown( this );
						

					}

					if( object->typeID == TYPE_CITY_OVERWORLD ) //placeholder
					{
						//printf("create!\n");
						newObject = new CityOverWorld( this );
						CityOverWorld* city;
						city = ( CityOverWorld* )newObject;

						city->SetLevelPath( GetProperty( object->properties, "levelPath" ).stringValue );
						city->SetTileIndex( GetProperty( object->properties, "tileIndex" ).intValue );
					}

					if( object->typeID == TYPE_CITY_OVERWORLD1X1 ) //placeholder
					{
						//printf("create!\n");
						newObject = new CityOverWorld1x1( this );
						CityOverWorld1x1* city;
						city = ( CityOverWorld1x1* )newObject;

						city->SetLevelPath( GetProperty( object->properties, "levelPath" ).stringValue );
						city->SetTileIndex( GetProperty( object->properties, "tileIndex" ).intValue );
					}

					if( newObject != NULL )
					{
						//newObject->SetTypeID	( object->typeID ); 		//get from property
						newObject->SetPos		( newPos );					//get from pos
						

						AddObject( newObject );
					}
				}
			}
		}

		FindLevelBoundaries();
	}*/
	void Quit(const char* message)
	{

		//Print Message
		printf( "Error: %s \n", message );
		printf( "Terminating Program" );

		//exit Program
		exit(EXIT_FAILURE);
	}
	//==========================================================
};

int main( int argc, char* argv[] )
{
	TMXConverter tmxConverter;
	TMXMap tmxMap;

	char* fileName = NULL;

	for( int i = 0; i < argc; i++ )
	{
		if( strcmp( argv[i], "-filename" ) == 0)
		{
			if( i + 1 <= argc )
			{
				fileName = argv[i+1];
			}
		}
	}

	tmxMap = tmxConverter.LoadTMXMap( fileName );

	return 0;
}