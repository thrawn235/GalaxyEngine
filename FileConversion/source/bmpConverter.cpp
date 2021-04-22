#include <iostream>
#include <filesystem>
#include <string>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "Vector2D.h"

bool debug = true;

//BMP Structs================================
struct BMPFileHEader
{
	char header[2];
	int32_t sizeInBytes;
	char reserved[4];
	int32_t pixelArrayOffset;
}__attribute__( ( packed ) );

struct BMPDIBHeader
{
	int32_t		  	size;
	int32_t 		width;
	int32_t			height;
	int16_t			numColorPlanes;
	int16_t			bitsPerPixel;
	int32_t 		compression;
	int32_t 		bitmapSize;
	int32_t 		horizontalResolution;
	int32_t 		verticalResolution;
	int32_t 		numColors;
	int32_t 		numImportantColors;
}__attribute__( ( packed ) );

struct BMP
{
	char 			source[30];
	BMPFileHEader 	fileHeader;
	BMPDIBHeader	DIBHeader;
	char 			extraBitMasks[16];
	unsigned char* 	colorTable;
	char* 			pixelArray;
};
//============================================

struct Sprite
{
	//MAGIC						//3
	uint16_t	id;				
	uint32_t 	width, height;	//4
	uint32_t	pixelFormat;	//4
	uint32_t	bitsPerPixel;	//2
	char* 		pixelData;
};
struct TileSet
{
	int 			id;
	int 			tileWidth, tileHeight;
	vector<Sprite*>	tiles;
};


Sprite* SDLLoadBMP( const char* filePath )
{
	cout<<"SDLLoadBMP..."<<endl;

	SDL_Surface* newSurface = SDL_LoadBMP( filePath );
	SDL_LockSurface( newSurface );


	Sprite* newSprite = new Sprite;
	newSprite->id = 0;
	cout<<"pixelFormat = "<<newSurface->format->format<<endl;
	if( newSurface->format->format == SDL_PIXELFORMAT_UNKNOWN )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_UNKNOWN"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_UNKNOWN;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_INDEX1LSB )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_INDEX1LSB"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_INDEX1LSB;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_INDEX1MSB )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_INDEX1MSB"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_INDEX1MSB;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_INDEX4LSB )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_INDEX4LSB"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_INDEX4LSB;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_INDEX4MSB )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_INDEX4MSB"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_INDEX4MSB;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_INDEX8 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_INDEX8"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_INDEX8;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGB332 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGB332"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGB332;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGB444 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGB444"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGB444;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGB555 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGB555"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGB555;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGR555 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGR555"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGR555;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ARGB4444 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ARGB4444"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ARGB4444;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGBA4444 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGBA4444"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGBA4444;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ABGR4444 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ABGR4444"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ABGR4444;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGRA4444 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGRA4444"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGRA4444;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ARGB1555 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ARGB1555"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ARGB1555;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGBA5551 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGBA5551"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGBA5551;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ABGR1555 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ABGR1555"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ABGR1555;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGRA5551 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGRA5551"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGRA5551;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGB565 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGB565"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGB565;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGR565 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGR565"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGR565;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGB24 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGB24"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGB24;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGR24 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGR24"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGR24;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGB888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGB888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGB888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGBX8888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGBX8888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGBX8888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGR888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGR888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGR888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGRX8888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGRX8888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGRX8888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ARGB8888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ARGB8888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ARGB8888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGBA8888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGBA8888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGBA8888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ABGR8888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ABGR8888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ABGR8888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGRA8888 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGRA8888"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGRA8888;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ARGB2101010 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ARGB2101010"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ARGB2101010;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_RGBA32 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_RGBA32"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_RGBA32;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ARGB32 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ARGB32"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ARGB32;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_BGRA32 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_BGRA32"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_BGRA32;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_ABGR32 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_ABGR32"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_ABGR32;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_YV12 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_YV12"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_YV12;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_IYUV )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_IYUV"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_IYUV;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_YUY2 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_YUY2"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_YUY2;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_UYVY )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_UYVY"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_UYVY;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_YVYU )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_YVYU"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_YVYU;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_NV12 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_NV12"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_NV12;
	}
	else if( newSurface->format->format == SDL_PIXELFORMAT_NV21 )
	{
		if( debug )
		{
			cout<<"pixelformat SDL_PIXELFORMAT_NV21"<<endl;
		}
		newSprite->pixelFormat = SDL_PIXELFORMAT_NV21;
	}
	

	newSprite->width = newSurface->w;
	newSprite->height = newSurface->h;
	cout<<"width = "<<newSprite->width<<"; height = "<<newSprite->height<<endl;

	int bytesPerPixel = newSurface->format->BitsPerPixel / 8;
	int pixelArraySize = newSprite->width * newSprite->height * bytesPerPixel;
	cout<<"BytesPerPixel = "<<newSurface->format->BitsPerPixel / 8<<"; ArraySize = "<<pixelArraySize<<endl;
	newSprite->bitsPerPixel = newSurface->format->BitsPerPixel;
	cout<<"bpp = "<<newSprite->bitsPerPixel<<endl;

	newSprite->pixelData = (char*)malloc( pixelArraySize );
	memcpy(newSprite->pixelData, (char*)newSurface->pixels, pixelArraySize );

	SDL_UnlockSurface( newSurface );
	SDL_FreeSurface( newSurface );

	return newSprite;
}



/*BMP LoadBMP( const char* filePath )
{
	FILE *file = fopen( filePath, "rb" );
	if( file == NULL )
	{
		printf( "Error Loading File!\n"  );
	}
	else
	{
		//file succesfully opend...

		BMP bmp;
		strcpy( bmp.source,filePath );
		//reading BMP header
		fread( &bmp.fileHeader, sizeof( bmp.fileHeader ), 1, file );

		bool debug = true;
		if( debug )
		{
			printf( "%c%c\n", bmp.fileHeader.header[0], bmp.fileHeader.header[1] );
		}
		if( bmp.fileHeader.header[0] != 'B' || bmp.fileHeader.header[1] != 'M' )
		{
			printf( "not a valid bmp file!" );
		}
		else
		{
			//valid bmp...
			if( debug )
			{
				printf( "filesize= %li\n", bmp.fileHeader.sizeInBytes );
				printf( "pixelArrayOffset= %li\n", bmp.fileHeader.pixelArrayOffset );
			}

			//read DIBHeader
			fread( &bmp.DIBHeader, sizeof( bmp.DIBHeader ), 1, file );
			if( debug )
			{
				printf( "sizeOfDIBHeader= %lu\n", bmp.DIBHeader.size );
				printf( "BitmapWidth= %li\n", bmp.DIBHeader.width );
				printf( "BitmapHeight= %li\n", bmp.DIBHeader.height );
				printf( "NumColorPlanes= %i\n", bmp.DIBHeader.numColorPlanes );
				printf( "bitsPerPixel= %i\n", bmp.DIBHeader.bitsPerPixel );
				printf( "compression= %lu\n", bmp.DIBHeader.compression );
				printf( "RawImageSize= %lu\n", bmp.DIBHeader.bitmapSize );
				printf( "horizontalResolution= %li\n", bmp.DIBHeader.horizontalResolution );
				printf( "verticalResolution= %li\n", bmp.DIBHeader.verticalResolution );
				printf( "numColors= %lu\n", bmp.DIBHeader.numColors );
				printf( "numImportantColors= %lu\n", bmp.DIBHeader.numImportantColors );
			}

			if( bmp.DIBHeader.size == 40 )
			{
				int reservedNumBytes = 40 - sizeof( bmp.DIBHeader );
				char extraBitMasks[reservedNumBytes];
				fread( extraBitMasks, reservedNumBytes, 1, file );
				if( debug )
				{
					printf( "reservedNumBytes= %i\n", reservedNumBytes );
				}
			}

			//read Color Table:
			bmp.colorTable = ( unsigned char* )malloc( bmp.DIBHeader.numColors * 4 );
			fread( bmp.colorTable, bmp.DIBHeader.numColors * 4, 1, file );

			if( debug )
			{
				int index = 0;
				for( int i = 0; i < bmp.DIBHeader.numColors; i++ )
				{
					printf( "R=%hhx; G=%hhx; B=%hhx; A=%hhx \n", bmp.colorTable[index+0], bmp.colorTable[index+1], bmp.colorTable[index+2], bmp.colorTable[index+3] );
					index = index + 4;
				}
			}

			//read pixelArray:
			bmp.pixelArray = ( char* )malloc( bmp.DIBHeader.bitmapSize );
			//position file pointer correctly
			fseek( file, bmp.fileHeader.pixelArrayOffset, SEEK_SET );
			fread( bmp.pixelArray, bmp.DIBHeader.bitmapSize, 1, file );

			if( 0 )
			{
				for( int y = 0; y < bmp.DIBHeader.height; y++ )
				{
					for( int x = 0; x < bmp.DIBHeader.width; x++ )
					{
						printf( "%hhu;", bmp.pixelArray[y * bmp.DIBHeader.width + x] );
						
					}
					printf( "\n" );
				}
			}
		}
		fclose( file );
		return bmp;
	}
}*/
Sprite* CropSprite( Sprite* in, int newID, Vector2D pos, int width, int height )
{
	if( debug )
	{
		cout<<"CropSprite..."<<endl;
	}	

	if( pos.x >= 0 && pos.y >= 0 && pos.x < in->width && pos.y < in->height )
	{
		Sprite* newSprite = new Sprite;
		newSprite->id = newID;
		newSprite->width = width;
		newSprite->height = height;
		newSprite->pixelFormat = in->pixelFormat;
		newSprite->bitsPerPixel = in->bitsPerPixel;
		if( pos.x + width > in->width )
		{
			newSprite->width = in->width - pos.x;
		}
		if( pos.y + height > in->height )
		{
			newSprite->height = in->height - pos.y;
		}

		int bytesPerPixel = (in->bitsPerPixel / 8);
		newSprite->pixelData = ( char* )malloc( width*height*sizeof( char )*bytesPerPixel );
		cout<<"bytesPerPixel = "<<bytesPerPixel<<" allocating "<<width*height*sizeof( char )*bytesPerPixel<<" bytes"<<endl;
		
		width = width * bytesPerPixel;
		pos.x = pos.x * bytesPerPixel;
		for( int y = 0; y < height; y++ )
		{
			/*for( int x = 0; x < width; x++ )
			{
				newSprite->pixelData[y * width + x] = in->pixelData[( ( int )pos.y + y ) * in->width + ( ( int )pos.x + x )];
			}*/
			int targetOffset = y * width;
			int sourceOffset = ((pos.y + y) * (in->width * bytesPerPixel)) + pos.x;
			memcpy( newSprite->pixelData + targetOffset , in->pixelData + sourceOffset, width);
			cout<<"copying "<<width<<" bytes from "<<sourceOffset<<"("<<sourceOffset/bytesPerPixel<<") to "<<targetOffset<<"("<<targetOffset / bytesPerPixel<<")"<<endl;
		}

		return newSprite;
	}
	return NULL;
}
TileSet* NewEmptyTileSet( int newID, int tileWidth, int tileHeight ) //just dont
{
	TileSet* newTileSet = new TileSet;
	newTileSet->id = newID;
	newTileSet->tileWidth = tileWidth; //just a guess. not reliable
	newTileSet->tileHeight = tileHeight; //just a guess. not reliable

	return newTileSet;
}
TileSet* ExtractTileSet( int newID, Sprite* in, Vector2D startPos, int tileWidth, int tileHeight)
{
	TileSet* newTileSet = new TileSet;
	newTileSet->id = newID;
	newTileSet->tileWidth = tileWidth;
	newTileSet->tileHeight = tileHeight;
	//strcpy( newTileSet->source, in->source );
	cout<<"spritewidth = "<<in->width<<endl;
	cout<<"spriteheight = "<<in->height<<endl;
	int numTliesHorizontal = in->width / tileWidth;
	int numTilesVertical = in->height / tileHeight;

	printf("\nTileSet TileWidth = %i\n", newTileSet->tileWidth);
	printf("TileSet TileHeight = %i\n", newTileSet->tileHeight);
	//printf("TileSet source = %s", newTileSet->tileWidth);
	printf("TileSet numTliesHorizontal = %i\n", numTliesHorizontal);
	printf("TileSet numTilesVertical = %i\n", numTilesVertical);



	for( int y = 0; y < numTilesVertical; y++ )
	{
		for( int x = 0; x < numTliesHorizontal; x++ )
		{
			int tileIndex = y * numTliesHorizontal + x;
			Vector2D tilePosOffset = Vector2D( x*tileWidth, y*tileHeight );
			newTileSet->tiles.push_back( CropSprite( in, tileIndex, startPos + tilePosOffset, tileWidth, tileHeight ) );
		}
	}

	return newTileSet;
}
/*Sprite* BMPToSprite( BMP* in, int id )
{
	Sprite* newSprite = new Sprite;
	newSprite->id = id;
	newSprite->width = in->DIBHeader.width;
	newSprite->height = in->DIBHeader.height;
	newSprite->pixelData = ( char* )malloc( in->DIBHeader.bitmapSize );
	strcpy( newSprite->source, in->source );
	
	//bmps are stored upside down!!
	//going to correct it for sprites
	//rather slow, but thats ok in that case
	int destY = in->DIBHeader.height;
	for( int y = 0; y < in->DIBHeader.height; y++ )
	{
		destY--;
		for( int x = 0; x < in->DIBHeader.width; x++ )
		{
			newSprite->pixelData[destY * newSprite->width + x] = in->pixelArray[y * in->DIBHeader.width + x];
		}
	}

	return newSprite;
}
void FreeBMP( BMP* in )
{
	free( in->pixelArray );
	free( in->colorTable );
}*/



void WriteSprite(const char* fileName, Sprite* out)
{
	FILE *file = fopen( fileName, "wb+" );
	char magic[3] = {'S','P','R'};
	fwrite(magic, 1, 3, file);
	fwrite(&out->width, 1, sizeof(uint32_t), file);
	fwrite(&out->height, 1, sizeof(uint32_t), file);
	fwrite(&out->pixelFormat, 1, sizeof(uint32_t), file);
	fwrite(&out->bitsPerPixel, 1, sizeof(uint32_t), file);
	int bytesPerPixel = out->bitsPerPixel / 8;
	fwrite(out->pixelData, 1, out->width * out->height * bytesPerPixel, file);
	cout<<"width = "<<out->width<<" height = "<<out->height<<" bpp = "<<bytesPerPixel<<endl;
	cout<<"wrote "<<out->width * out->height * bytesPerPixel<<" bytes"<<endl;

	fclose( file );
	return;
}

void JustWriteSprite( Sprite* out, FILE* file )
{
	char magic[3] = {'S','P','R'};
	fwrite(magic, 1, 3, file);
	fwrite(&out->width, 1, sizeof(uint32_t), file);
	fwrite(&out->height, 1, sizeof(uint32_t), file);
	fwrite(&out->pixelFormat, 1, sizeof(uint32_t), file);
	fwrite(&out->bitsPerPixel, 1, sizeof(uint32_t), file);
	int bytesPerPixel = out->bitsPerPixel / 8;
	fwrite(out->pixelData, 1, out->width * out->height * bytesPerPixel, file);
	cout<<"wrote "<<out->width * out->height * bytesPerPixel<<" bytes"<<endl;
	
	return;
}



int main( int argc, char* argv[] )
{
	char* fileName = NULL;
	int hSize = 0;
	int vSize = 0;
	bool anim = 0;
	bool collection = 0;

	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-filename") == 0)
		{
			if(i+1 <= argc)
			{
				fileName = argv[i+1];
			}
		}
		if(strcmp(argv[i], "-size") == 0)
		{
			if(i+1 <= argc)
			{
				hSize = atoi(argv[i+1]);
				vSize = atoi(argv[i+1]);
			}

		}

		if(strcmp(argv[i], "-hSize") == 0)
		{
			if(i+1 <= argc)
			{
				hSize = atoi(argv[i+1]);
			}

		}

		if(strcmp(argv[i], "-vSize") == 0)
		{
			if(i+1 <= argc)
			{
				vSize = atoi(argv[i+1]);
			}

		}

		if(strcmp(argv[i], "-anim") == 0)
		{
			if(i+1 <= argc)
			{
				anim = atoi(argv[i+1]);
			}

		}

		if(strcmp(argv[i], "-collection") == 0)
		{
			if(i+1 <= argc)
			{
				collection = atoi(argv[i+1]);
			}

		}
	}

	cout<<"hSize= "<<hSize<<" vSize= "<<vSize<<endl;

	if(fileName == NULL)
	{
		printf("please provide a file name!\n");
		printf("with -filname!\n");
		return 0;
	}


	//BMP in = LoadBMP(fileName);
	Sprite* inSprite = new Sprite;
	inSprite = SDLLoadBMP( fileName );

	printf("Filename: %s\n", fileName);
	char* withoutExtension = strtok(fileName, ".");
	printf("just filename: %s\n", withoutExtension);
	char oldName[100];
	strcpy(oldName, fileName);

	if( hSize == 0 )
	{
		cout<<"Sprite..."<<endl;
		WriteSprite( strcat(withoutExtension,".nspr"), inSprite );
	}
	else
	{
		if( anim )
		{
			cout<<"animation..."<<endl;
			TileSet* inSet = new TileSet;
			
			inSet = ExtractTileSet(0, inSprite, Vector2D(0,0), hSize, vSize);

			string name, number, extension;
			name = withoutExtension;
			extension = ".nanim";
			string outName = name + number + extension;
			FILE *file = fopen( outName.c_str(), "wb+" );

			//write number of animation frames
			char magic[3] = {'A','N','I'};
			fwrite( magic, 1, 3, file );
			uint32_t numFrames = inSet->tiles.size();
			fwrite( &numFrames, 1, sizeof(uint32_t), file );

			for( unsigned int i = 0; i < inSet->tiles.size(); i++ )
			{
				
				JustWriteSprite( inSet->tiles[i], file );
			}

			fclose( file );
		}
		else if( collection )
		{
			cout<<"collection..."<<endl;
			TileSet* inSet = new TileSet;
			
			inSet = ExtractTileSet(0, inSprite, Vector2D(0,0), hSize, vSize);

			string name, number, extension;
			name = withoutExtension;
			extension = ".ncol";
			string outName = name + number + extension;
			FILE *file = fopen( outName.c_str(), "wb+" );

			//write number of animation frames
			char magic[3] = {'C','O','L'};
			fwrite( magic, 1, 3, file );
			uint32_t numFrames = inSet->tiles.size();
			fwrite( &numFrames, 1, sizeof(uint32_t), file );
			uint32_t size = ( ( inSet->tileWidth + inSet->tileHeight ) * ( inSet->tiles[0]->bitsPerPixel / 8 ) + 3 + 4 * sizeof( uint32_t ) );
			fwrite( &size, 1, sizeof(uint32_t), file );

			for( unsigned int i = 0; i < inSet->tiles.size(); i++ )
			{
				
				JustWriteSprite( inSet->tiles[i], file );
			}

			fclose( file );
		}
		else
		{
			cout<<"Tileset..."<<endl;
			TileSet* inSet = new TileSet;
			
			inSet = ExtractTileSet(0, inSprite, Vector2D(0,0), hSize, vSize);

			for( unsigned int i = 0; i < inSet->tiles.size(); i++ )
			{
				string name, number, extension;
				name = withoutExtension;
				number = to_string(i);
				extension = ".nspr";
				string outName = name + number + extension;
				WriteSprite( outName.c_str(), inSet->tiles[i] );
			}
		}
	}
}