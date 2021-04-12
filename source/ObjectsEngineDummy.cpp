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
Object* ObjectsEngineDummy::GetObjectByID( unsigned long uid )
{
	return NULL;
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
