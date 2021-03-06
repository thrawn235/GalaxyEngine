//====================================
// ObjectsEngine.h
// handles all game objects
// this is the most essential part of the engine
// game objects can ask engine->objects to get objectpointers
// based on certain criteria, distance to a point or everything in a box etc
//====================================

//========== include guard ===========
#ifndef OBJECTS_ENGINE
#define OBJECTS_ENGINE
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Vector2D.h"
#include "GameEngine.h"
#include "Object.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
#define OBJECTS_TYPE_DUMMY     0
#define OBJECTS_TYPE_VECTOR    1
//====================================

struct Grid
{
    unsigned int                id;
    unsigned int                width;
    unsigned int                height;
    unsigned int                tileWidth;
    unsigned int                tileHeight;
    unsigned int                offsetX;
    unsigned int                offsetY;
    Object**                    objects = NULL;
};


class ObjectsEngine
{
protected:

public:
                                    ObjectsEngine                                   ( GameEngine* engine )                                                                                                                      {};
    virtual                         ~ObjectsEngine                                  ()                                                                                                                                          {};

    virtual     void                SetHighestUID                                   ( unsigned long int UID )                                                                                                                   = 0;
    virtual     unsigned long int   GetHighestUID                                   ()                                                                                                                                          = 0;
    virtual     unsigned long int   GetHighestUIDAndInc                             ()                                                                                                                                          = 0;                                                                  

    //--------------------------- add Objects -----------------------------
    virtual     void                AddObject                                       ( Object* object )                                                                                                                          = 0;
    //virtual     void                AddObjectToGrid             ( Object* object, unsigned int x, unsigned int y )                                                                                          = 0;

    //------------------------ getting objects ----------------------------
    virtual     vector<Object*>     GetAllObjects                                   ()                                                                                                                                          = 0;
    virtual     vector<Object*>     GetAllGridObjects                               ()                                                                                                                                          = 0;      
    virtual     vector<Object*>     GetAllAgentObjects                              ()                                                                                                                                          = 0;
    virtual     vector<Object*>     GetAllObjectsExcept                             ( Object* object )                                                                                                                          = 0;
    virtual     vector<Object*>     GetAllObjectsExcept                             ( vector<Object*> objects )                                                                                                                 = 0;

    virtual     vector<Object*>     GetAllAgentObjectsExcept                        ( Object* object )                                                                                                                          = 0;
    virtual     vector<Object*>     GetAllAgentObjectsExcept                        ( vector<Object*> objects )                                                                                                                 = 0;
    virtual     vector<Object*>     GetAllGridObjectsExcept                         ( Object* object )                                                                                                                          = 0;
    virtual     vector<Object*>     GetAllGridObjectsExcept                         ( vector<Object*> objects )                                                                                                                 = 0;

    virtual     Object*             GetObjectByID                                   ( unsigned long uid )                                                                                                                       = 0;

    virtual     unsigned int        GetNumObjects                                   ()                                                                                                                                          = 0;
    virtual     unsigned int        GetNumAgentObjects                              ()                                                                                                                                          = 0;
    virtual     unsigned int        GetNumGridItems                                 ()                                                                                                                                          = 0;
    virtual     unsigned int        GetNumGrids                                     ()                                                                                                                                          = 0;

    //------------------------ deleting objects ---------------------------
    //(delete = move objects to delete list)
    virtual     void                DeleteAllObjects                                ()                                                                                                                                          = 0;
    virtual     void                DeleteAllObjectsExcept                          ( Object* object )                                                                                                                          = 0;
    virtual     void                DeleteAllObjectsExcept                          ( vector<Object*> objects )                                                                                                                 = 0;
    virtual     void                DeleteAllObjects                                ( bool includePersistent )                                                                                                                  = 0;
    virtual     void                DeleteAllObjectsExcept                          ( Object* object, bool includePersistent )                                                                                                  = 0;
    virtual     void                DeleteAllObjectsExcept                          ( vector<Object*> objects, bool includePersistent )                                                                                         = 0;

    virtual     void                DeleteAllGridObjects                            ()                                                                                                                                          = 0;
    virtual     void                DeleteAllGridObjectsExcept                      ( Object* object )                                                                                                                          = 0;
    virtual     void                DeleteAllGridObjectsExcept                      ( vector<Object*> objects )                                                                                                                 = 0;
    virtual     void                DeleteAllGridObjects                            ( bool includePersistent )                                                                                                                  = 0;
    virtual     void                DeleteAllGridObjectsExcept                      ( Object* object, bool includePersistent )                                                                                                  = 0;
    virtual     void                DeleteAllGridObjectsExcept                      ( vector<Object*> objects, bool includePersistent )                                                                                         = 0;

    virtual     void                DeleteAllAgentObjects                           ()                                                                                                                                          = 0;
    virtual     void                DeleteAllAgentObjectsExcept                     ( Object* object )                                                                                                                          = 0;
    virtual     void                DeleteAllAgentObjectsExcept                     ( vector<Object*> objects )                                                                                                                 = 0;
    virtual     void                DeleteAllAgentObjects                           ( bool includePersistent )                                                                                                                  = 0;
    virtual     void                DeleteAllAgentObjectsExcept                     ( Object* object, bool includePersistent )                                                                                                  = 0;
    virtual     void                DeleteAllAgentObjectsExcept                     ( vector<Object*> objects, bool includePersistent )                                                                                         = 0;

    virtual     void                DeleteObject                                    ( unsigned long uid )                                                                                                                       = 0;
    virtual     void                DeleteObject                                    ( Object* object )                                                                                                                          = 0;
    virtual     void                DeleteObjects                                   ( vector<unsigned long> uids )                                                                                                              = 0;
    virtual     void                DeleteObjects                                   ( vector<Object*> objects )                                                                                                                 = 0;
    
    virtual     void                ClearAllDeletedObjects                          ()                                                                                                                                          = 0;
    virtual     void                ClearAllDeletedObjects                          ( bool includePersistent )                                                                                                                  = 0;

    //------------------------ purging objects ----------------------------
    //(purge = delete objects immediatly. might lead to broken pointers)
    virtual     void                PurgeAllObjects                                 ()                                                                                                                                          = 0;
    virtual     void                PurgeAllObjectsExcept                           ( Object* object )                                                                                                                          = 0;
    virtual     void                PurgeAllObjectsExcept                           ( vector<Object*> objects )                                                                                                                 = 0;
    virtual     void                PurgeAllObjects                                 ( bool includePersistent )                                                                                                                  = 0;
    virtual     void                PurgeAllObjectsExcept                           ( Object* object, bool includePersistent )                                                                                                  = 0;
    virtual     void                PurgeAllObjectsExcept                           ( vector<Object*> objects, bool includePersistent )                                                                                         = 0;

    virtual     void                PurgeAllGridObjects                             ()                                                                                                                                          = 0;
    virtual     void                PurgeAllGridObjectsExcept                       ( Object* object )                                                                                                                          = 0;
    virtual     void                PurgeAllGridObjectsExcept                       ( vector<Object*> objects )                                                                                                                 = 0;
    virtual     void                PurgeAllGridObjects                             ( bool includePersistent )                                                                                                                  = 0;
    virtual     void                PurgeAllGridObjectsExcept                       ( Object* object, bool includePersistent )                                                                                                  = 0;
    virtual     void                PurgeAllGridObjectsExcept                       ( vector<Object*> objects, bool includePersistent )                                                                                         = 0;

    virtual     void                PurgeAllAgentObjects                            ()                                                                                                                                          = 0;
    virtual     void                PurgeAllAgentObjectsExcept                      ( Object* object )                                                                                                                          = 0;
    virtual     void                PurgeAllAgentObjectsExcept                      ( vector<Object*> objects )                                                                                                                 = 0;
    virtual     void                PurgeAllAgentObjects                            ( bool includePersistent )                                                                                                                  = 0;
    virtual     void                PurgeAllAgentObjectsExcept                      ( Object* object, bool includePersistent )                                                                                                  = 0;
    virtual     void                PurgeAllAgentObjectsExcept                      ( vector<Object*> objects, bool includePersistent )                                                                                         = 0;

    virtual     void                PurgeObject                                     ( unsigned long uid )                                                                                                                       = 0;
    virtual     void                PurgeObject                                     ( Object* object )                                                                                                                          = 0;
    virtual     void                PurgeObjects                                    ( vector<unsigned long> uids )                                                                                                              = 0;
    virtual     void                PurgeObjects                                    ( vector<Object*> objects )                                                                                                                 = 0;

    //--------------------- store/restore objects -------------------------
    //(store = move to background list to be reused later)
    // virtual     int              CreateStore                                     ()                                                                                                                                          = 0;
    // virtual     void             DeleteStore                                     ( int storeID )                                                                                                                             = 0;
    // virtual     void             StoreAllObjects                                 ()                                                                                                                                          = 0;
    // virtual     void             StoreAllObjectsExcept                           ( Object* object, int storeID )                                                                                                             = 0;
    // virtual     void             StoreAllObjectsExcept                           ( vector<Object*> objects, int storeID )                                                                                                    = 0;
    // virtual     void             StoreAllObjects                                 ( bool includePersistent, int storeID )                                                                                                     = 0;
    // virtual     void             StoreAllObjectsExcept                           ( Object* object, bool includePersistent, int storeID )                                                                                     = 0;
    // virtual     void             StoreAllObjectsExcept                           ( vector<Object*> objects, bool includePersistent, int storeID )                                                                            = 0;
    // virtual     void             StoreObject                                     ( unsigned long uid ,int storeID )                                                                                                          = 0;
    // virtual     void             StoreObject                                     ( Object* object, int storeID )                                                                                                             = 0;
    // virtual     void             StoreObjects                                    ( vector<unsigned long> uids, int storeID )                                                                                                 = 0;
    // virtual     void             StoreObjects                                    ( vector<Object*> objects, int storeID )                                                                                                    = 0;
    // virtual     void             RestoreAllObjects                               ()                                                                                                                                          = 0;
    // virtual     void             RestoreAllObjectsExcept                         ( Object* object, int storeID )                                                                                                             = 0;
    // virtual     void             RestoreAllObjectsExcept                         ( vector<Object*> objects, int storeID )                                                                                                    = 0;
    // virtual     void             RestoreAllObjects                               ( bool includePersistent, int storeID )                                                                                                     = 0;
    // virtual     void             RestoreAllObjectsExcept                         ( Object* object, bool includePersistent, int storeID )                                                                                     = 0;
    // virtual     void             RestoreAllObjectsExcept                         ( vector<Object*> objects, bool includePersistent, int storeID )                                                                            = 0;
    // virtual     void             RestoreObject                                   ( unsigned long uid ,int storeID )                                                                                                          = 0;
    // virtual     void             RestoreObject                                   ( Object* object, int storeID )                                                                                                             = 0;
    // virtual     void             RestoreObjects                                  ( vector<unsigned long> uids, int storeID )                                                                                                 = 0;
    // virtual     void             RestoreObjects                                  ( vector<Object*> objects, int storeID )                                                                                                    = 0;

    //--------------------------- Grid -----------------------------------
    virtual     unsigned int        LoadMap                                         ( unsigned int id )                                                                                                                         = 0;
    virtual     unsigned int        CreateGrid                                      ( unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, unsigned int offsetX, unsigned int offsetY )    = 0;
    virtual     Grid*               GetGrid                                         ( unsigned int id )                                                                                                                         = 0;
    virtual     vector<Grid*>       GetAllGrids                                     ()                                                                                                                                          = 0;
    virtual     void                PurgeGrid                                       ( unsigned int id )                                                                                                                         = 0;
    virtual     void                PurgeAllGrids                                   ()                                                                                                                                          = 0;

    //------------------------ Calling Methods --------------------------
    virtual     void                UpdateAllObjects                                ()                                                                                                                                          = 0;
    virtual     void                ClientIndependendUpdateAllObjects               ()                                                                                                                                          = 0;
    virtual     void                ClientSideUpdateAllObjects                      ( bool waitingForUpdate )                                                                                                                   = 0;
    virtual     void                PredictAllObjects                               ( float tickRate )                                                                                                                          = 0;
    virtual     void                ClientSideAndPredictAndIndependentAllObjects    ( bool waitingForUpdate, float tickRate )                                                                                                   = 0;
    virtual     void                RenderAllObjects                                ()                                                                                                                                          = 0;
};

#endif