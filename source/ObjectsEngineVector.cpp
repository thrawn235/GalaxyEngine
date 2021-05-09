//ObjectsEngineVector.cpp

#include "ObjectsEngineVector.h"
#include "GameEngine.h"
#include "DerivedObjects.h"

ObjectsEngineVector::ObjectsEngineVector( GameEngine* engine ) : ObjectsEngine( engine )
{
    //
	this->engine = engine;
}
ObjectsEngineVector::~ObjectsEngineVector()
{
    engine->debug->PrintString( "Purge all objects... \n" );
    PurgeAllObjects( true );
    PurgeAllGrids();
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
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            allObjects.push_back( grids[i]->objects[u] );
        }
    }
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        allObjects.push_back( objects[i] );
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllObjectsExcept( Object* object )
{
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( grids[i]->objects[u] == object )
            {
                allObjects.push_back( grids[i]->objects[u] );
            }
        }
    }
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i] == object )
        {
            allObjects.push_back( objects[i] );
        }
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllObjectsExcept( vector<Object*> objects )
{
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned z = 0; z < objects.size(); z++ )
            {
                if( grids[i]->objects[u] == objects[z] )
                {
                    allObjects.push_back( grids[i]->objects[u] );
                }
            }
        }
    }
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        for( unsigned z = 0; z < objects.size(); z++ )
        {
            if( this->objects[i] == objects[z] )
            {
                allObjects.push_back( this->objects[i] );
            }
        }
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllGridObjectsExcept( Object* object )
{
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( grids[i]->objects[u] == object )
            {
                allObjects.push_back( grids[i]->objects[u] );
            }
        }
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllGridObjectsExcept( vector<Object*> objects )
{
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned z = 0; z < objects.size(); z++ )
            {
                if( grids[i]->objects[u] == objects[z] )
                {
                    allObjects.push_back( grids[i]->objects[u] );
                }
            }
        }
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllAgentObjectsExcept( Object* object )
{
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( objects[i] == object )
        {
            allObjects.push_back( objects[i] );
        }
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllAgentObjectsExcept( vector<Object*> objects )
{
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        for( unsigned z = 0; z < objects.size(); z++ )
        {
            if( this->objects[i] == objects[z] )
            {
                allObjects.push_back( this->objects[i] );
            }
        }
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllGridObjects()
{
    vector<Object*> allObjects;
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            allObjects.push_back( grids[i]->objects[u] );
        }
    }
    //engine->debug->PrintString( "Get objects, i have %i\n", allObjects.size() );
    return allObjects;
}
vector<Object*> ObjectsEngineVector::GetAllAgentObjects()
{
    //
    return objects;
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
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( grids[i]->objects[u]->GetUID() == uid )
            {
                return grids[i]->objects[u];
            }
        }
    }
    return NULL;
}

void ObjectsEngineVector::DeleteAllObjects()
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() )
            {
                deletedObjects.push_back( grids[i]->objects[u] );
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
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
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() )
            {
                if( grids[i]->objects[u] != object )
                {
                    deletedObjects.push_back( grids[i]->objects[u] );
                    grids[i]->objects.erase( grids[i]->objects.begin() + u );
                    u--;
                }
            }
        }
    }
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
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned int z = 0; z < objects.size(); z++ )
            {
                if( grids[i]->objects[u] != objects[z] )
                {
                    if( !grids[i]->objects[u]->GetPersistent() )
                    {
                        deletedObjects.push_back( grids[i]->objects[u] );
                        grids[i]->objects.erase( grids[i]->objects.begin() + u );
                        u--;
                    }
                }
            }
        }
    }
    for( unsigned int i = 0; i < this->objects.size(); i++ )
    {
        for( unsigned int z = 0; z < objects.size(); z++ )
        {
            if( grids[i]->objects[u] != objects[z] )
            {
                if( !objects[i]->GetPersistent() )
                {
                    deletedObjects.push_back( this->objects[i] );
                    this->objects.erase( this->objects.begin() + i );
                    i--; 
                }
            }
        }
    }
}
void ObjectsEngineVector::DeleteAllObjects( bool includePersistent )
{
	for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() || includePersistent )
            {
                deletedObjects.push_back( grids[i]->objects[u] );
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistentc )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void ObjectsEngineVector::DeleteAllObjectsExcept( Object* object, bool includePersistent )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() || includePersistent )
            {
                if( grids[i]->objects[u] != object )
                {
                    deletedObjects.push_back( grids[i]->objects[u] );
                    grids[i]->objects.erase( grids[i]->objects.begin() + u );
                    u--;
                }
            }
        }
    }
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
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
void ObjectsEngineVector::DeleteAllObjectsExcept( vector<Object*> objects, bool includePersistent )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned int z = 0; z < objects.size(); z++ )
            {
                if( grids[i]->objects[u] != objects[z] )
                {
                    if( !grids[i]->objects[u]->GetPersistent() || includePersistent )
                    {
                        deletedObjects.push_back( grids[i]->objects[u] );
                        grids[i]->objects.erase( grids[i]->objects.begin() + u );
                        u--;
                    }
                }
            }
        }
    }
    for( unsigned int i = 0; i < this->objects.size(); i++ )
    {
        for( unsigned int z = 0; z < objects.size(); z++ )
        {
            if( grids[i]->objects[u] != objects[z] )
            {
                if( !objects[i]->GetPersistent() || includePersistent )
                {
                    deletedObjects.push_back( this->objects[i] );
                    this->objects.erase( this->objects.begin() + i );
                    i--; 
                }
            }
        }
    }
}

void ObjectsEngineVector::DeleteAllGridObjects()
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() )
            {
                deletedObjects.push_back( grids[i]->objects[u] );
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
}
void ObjectsEngineVector::DeleteAllGridObjectsExcept( Object* object )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() )
            {
                if( grids[i]->objects[u] != object )
                {
                    deletedObjects.push_back( grids[i]->objects[u] );
                    grids[i]->objects.erase( grids[i]->objects.begin() + u );
                    u--;
                }
            }
        }
    }
}
void ObjectsEngineVector::DeleteAllGridObjectsExcept( vector<Object*> objects )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned int z = 0; z < objects.size(); z++ )
            {
                if( grids[i]->objects[u] != objects[z] )
                {
                    if( !grids[i]->objects[u]->GetPersistent() )
                    {
                        deletedObjects.push_back( grids[i]->objects[u] );
                        grids[i]->objects.erase( grids[i]->objects.begin() + u );
                        u--;
                    }
                }
            }
        }
    }
}
void ObjectsEngineVector::DeleteAllGridObjects( bool includePersistent )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() || includePersistent )
            {
                deletedObjects.push_back( grids[i]->objects[u] );
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
}
void ObjectsEngineVector::DeleteAllGridObjectsExcept( Object* object, bool includePersistent )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() || includePersistent )
            {
                if( grids[i]->objects[u] != object )
                {
                    deletedObjects.push_back( grids[i]->objects[u] );
                    grids[i]->objects.erase( grids[i]->objects.begin() + u );
                    u--;
                }
            }
        }
    }
}
void ObjectsEngineVector::DeleteAllGridObjectsExcept( vector<Object*> objects, bool includePersistent )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned int z = 0; z < objects.size(); z++ )
            {
                if( grids[i]->objects[u] != objects[z] )
                {
                    if( !grids[i]->objects[u]->GetPersistent() || includePersistent )
                    {
                        deletedObjects.push_back( grids[i]->objects[u] );
                        grids[i]->objects.erase( grids[i]->objects.begin() + u );
                        u--;
                    }
                }
            }
        }
    }
}

void ObjectsEngineVector::DeleteAllAgentObjects()
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
void ObjectsEngineVector::DeleteAllAgentObjectsExcept( Object* object )
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
void ObjectsEngineVector::DeleteAllAgentObjectsExcept( vector<Object*> objects )
{
    for( unsigned int i = 0; i < this->objects.size(); i++ )
    {
        for( unsigned int z = 0; z < objects.size(); z++ )
        {
            if( grids[i]->objects[u] != objects[z] )
            {
                if( !objects[i]->GetPersistent() )
                {
                    deletedObjects.push_back( this->objects[i] );
                    this->objects.erase( this->objects.begin() + i );
                    i--; 
                }
            }
        }
    }
}
void ObjectsEngineVector::DeleteAllAgentObjects( bool includePersistent )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistentc )
        {
            deletedObjects.push_back( objects[i] );
            objects.erase( objects.begin() + i );
            i--;   
        }
    }
}
void ObjectsEngineVector::DeleteAllAgentObjectsExcept( Object* object, bool includePersistent )
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        if( !objects[i]->GetPersistent() || includePersistent )
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
void ObjectsEngineVector::DeleteAllAgentObjectsExcept( vector<Object*> objects, bool includePersistent )
{
    for( unsigned int i = 0; i < this->objects.size(); i++ )
    {
        for( unsigned int z = 0; z < objects.size(); z++ )
        {
            if( grids[i]->objects[u] != objects[z] )
            {
                if( !objects[i]->GetPersistent() || includePersistent )
                {
                    deletedObjects.push_back( this->objects[i] );
                    this->objects.erase( this->objects.begin() + i );
                    i--; 
                }
            }
        }
    }
}

void ObjectsEngineVector::DeleteObject( unsigned long uid )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( grids[i]->objects[u]->GetUID() == uid )
            {
                deletedObjects.push_back( grids[i]->objects[u] );
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
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
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( grids[i]->objects[u] == object )
            {
                deletedObjects.push_back( grids[i]->objects[u] );
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
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
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned int z = 0; z < uids.size(); z++ )
            {
                if( grids[i]->objects[u]->GetUID() == uids[z] )
                {
                    deletedObjects.push_back( grids[i]->objects[u] );
                    grids[i]->objects.erase( grids[i]->objects.begin() + u );
                    u--;
                }
            }
        }
    }
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
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            for( unsigned int z = 0; z < objetcs.size(); z++ )
            {
                if( grids[i]->objects[u]->GetUID() == objects[z] )
                {
                    deletedObjects.push_back( grids[i]->objects[u] );
                    grids[i]->objects.erase( grids[i]->objects.begin() + u );
                    u--;
                }
            }
        }
    }
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
    for( unsigned int i = 0; i < deletedObjects.size(); i++ )
    {
        if( !deletedObjects[i]->GetPersistent() || includePersistent )
        {
            deletedObjects.erase( deletedObjects.begin() + i )
        }
    }
}

void ObjectsEngineVector::PurgeAllObjects()
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() )
            {
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
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
	for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int u = 0; u < grids[i]->width * grids[i]->height; u++ )
        {
            if( !grids[i]->objects[u]->GetPersistent() || includePersistent )
            {
                grids[i]->objects.erase( grids[i]->objects.begin() + u );
                u--;
            }
        }
    }
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

}
void ObjectsEngineVector::PurgeAllObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}

void ObjectsEngineVector::PurgeAllGridObjects()
{

}
void ObjectsEngineVector::PurgeAllGridObjectsExcept( Object* object )
{

}
void ObjectsEngineVector::PurgeAllGridObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineVector::PurgeAllGridObjects( bool includePersistent )
{

}
void ObjectsEngineVector::PurgeAllGridObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineVector::PurgeAllGridObjectsExcept( vector<Object*> objects, bool includePersistent )
{

}

void ObjectsEngineVector::PurgeAllAgentObjects()
{

}
void ObjectsEngineVector::PurgeAllAgentObjectsExcept( Object* object )
{

}
void ObjectsEngineVector::PurgeAllAgentObjectsExcept( vector<Object*> objects )
{

}
void ObjectsEngineVector::PurgeAllAgentObjects( bool includePersistent )
{

}
void ObjectsEngineVector::PurgeAllAgentObjectsExcept( Object* object, bool includePersistent )
{

}
void ObjectsEngineVector::PurgeAllAgentObjectsExcept( vector<Object*> objects, bool includePersistent )
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


unsigned int ObjectsEngineVector::LoadMap( unsigned int id )
{
    struct Map
    {
        char        magic[3];
        uint32_t    width;
        uint32_t    height;
        uint32_t    tileWidth;
        uint32_t    tileHeight;
        uint32_t    numLayers;
        char        data;
    }__attribute__((packed));

    Map* map = (Map*)engine->data->GetData( id );

    engine->debug->PrintString( "Map: magic %c%c%c w/h:%i/%i, numLayers:%i\n", map->magic[0], map->magic[1], map->magic[2], map->width, map->height, map->numLayers );
    
    struct Layer
    {
        uint32_t    tileSetID;
        uint32_t    width;
        uint32_t    height;
        uint32_t    offsetX;
        uint32_t    offsetY;
        char        data;
    }__attribute__((packed));
    
    char* layerPtr;
    layerPtr = &map->data;

    for( unsigned int i = 0; i < map->numLayers; i++ )
    {
        Layer* layer = (Layer*)layerPtr;
        engine->debug->PrintString( "Layer: SetID:%i w/h:%i/%i, offsetX/Y: %i/%i tileW/H %i/%i\n", layer->tileSetID, layer->width, layer->height, layer->offsetX, layer->offsetY, map->tileWidth, map->tileHeight );
        
        if( layer->tileSetID != 0 )
        {
            Grid* grid = new Grid;
            grid->id             = layer->tileSetID;
            grid->width          = layer->width;
            grid->height         = layer->height;
            grid->offsetX        = layer->offsetX;
            grid->offsetY        = layer->offsetY;
            grid->tileWidth      = map->tileWidth;
            grid->tileHeight     = map->tileHeight;

            unsigned char* data = (unsigned char*)&layer->data;


            grid->objects = (Object**)malloc( layer->width * layer->height * sizeof(Object*) );
            Vector2D newTilePos;
            for( unsigned int y = 0; y < layer->height; y++ )
            {
                for( unsigned int x = 0; x < layer->width; x++ )
                {
                    //create tile:
                    if( *data != 0 )
                    {
                        Object* tileObjectPtr = new Tile( engine );
                        Tile* tile = (Tile*)tileObjectPtr;
                        if( layer->tileSetID == 23 )  //fix! its fucked up
                        {
                            tile->SetTileSetID( DATA_TILESET );
                        }
                        tile->SetTileIndex( (*data) - 1 );
                        tile->SetPos( newTilePos );
                        engine->debug->PrintString( "%X,", (*data) - 1 );
                        grid->objects[y * layer->height + x] = tileObjectPtr;
                        data++;
                        newTilePos.x = newTilePos.x + map->tileWidth;

                        //engine->text->PrintString( "Tile: %i W/H: %f/%f\n", y * layer->height + x, grid->objects[y * layer->height + x]->GetPos().x, grid->objects[y * layer->height + x]->GetPos().y );
                    }
                }
                newTilePos.x = 0;
                newTilePos.y = newTilePos.y + map->tileHeight;
            }

            grids.push_back( grid );

            /*for( unsigned int xy = 0; xy < grid->width * grid->height; xy++ )
            {
                engine->text->PrintString( "Tile: %i W/H: %f/%f\n", xy, grids[i]->objects[xy]->GetPos().x, grids[i]->objects[xy]->GetPos().y ); 
            }*/
        }

        layerPtr = layerPtr + layer->width * layer->height + sizeof(uint32_t) * 5;
    }

    return 0;
}
unsigned int ObjectsEngineVector::ObjectsEngineVector::CreateGrid( unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, unsigned int offsetX, unsigned int offsetY )
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
void ObjectsEngineVector::PurgeGrid( unsigned int id )
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        if( grids[i]->id == id )
        {
            for( unsigned int xy = 0; xy < grids[i]->width * grids[i]->height; xy++ )
            {

                DeleteObject( grids[i]->objects[xy] );
            }
            free( grids[i]->objects );
            return;
        }
    }
}
void ObjectsEngineVector::PurgeAllGrids()
{
    for( unsigned int i = 0; i < grids.size(); i++ )
    {
        for( unsigned int xy = 0; xy < grids[i]->width * grids[i]->height; xy++ )
        {

            DeleteObject( grids[i]->objects[xy] );
        }
        free( grids[i]->objects );
        return;
    }
}