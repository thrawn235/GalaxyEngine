//====================================
// DataEngineDummy.h
// The data engine grabs data from memory or from file
// and provides pointers to the end user
// Dummy Implementation
//====================================

//========== include guard ===========
#ifndef DATA_ENGINE_DUMMY
#define DATA_ENGINE_DUMMY
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


class DataEngineDummy : public DataEngine
{
protected:

public:
            DataEngineDummy     ( GameEngine* engine );
            ~DataEngineDummy 	();

    void    Update          	();

    void 	LoadArchiveFile 	( string filePath );

    void*   GetData         	( unsigned long id );
    void    FreeData        	( unsigned long id );

    //--------------------- diagnostics ----------------------
};

#endif