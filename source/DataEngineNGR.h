//====================================
// DataEngineNGR.h
// The data engine grabs data from memory or from file
// and provides pointers to the end user
// This Implementation accceses .ngr files (see NGRCreator)
//====================================

//========== include guard ===========
#ifndef DATA_ENGINE_NGR
#define DATA_ENGINE_NGR
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "DataEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

#define TYPE_UNK 0
#define TYPE_PAL 1
#define TYPE_SPR 2
#define TYPE_ANI 3
#define TYPE_COL 4
#define TYPE_STR 5


struct NGRHeader
{
	//fileheader
	char 		ident[3] 	= { 'N', 'G', 'R' };
	uint16_t	numItems 	= 0;
	uint32_t	offsetTOC	= 0;
}__attribute__((__packed__));

struct TOCEntry
{
	uint32_t 	id;
	uint32_t	offset;
	uint32_t	size;
	uint32_t	type;
	char		name[24];
}__attribute__((__packed__));;

class DataBlock
{
public:
	unsigned int 	id;
	char* 			data;
};

class DataEngineNGR : public DataEngine
{
protected:
	GameEngine*			engine;
	
	vector<int> 		files;
	vector<DataBlock> 	dataBlocks;

public:
            DataEngineNGR       ( GameEngine* engine );
            ~DataEngineNGR  	();

    void    Update          	();

    void 	LoadArchiveFile 	( string filePath );

    void*   GetData         	( unsigned long id );
    void    FreeData        	( unsigned long id );

    //--------------------- diagnostics ----------------------
};

#endif