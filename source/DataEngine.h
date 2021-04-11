//====================================
// DataEngine.h
// The data engine grabs data from memory or from file
// and provides pointers to the end user
// it uses the file engine (FileEngine.h) to access the local filesystem
//====================================

//========== include guard ===========
#ifndef DATA_ENGINE
#define DATA_ENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
#define DATA_TYPE_DUMMY     0
#define DATA_TYPE_NGR       1
//====================================


class DataEngine
{
protected:

public:
                        DataEngine      ( GameEngine* engine )  {};
    virtual             ~DataEngine     ()                      {};

    virtual     void    Update          ()                      = 0;

    virtual 	void 	LoadArchiveFile ( string filePath )		= 0;

    virtual     void*   GetData         ( unsigned long id )    = 0;
    virtual     void    FreeData        ( unsigned long id )    = 0;

    //--------------------- diagnostics ----------------------
};

#endif