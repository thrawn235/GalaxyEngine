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
public:
					Player				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void 	ClientSideUpdate	();
	virtual void	Render				();
};




class Enemy : public Object
{
protected:
public:
					Enemy				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void	Render				();
};

#endif