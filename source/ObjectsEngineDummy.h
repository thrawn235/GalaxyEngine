//====================================
// ObjectsEngine.h
// handles all game objects
// this is the most essential part of the engine
// game objects can ask engine->objects to get objectpointers
// based on certain criteria, distance to a point or everything in a box etc
// dummy implementation
//====================================

//========== include guard ===========
#ifndef OBJECTS_ENGINE_DUMMY
#define OBJECTS_ENGINE_DUMMY
//====================================

//========== stdlib includes =========
#include <string>
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Vector2D.h"
#include "ObjectsEngine.h"
//====================================

//======= forward declarations =======
class GameEngine;
//====================================

//============= defines ==============
//====================================


class ObjectsEngineDummy : public ObjectsEngine
{
protected:
    GameEngine*     engine;

public:
                        ObjectsEngineDummy                              ( GameEngine* engine );
                        ~ObjectsEngineDummy                             ();

    void                SetHighestUID                                   ( unsigned long int UID );
    unsigned long int   GetHighestUID                                   ();
    unsigned long int   GetHighestUIDAndInc                             ();

    //--------------------------- add Objects -----------------------------
    void                AddObject                                       ( Object* object );

    //------------------------ getting objects ----------------------------
    vector<Object*>     GetAllObjects                                   ();
    vector<Object*>     GetAllGridObjects                               ();
    vector<Object*>     GetAllAgentObjects                              ();
    vector<Object*>     GetAllObjectsExcept                             ( Object* object );
    vector<Object*>     GetAllObjectsExcept                             ( vector<Object*> objects );

    vector<Object*>     GetAllAgentObjectsExcept                        ( Object* object );
    vector<Object*>     GetAllAgentObjectsExcept                        ( vector<Object*> objects );
    vector<Object*>     GetAllGridObjectsExcept                         ( Object* object );
    vector<Object*>     GetAllGridObjectsExcept                         ( vector<Object*> objects );

    Object*             GetObjectByID                                   ( unsigned long uid );

    unsigned int        GetNumObjects                                   ();
    unsigned int        GetNumAgentObjects                              ();
    unsigned int        GetNumGridItems                                 ();
    unsigned int        GetNumGrids                                     ();

    //------------------------ deleting objects ---------------------------
    //(delete = move objects to delete list)
    void                DeleteAllObjects                                ();
    void                DeleteAllObjectsExcept                          ( Object* object );
    void                DeleteAllObjectsExcept                          ( vector<Object*> objects );
    void                DeleteAllObjects                                ( bool includePersistent );
    void                DeleteAllObjectsExcept                          ( Object* object, bool includePersistent );
    void                DeleteAllObjectsExcept                          ( vector<Object*> objects, bool includePersistent );

    void                DeleteAllGridObjects                            ();
    void                DeleteAllGridObjectsExcept                      ( Object* object );
    void                DeleteAllGridObjectsExcept                      ( vector<Object*> objects );
    void                DeleteAllGridObjects                            ( bool includePersistent );
    void                DeleteAllGridObjectsExcept                      ( Object* object, bool includePersistent );
    void                DeleteAllGridObjectsExcept                      ( vector<Object*> objects, bool includePersistent );

    void                DeleteAllAgentObjects                           ();
    void                DeleteAllAgentObjectsExcept                     ( Object* object );
    void                DeleteAllAgentObjectsExcept                     ( vector<Object*> objects );
    void                DeleteAllAgentObjects                           ( bool includePersistent );
    void                DeleteAllAgentObjectsExcept                     ( Object* object, bool includePersistent );
    void                DeleteAllAgentObjectsExcept                     ( vector<Object*> objects, bool includePersistent );

    void                DeleteObject                                    ( unsigned long uid );
    void                DeleteObject                                    ( Object* object );
    void                DeleteObjects                                   ( vector<unsigned long> uids );
    void                DeleteObjects                                   ( vector<Object*> objects );
    
    void                ClearAllDeletedObjects                          ();
    void                ClearAllDeletedObjects                          ( bool includePersistent );

    //------------------------ purging objects ----------------------------
    //(purge = delete objects immediatly. might lead to broken pointers)
    void                PurgeAllObjects                                 ();
    void                PurgeAllObjectsExcept                           ( Object* object );
    void                PurgeAllObjectsExcept                           ( vector<Object*> objects );
    void                PurgeAllObjects                                 ( bool includePersistent );
    void                PurgeAllObjectsExcept                           ( Object* object, bool includePersistent );
    void                PurgeAllObjectsExcept                           ( vector<Object*> objects, bool includePersistent );

    void                PurgeAllGridObjects                             ();
    void                PurgeAllGridObjectsExcept                       ( Object* object );
    void                PurgeAllGridObjectsExcept                       ( vector<Object*> objects );
    void                PurgeAllGridObjects                             ( bool includePersistent );
    void                PurgeAllGridObjectsExcept                       ( Object* object, bool includePersistent );
    void                PurgeAllGridObjectsExcept                       ( vector<Object*> objects, bool includePersistent );

    void                PurgeAllAgentObjects                            ();
    void                PurgeAllAgentObjectsExcept                      ( Object* object );
    void                PurgeAllAgentObjectsExcept                      ( vector<Object*> objects );
    void                PurgeAllAgentObjects                            ( bool includePersistent );
    void                PurgeAllAgentObjectsExcept                      ( Object* object, bool includePersistent );
    void                PurgeAllAgentObjectsExcept                      ( vector<Object*> objects, bool includePersistent );

    void                PurgeObject                                     ( unsigned long uid );
    void                PurgeObject                                     ( Object* object );
    void                PurgeObjects                                    ( vector<unsigned long> uids );
    void                PurgeObjects                                    ( vector<Object*> objects );

    //--------------------- store/restore objects -------------------------
    //(store = move to background list to be reused later)
    // int              CreateStore                                     ();
    // void             DeleteStore                                     ( int storeID );
    // void             StoreAllObjects                                 ();
    // void             StoreAllObjectsExcept                           ( Object* object, int storeID );
    // void             StoreAllObjectsExcept                           ( vector<Object*> objects, int storeID );
    // void             StoreAllObjects                                 ( bool includePersistent, int storeID );
    // void             StoreAllObjectsExcept                           ( Object* object, bool includePersistent, int storeID );
    // void             StoreAllObjectsExcept                           ( vector<Object*> objects, bool includePersistent, int storeID );
    // void             StoreObject                                     ( unsigned long uid ,int storeID );
    // void             StoreObject                                     ( Object* object, int storeID );
    // void             StoreObjects                                    ( vector<unsigned long> uids, int storeID );
    // void             StoreObjects                                    ( vector<Object*> objects, int storeID );
    // void             RestoreAllObjects                               ();
    // void             RestoreAllObjectsExcept                         ( Object* object, int storeID );
    // void             RestoreAllObjectsExcept                         ( vector<Object*> objects, int storeID );
    // void             RestoreAllObjects                               ( bool includePersistent, int storeID );
    // void             RestoreAllObjectsExcept                         ( Object* object, bool includePersistent, int storeID );
    // void             RestoreAllObjectsExcept                         ( vector<Object*> objects, bool includePersistent, int storeID );
    // void             RestoreObject                                   ( unsigned long uid ,int storeID );
    // void             RestoreObject                                   ( Object* object, int storeID );
    // void             RestoreObjects                                  ( vector<unsigned long> uids, int storeID );
    // void             RestoreObjects                                  ( vector<Object*> objects, int storeID );

    //--------------------------- Grid -----------------------------------
    unsigned int        LoadMap                                         ( unsigned int id ); 
    unsigned int        CreateGrid                                      ( unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, unsigned int offsetX, unsigned int offsetY );
    Grid*               GetGrid                                         ( unsigned int id );
    vector<Grid*>       GetAllGrids                                     ();
    void                PurgeGrid                                       ( unsigned int id );
    void                PurgeAllGrids                                   ();

    void                UpdateAllObjects                                ();
    void                ClientIndependendUpdateAllObjects               ();
    void                ClientSideUpdateAllObjects                      ( bool waitingForUpdate );
    void                PredictAllObjects                               ( float tickRate );
    void                ClientSideAndPredictAndIndependentAllObjects    ( bool waitingForUpdate, float tickRate );
    void                RenderAllObjects                                ();
};

#endif