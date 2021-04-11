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


class DataEngineNGR : public DataEngine
{
protected:

public:
            DataEngineNGR       ( GameEngine* engine );
            ~DataEngineNGR  	();

    void    Update          	();

    void*   GetData         	( unsigned long id );
    void    FreeData        	( unsigned long id );

    //--------------------- diagnostics ----------------------
};

#endif