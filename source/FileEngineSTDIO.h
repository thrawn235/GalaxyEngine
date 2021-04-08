//====================================
// FileEngineSTDIO.h
// handles File Access
// STDIO Implementation
//====================================

//========== include guard ===========
#ifndef FILE_ENGINE_STDIO
#define FILE_ENGINE_STDIO
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
#include <stdio.h>
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


class FileEngineSTDIO : public FileEngine
{
protected:
    GameEngine* engine;

public:
    //---------- Constructor / Destructor ------------
                    FileEngineSTDIO     ( GameEngine* engine );
                    ~FileEngineSTDIO    ();

    void            Update              ();        //runs in every game loop

    unsigned int    Open                ( string filePath );
    void            Close               ( unsigned int fileID );
    char*           ReadWholeFile       ( unsigned int fileID );
    char*           Read                ( unsigned int fileID );
    char*           Read                ( unsigned int fileID, unsigned int start, unsigned long length );
    void            Write               ( char* data, unsigned long length );
    void            Write               ( char* data, unsigned long start, unsigned long length );

    void            SetFilePos          ( unsigned int fileID, unsigned long pos );
    void            Rewind              ( unsigned int fileID );
    void            SetFilePosEnd       ( unsigned int fileID );
    void            ChangeFilePos       ( unsigned int fileID, unsigned long delta );
};

#endif