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

struct PlayerStats : ObjectStats
{
	bool up, down, left, right;
	bool fire;
	int target;
};

class Player : public Object
{
private:
	
protected:
	PlayerStats*	netStats;
public:
					Player				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void 	ClientSideUpdate	();
	virtual void	Render				();
};


struct EnemyStats : ObjectStats
{
	
};

class Enemy : public Object
{
private:
	
protected:
	EnemyStats*		netStats;
public:
					Enemy				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void	Render				();
};

#endif