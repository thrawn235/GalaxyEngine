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

class FileHandle
{
public:
    unsigned int    ID;
    FILE*           filePointer;
};

class FileEngineSTDIO : public FileEngine
{
protected:
    GameEngine*         engine;

    int                 highestID;
    vector<FileHandle>  files;

public:
    //---------- Constructor / Destructor ------------
                    FileEngineSTDIO     ( GameEngine* engine );
                    ~FileEngineSTDIO    ();

    void            Update              ();        //runs in every game loop

    unsigned int    Open                ( string filePath );
    void            Close               ( unsigned int fileID );
    void            CloseAll            ();
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