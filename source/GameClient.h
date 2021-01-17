//GameClient.h
//the GameClient class handles user input and graphics/sound output
//it communicates with the server component that does all the game logic

//why cant i use my include Guard !!!!!!!!!!!!??????????
//========== include guard ===========
//#ifdef GAMECLIENT
//#define GAMECLIENT
//====================================

//========== stdlib includes =========
#include <vector>
using namespace std;
//====================================

//========= galaxy includes ==========
#include "GameEngine.h"
#include "NetEngine.h"
//====================================

//======= forward declarations =======
//====================================

class GameClient
{
protected:
	GameEngine* engine;

public:
			GameClient 	( vector<NetCommand>* localNetBuffer );
	void 	Run			();
};

//#endif