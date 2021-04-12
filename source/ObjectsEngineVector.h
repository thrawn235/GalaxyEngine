//====================================
// ObjectsEngine.h
// handles all game objects
// this is the most essential part of the engine
// game objects can ask engine->objects to get objectpointers
// based on certain criteria, distance to a point or everything in a box etc
// standard vector implementation
//====================================

//========== include guard ===========
#ifndef OBJECTS_ENGINE_VECTOR
#define OBJECTS_ENGINE_VECTOR
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


class ObjectsEngineVector : public ObjectsEngine
{
protected:
    GameEngine*         engine;

    vector<Object*>     objects;
    vector<Object*>     deletedObjects;

    unsigned long int   highestUID;

public:
                        ObjectsEngineVector         ( GameEngine* engine );
                        ~ObjectsEngineVector        ();

    void                SetHighestUID               ( unsigned long int UID );
    unsigned long int   GetHighestUID               ();
    unsigned long int   GetHighestUIDAndInc         ();

    //--------------------------- add Objects -----------------------------
    void                AddObject                   ( Object* object );

    //------------------------ getting objects ----------------------------
    vector<Object*>     GetAllObjects               ();
    vector<Object*>     GetAllObjectsExcept         ( Object* object );
    vector<Object*>     GetAllObjectsExcept         ( vector<Object*> objects );
    Object*             GetObjectByID               ( unsigned long uid );

    //------------------------ deleting objects ---------------------------
    //(delete = move objects to delete list)
    void                DeleteAllObjects            ();
    void                DeleteAllObjectsExcept      ( Object* object );
    void                DeleteAllObjectsExcept      ( vector<Object*> objects );
    void                DeleteAllObjects            ( bool includePersistent );
    void                DeleteAllObjectsExcept      ( Object* object, bool includePersistent );
    void                DeleteAllObjectsExcept      ( vector<Object*> objects, bool includePersistent );
    void                DeleteObject                ( unsigned long uid );
    void                DeleteObject                ( Object* object );
    void                DeleteObjects               ( vector<unsigned long> uids );
    void                DeleteObjects               ( vector<Object*> objects );
    void                ClearAllDeletedObjects      ();
    void                ClearAllDeletedObjects      ( bool includePersistent );

    //------------------------ purging objects ----------------------------
    //(purge = delete objects immediatly. might lead to broken pointers)
    void                PurgeAllObjects             ();
    void                PurgeAllObjectsExcept       ( Object* object );
    void                PurgeAllObjectsExcept       ( vector<Object*> objects );
    void                PurgeAllObjects             ( bool includePersistent );
    void                PurgeAllObjectsExcept       ( Object* object, bool includePersistent );
    void                PurgeAllObjectsExcept       ( vector<Object*> objects, bool includePersistent );
    void                PurgeObject                 ( unsigned long uid );
    void                PurgeObject                 ( Object* object );
    void                PurgeObjects                ( vector<unsigned long> uids );
    void                PurgeObjects                ( vector<Object*> objects );

    //--------------------- store/restore objects -------------------------
    //(store = move to background list to be reused later)
    // int              CreateStore                 ();
    // void             DeleteStore                 ( int storeID );
    // void             StoreAllObjects             ();
    // void             StoreAllObjectsExcept       ( Object* object, int storeID );
    // void             StoreAllObjectsExcept       ( vector<Object*> objects, int storeID );
    // void             StoreAllObjects             ( bool includePersistent, int storeID );
    // void             StoreAllObjectsExcept       ( Object* object, bool includePersistent, int storeID );
    // void             StoreAllObjectsExcept       ( vector<Object*> objects, bool includePersistent, int storeID );
    // void             StoreObject                 ( unsigned long uid ,int storeID );
    // void             StoreObject                 ( Object* object, int storeID );
    // void             StoreObjects                ( vector<unsigned long> uids, int storeID );
    // void             StoreObjects                ( vector<Object*> objects, int storeID );
    // void             RestoreAllObjects           ();
    // void             RestoreAllObjectsExcept     ( Object* object, int storeID );
    // void             RestoreAllObjectsExcept     ( vector<Object*> objects, int storeID );
    // void             RestoreAllObjects           ( bool includePersistent, int storeID );
    // void             RestoreAllObjectsExcept     ( Object* object, bool includePersistent, int storeID );
    // void             RestoreAllObjectsExcept     ( vector<Object*> objects, bool includePersistent, int storeID );
    // void             RestoreObject               ( unsigned long uid ,int storeID );
    // void             RestoreObject               ( Object* object, int storeID );
    // void             RestoreObjects              ( vector<unsigned long> uids, int storeID );
    // void             RestoreObjects              ( vector<Object*> objects, int storeID );
};

#endif