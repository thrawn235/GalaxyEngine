//====================================
// FileEngine.h
// handles File Access
// should hardly be neccesary outside of the DataEngine
//====================================

//========== include guard ===========
#ifndef FILE_ENGINE
#define FILE_ENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <string>
using namespace std;
//====================================

//========= galaxy includes ==========
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
#define FILE_TYPE_DUMMY    0
#define FILE_TYPE_STDIO    1
//====================================


class FileEngine
{
protected:
    GameEngine* engine;

public:
    //---------- Constructor / Destructor ------------
                            FileEngine      ( GameEngine* engine )                                                          {};
    virtual                 ~FileEngine     ()                                                                              {};

    virtual void            Update          ()                                                                              = 0;        //runs in every game loop

    virtual unsigned int    Open            ( string filePath )                                                             = 0;
    virtual void            Close           ( unsigned int fileID )                                                         = 0;
    virtual char*           ReadWholeFile   ( unsigned int fileID )                                                         = 0;
    virtual char*           Read            ( unsigned int fileID, unsigned long length )                                   = 0;
    virtual char*           Read            ( unsigned int fileID, unsigned int start, unsigned long length )               = 0;
    virtual void            Write           ( unsigned int fileID, char* data, unsigned long length )                       = 0;
    virtual void            Write           ( unsigned int fileID, char* data, unsigned long start, unsigned long length )  = 0;

    virtual void            SetFilePos      ( unsigned int fileID, unsigned long pos )                                      = 0;
    virtual void            Rewind          ( unsigned int fileID )                                                         = 0;
    virtual void            SetFilePosEnd   ( unsigned int fileID )                                                         = 0;
    virtual void            ChangeFilePos   ( unsigned int fileID, unsigned long delta )                                    = 0;
};

#endif