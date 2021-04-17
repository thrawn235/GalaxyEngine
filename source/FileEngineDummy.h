//====================================
// FileEngineDummy.h
// handles File Access
// Dummy Implementation
//====================================

//========== include guard ===========
#ifndef FILE_ENGINE_DUMMY
#define FILE_ENGINE_DUMMY
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <string>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "FileEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
//====================================


class FileEngineDummy : public FileEngine
{
protected:
    GameEngine* engine;

public:
    //---------- Constructor / Destructor ------------
                    FileEngineDummy     ( GameEngine* engine );
                    ~FileEngineDummy    ();

    void            Update              ();        //runs in every game loop

    unsigned int    Open                ( string filePath );
    void            Close               ( unsigned int fileID );
    void            ReadWholeFile       ( unsigned int fileID, char* buffer );
    void            Read                ( unsigned int fileID, char* buffer, unsigned long length );
    void            Read                ( unsigned int fileID, char* buffer, unsigned int start, unsigned long length );
    void            Write               ( unsigned int fileID, char* data, unsigned long length );
    void            Write               ( unsigned int fileID, char* data, unsigned long start, unsigned long length );

    void            SetFilePos          ( unsigned int fileID, unsigned long pos );
    unsigned long   GetFilePos          ( unsigned int fileID );
    unsigned long   GetFileSize         ( unsigned int fileID );
    void            Rewind              ( unsigned int fileID );
    void            SetFilePosEnd       ( unsigned int fileID );
    void            ChangeFilePos       ( unsigned int fileID, unsigned long delta );
};

#endif