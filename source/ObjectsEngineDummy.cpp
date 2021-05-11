//ObjectsEngineDummy.cpp

#include "ObjectsEngineDummy.h"
#include "GameEngine.h"

ObjectsEngineDummy::ObjectsEngineDummy( GameEngine* engine ) : ObjectsEngine( engine )
{

}
ObjectsEngineDummy::~ObjectsEngineDummy()
{

}
void ObjectsEngineDummy::SetHighestUID( unsigned long int UID )
{

}
unsigned long int ObjectsEngineDummy::GetHighestUID()
{
    return 0;
}
unsigned long int ObjectsEngineDummy::GetHighestUIDAndInc()
{
    return 0;
}
void ObjectsEngineDummy::AddObject( Object* object )
{

}
vector<Object*> ObjectsEngineDummy::GetAllObjects()
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineDummy::GetAllGridObjects()
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineDummy::GetAllAgentObjects()
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineDummy::GetAllObjectsExcept( Object* object )
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineDummy::GetAllObjectsExcept( vector<Object*> objects )
{
    vector<Object*> out;
    return out;
}

vector<Object*> ObjectsEngineDummy::GetAllGridObjectsExcept( Object* object )
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineDummy::GetAllGridObjectsExcept( vector<Object*> objects )
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineDummy::GetAllAgentObjectsExcept( Object* object )
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineDummy::GetAllAgentObjectsExcept( vector<Object*> objects )
{
    vector<Object*> out;
    return out;
}

Object* ObjectsEngineDummy::GetObjectByID( unsigned long uid )
{
	return NULL;
}
unsigned int ObjectsEngineDummy::GetNumObjects()
{
    return 0;
}
unsigned int ObjectsEngineDummy::GetNumAgentObjects()
{
    return 0;
}
unsigned int ObjectsEngineDummy::GetNumGridItems()
{
    return 0;
}
unsigned int ObjectsEngineDummy::GetNumGrids()
{
    return 0;
}
void ObjectsEngineDummy::DeleteAllObjects()
{

}
void ObjectsEngineDummy::DeleteAllObjectsExcept( Object* object )
{

}
void ObjectsEngineDummy::DeleteAllObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineDummy::DeleteAllObjects( bool includePersistent )
{

}
void ObjectsEngineDummy::DeleteAllObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineDummy::DeleteAllObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}

void ObjectsEngineDummy::DeleteAllGridObjects()
{

}
void ObjectsEngineDummy::DeleteAllGridObjectsExcept( Object* object )
{

}
void ObjectsEngineDummy::DeleteAllGridObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineDummy::DeleteAllGridObjects( bool includePersistent )
{

}
void ObjectsEngineDummy::DeleteAllGridObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineDummy::DeleteAllGridObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}

void ObjectsEngineDummy::DeleteAllAgentObjects()
{

}
void ObjectsEngineDummy::DeleteAllAgentObjectsExcept( Object* object )
{

}
void ObjectsEngineDummy::DeleteAllAgentObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineDummy::DeleteAllAgentObjects( bool includePersistent )
{

}
void ObjectsEngineDummy::DeleteAllAgentObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineDummy::DeleteAllAgentObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}


void ObjectsEngineDummy::DeleteObject( unsigned long uid )
{

}
void ObjectsEngineDummy::DeleteObject( Object* object )
{

}
void ObjectsEngineDummy::DeleteObjects( vector<unsigned long> uids )
{

}
void ObjectsEngineDummy::DeleteObjects( vector<Object*> objects )
{

}
void ObjectsEngineDummy::ClearAllDeletedObjects()
{

}
void ObjectsEngineDummy::ClearAllDeletedObjects( bool includePersistent )
{

}

void ObjectsEngineDummy::PurgeAllObjects()
{

}
void ObjectsEngineDummy::PurgeAllObjectsExcept( Object* object )
{

}
void ObjectsEngineDummy::PurgeAllObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineDummy::PurgeAllObjects( bool includePersistent )
{

}
void ObjectsEngineDummy::PurgeAllObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineDummy::PurgeAllObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}

void ObjectsEngineDummy::PurgeAllGridObjects()
{

}
void ObjectsEngineDummy::PurgeAllGridObjectsExcept( Object* object )
{

}
void ObjectsEngineDummy::PurgeAllGridObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineDummy::PurgeAllGridObjects( bool includePersistent )
{

}
void ObjectsEngineDummy::PurgeAllGridObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineDummy::PurgeAllGridObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}

void ObjectsEngineDummy::PurgeAllAgentObjects()
{

}
void ObjectsEngineDummy::PurgeAllAgentObjectsExcept( Object* object )
{

}
void ObjectsEngineDummy::PurgeAllAgentObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineDummy::PurgeAllAgentObjects( bool includePersistent )
{

}
void ObjectsEngineDummy::PurgeAllAgentObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineDummy::PurgeAllAgentObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}

void ObjectsEngineDummy::PurgeObject( unsigned long uid )
{

}
void ObjectsEngineDummy::PurgeObject( Object* object )
{

}
void ObjectsEngineDummy::PurgeObjects( vector<unsigned long> uids )
{

}
void ObjectsEngineDummy::PurgeObjects( vector<Object*> objects )
{

}
// int ObjectsEngineDummy::CreateStore()
// void ObjectsEngineDummy::DeleteStore( int storeID )
// void ObjectsEngineDummy::StoreAllObjects()
// void ObjectsEngineDummy::StoreAllObjectsExcept( Object* object, int storeID )
// void ObjectsEngineDummy::StoreAllObjectsExcept( vector<Object*> objects, int storeID )
// void ObjectsEngineDummy::StoreAllObjects( bool includePersistent, int storeID )
// void ObjectsEngineDummy::StoreAllObjectsExcept( Object* object, bool includePersistent, int storeID )
// void ObjectsEngineDummy::StoreAllObjectsExcept( vector<Object*> objects, bool includePersistent, int storeID )
// void ObjectsEngineDummy::StoreObject( unsigned long uid ,int storeID )
// void ObjectsEngineDummy::StoreObject( Object* object, int storeID )
// void ObjectsEngineDummy::StoreObjects( vector<unsigned long> uids, int storeID )
// void ObjectsEngineDummy::StoreObjects( vector<Object*> objects, int storeID )
// void ObjectsEngineDummy::RestoreAllObjects()
// void ObjectsEngineDummy::RestoreAllObjectsExcept( Object* object, int storeID )
// void ObjectsEngineDummy::RestoreAllObjectsExcept( vector<Object*> objects, int storeID )
// void ObjectsEngineDummy::RestoreAllObjects( bool includePersistent, int storeID )
// void ObjectsEngineDummy::RestoreAllObjectsExcept( Object* object, bool includePersistent, int storeID )
// void ObjectsEngineDummy::RestoreAllObjectsExcept( vector<Object*> objects, bool includePersistent, int storeID )
// void ObjectsEngineDummy::RestoreObject( unsigned long uid ,int storeID )
// void ObjectsEngineDummy::RestoreObject( Object* object, int storeID )
// void ObjectsEngineDummy::RestoreObjects( vector<unsigned long> uids, int storeID )
// void ObjectsEngineDummy::RestoreObjects( vector<Object*> objects, int storeID )

unsigned int ObjectsEngineDummy::LoadMap( unsigned int id )
{
	return 0;
}
unsigned int ObjectsEngineDummy::CreateGrid( unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, unsigned int offsetX, unsigned int offsetY )
{
	return 0;
}
Grid* ObjectsEngineDummy::GetGrid( unsigned int id )
{
	return NULL;
}
vector<Grid*> ObjectsEngineDummy::GetAllGrids()
{
	vector<Grid*> grids;
	return grids;
}
void ObjectsEngineDummy::PurgeGrid( unsigned int id )
{

}
void ObjectsEngineDummy::PurgeAllGrids()
{

}

void ObjectsEngineDummy::UpdateAllObjects()
{

}                       
void ObjectsEngineDummy::ClientIndependendUpdateAllObjects()
{

}                       
void ObjectsEngineDummy::ClientSideUpdateAllObjects( bool waitingForUpdate )
{

}
void ObjectsEngineDummy::PredictAllObjects( float tickRate )
{

}                       
void ObjectsEngineDummy::ClientSideAndPredictAndIndependentAllObjects( bool waitingForUpdate, float tickRate )
{

}                     
void ObjectsEngineDummy::RenderAllObjects()
{

}