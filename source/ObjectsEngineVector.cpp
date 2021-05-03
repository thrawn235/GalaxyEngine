//ObjectsEngineVector.cpp

#include "ObjectsEngineVector.h"
#include "GameEngine.h"

ObjectsEngineVector::ObjectsEngineVector( GameEngine* engine ) : ObjectsEngine( engine )
{
	this->engine = engine;
}
ObjectsEngineVector::~ObjectsEngineVector()
{
    engine->debug->PrintString( "Purge all objects... \n" );
    PurgeAllObjects( true );
    engine->debug->PrintString( "Clear deleted objects... \n" );
    ClearAllDeletedObjects();
}
void ObjectsEngineVector::SetHighestUID( unsigned long int UID )
{
	highestUID = UID;
	//
}
unsigned long int ObjectsEngineVector::GetHighestUID()
{
    //
    return highestUID;
}
unsigned long int ObjectsEngineVector::GetHighestUIDAndInc()
{
    highestUID++;
    return highestUID - 1;
}
void ObjectsEngineVector::AddObject( Object* object )
{
	objects.push_back( object );
    engine->debug->PrintString( "Add object, i have %i\n", objects.size() );
}
vector<Object*> ObjectsEngineVector::GetAllObjects()
{
    engine->debug->PrintString( "Get objects, i have %i\n", objects.size() );
    return objects;
}
vector<Object*> ObjectsEngineVector::GetAllObjectsExcept( Object* object )
{
    vector<Object*> out;
    return out;
}
vector<Object*> ObjectsEngineVector::GetAllObjectsExcept( vector<Object*> objects )
{
    vector<Object*> out;
    return out;
}
Object* ObjectsEngineVector::GetObjectByID( unsigned long uid )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetUID() == uid )
        {
            return objects[i];
        }
    }
    return NULL;
}
void ObjectsEngineVector::DeleteAllObjects()
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void ObjectsEngineVector::DeleteAllObjectsExcept( Object* object )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() )
        {
            if( objects[i] != object )
            {
                deletedObjects.push_back( objects[i] );
                objects.erase( objects.begin() + i );
                i--;
            }   
        }
    }
}
void ObjectsEngineVector::DeleteAllObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineVector::DeleteAllObjects( bool includePersistent )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void ObjectsEngineVector::DeleteAllObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineVector::DeleteAllObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}
void ObjectsEngineVector::DeleteObject( unsigned long uid )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetUID() == uid )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void ObjectsEngineVector::DeleteObject( Object* object )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i] == object )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void ObjectsEngineVector::DeleteObjects( vector<unsigned long> uids )
{
	for( unsigned int i = 0; i < uids.size(); i++ )
    {
        for( unsigned int u = 0; u < objects.size(); u++ )
        {
            if( objects[u]->GetUID() == uids[i] )
            {
                deletedObjects.push_back( objects[i] );
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
void ObjectsEngineVector::DeleteObjects( vector<Object*> objects )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        for( unsigned int u = 0; u < this->objects.size(); u++ )
        {
            if( this->objects[i] == objects[u] )
            {
                deletedObjects.push_back( objects[i] );
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
void ObjectsEngineVector::ClearAllDeletedObjects()
{
	//
	deletedObjects.clear();
}
void ObjectsEngineVector::ClearAllDeletedObjects( bool includePersistent )
{

}
void ObjectsEngineVector::PurgeAllObjects()
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() )
        {
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void ObjectsEngineVector::PurgeAllObjectsExcept( Object* object )
{

}
void ObjectsEngineVector::PurgeAllObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineVector::PurgeAllObjects( bool includePersistent )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
        {
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void ObjectsEngineVector::PurgeAllObjectsExcept( Object* object, bool includePersistent )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
        {
            if( objects[i] != object )
            {
                objects.erase( objects.begin() + i );
                i--;
            }   
        }
    }
}
void ObjectsEngineVector::PurgeAllObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}
void ObjectsEngineVector::PurgeObject( unsigned long uid )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i]->GetUID() == uid )
        {
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void ObjectsEngineVector::PurgeObject( Object* object )
{
	for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i] == object )
        {
            objects.erase( objects.begin() + i );
            i--;
        }
    }
}
void ObjectsEngineVector::PurgeObjects( vector<unsigned long> uids )
{
	for( unsigned int u = 0; u < uids.size(); u++ )
    {
        for( unsigned int i = 0; i < objects.size(); i++ )
        {
            if( objects[i]->GetUID() == uids[u] )
            {
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
void ObjectsEngineVector::PurgeObjects( vector<Object*> objects )
{
	for( unsigned int u = 0; u < objects.size(); u++ )
    {
        for( unsigned int i = 0; i < this->objects.size(); i++ )
        {
            if( this->objects[i] == objects[u] )
            {
                objects.erase( objects.begin() + i );
                i--;
            }
        }
    }
}
// int ObjectsEngineVector::CreateStore()
// void ObjectsEngineVector::DeleteStore( int storeID )
// void ObjectsEngineVector::StoreAllObjects()
// void ObjectsEngineVector::StoreAllObjectsExcept( Object* object, int storeID )
// void ObjectsEngineVector::StoreAllObjectsExcept( vector<Object*> objects, int storeID )
// void ObjectsEngineVector::StoreAllObjects( bool includePersistent, int storeID )
// void ObjectsEngineVector::StoreAllObjectsExcept( Object* object, bool includePersistent, int storeID )
// void ObjectsEngineVector::StoreAllObjectsExcept( vector<Object*> objects, bool includePersistent, int storeID )
// void ObjectsEngineVector::StoreObject( unsigned long uid ,int storeID )
// void ObjectsEngineVector::StoreObject( Object* object, int storeID )
// void ObjectsEngineVector::StoreObjects( vector<unsigned long> uids, int storeID )
// void ObjectsEngineVector::StoreObjects( vector<Object*> objects, int storeID )
// void ObjectsEngineVector::RestoreAllObjects()
// void ObjectsEngineVector::RestoreAllObjectsExcept( Object* object, int storeID )
// void ObjectsEngineVector::RestoreAllObjectsExcept( vector<Object*> objects, int storeID )
// void ObjectsEngineVector::RestoreAllObjects( bool includePersistent, int storeID )
// void ObjectsEngineVector::RestoreAllObjectsExcept( Object* object, bool includePersistent, int storeID )
// void ObjectsEngineVector::RestoreAllObjectsExcept( vector<Object*> objects, bool includePersistent, int storeID )
// void ObjectsEngineVector::RestoreObject( unsigned long uid ,int storeID )
// void ObjectsEngineVector::RestoreObject( Object* object, int storeID )
// void ObjectsEngineVector::RestoreObjects( vector<unsigned long> uids, int storeID )
// void ObjectsEngineVector::RestoreObjects( vector<Object*> objects, int storeID )


unsigned int ObjectsEngineVector::CreateGrid( unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, unsigned int offsetX, unsigned int offsetY )
{
    return 0;
}
Grid* ObjectsEngineVector::GetGrid( unsigned int id )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        if( grids[i]->id == id )
        {
            return grids[i];
        }
    }
    return NULL;
}
vector<Grid*> ObjectsEngineVector::GetAllGrids()
{
    //
    return grids;
}
void ObjectsEngineVector::PopulateGrid( unsigned int gridID, unsigned int assetID )
{

}
void ObjectsEngineVector::DeleteGrid( unsigned int id )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        if( grids[i]->id == id )
        {
            for( unsigned int y = 0; y < grids[i]->objects.size(); y++ )
            {
                for( unsigned int x = 0; x < grids[i]->objects[y].size(); x++ )
                {
                    DeleteObject( grids[i]->objects[y][x] );
                }
                grids[i]->objects[y].clear();
            }
            grids[i]->objects.clear();
            delete grids[i];
            return;
        }
    }
}
void ObjectsEngineVector::DeleteAllGrids()
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int y = 0; y < grids[i]->objects.size(); y++ )
        {
            for( unsigned int x = 0; x < grids[i]->objects[y].size(); x++ )
            {
                DeleteObject( grids[i]->objects[y][x] );
            }
            grids[i]->objects[y].clear();
        }
        grids[i]->objects.clear();
        delete grids[i];
    }
}