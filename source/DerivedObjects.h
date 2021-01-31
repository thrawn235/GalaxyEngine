//====================================
// DerivedObjects.h
// All Game Objects are derived from the object base class (Object.h)
//====================================

//========== include guard ===========
#ifndef DERIVED_OBJECTS
#define DERIVED_OBJECTS
//====================================

//========== stdlib includes =========
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Object.h"
//#include "GameEngine.h"
//====================================

//======= forward declarations =======
//====================================

class Player : public Object
{
protected:
	bool up, down, left, right;
	bool fire;
	int target;
public:
					Player				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void 	ClientSideUpdate	();
	virtual void	Render				();
	virtual void	LoadStatus			( void* data );
	virtual void	SendStatus			();
};




class Enemy : public Object
{
protected:
public:
					Enemy				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void	Render				();
	virtual void	LoadStatus			( void* data );
	virtual void	SendStatus			();
};

#endif