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

struct PlayerStats
{
	bool up, down, left, right;
	bool fire;
	int target;
};

class Player : public Object
{
protected:
	PlayerStats		playerStats;
public:
					Player				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void 	ClientSideUpdate	();
	virtual void	Render				();
	virtual void	SendStatus			();
	virtual void	LoadStatus			( void* data );
};


struct EnemyStats
{
	
};

class Enemy : public Object
{
protected:
	EnemyStats		enemyStats;
public:
					Enemy				( GameEngine* engine );
	virtual void 	GameLogic			();
	virtual void	Render				();
	virtual void	SendStatus			();
	virtual void	LoadStatus			( void* data );
};

#endif