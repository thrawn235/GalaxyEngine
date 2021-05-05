//====================================
// DerivedObjects.h
// All Game Objects are derived from the object base class (Object.h)
//====================================

//========== include guard ===========
#ifndef DERIVED_OBJECTS
#define DERIVED_OBJECTS
//====================================

//========== stdlib includes =========
#include <string>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "Object.h"
//#include "GameServer.h"
//#include "GameEngine.h"
//====================================

//======= forward declarations =======
class GameServer;
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


struct TileStats : ObjectStats
{
	unsigned int 	tileSetID;
	unsigned char 	tileIndex;
};

class Tile : public Object
{
private:
	
protected:
	TileStats*		netStats;
public:
					Tile				( GameEngine* engine );
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


struct MainMenuStats : ObjectStats
{
	
};

class MainMenu : public Object
{
private:
	
protected:
	MainMenuStats*	netStats;
	string 			mainInput;
	bool			hidden;
	bool			optionsMenu;
	int 			netType;
public:
					MainMenu				( GameEngine* engine );
					~MainMenu				();
	virtual void 	GameLogic				();
	virtual void 	ClientSideUpdate		();
	virtual void	UpdateServerIndependend	();
	virtual void	Render					();
	//--------------- MainMenu specific -----------------
};




struct PerformanceOverlayStats : ObjectStats
{
	
};

class PerformanceOverlay : public Object
{
private:
	
protected:
	PerformanceOverlayStats*	netStats;
public:
					PerformanceOverlay		( GameEngine* engine );
					~PerformanceOverlay		();
	virtual void 	GameLogic				();
	virtual void 	ClientSideUpdate		();
	virtual void	UpdateServerIndependend	();
	virtual void	Render					();
	//--------------- PerformanceOverlay specific -----------------
};

#endif