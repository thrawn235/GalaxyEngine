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
class GameServer;
//====================================

class GameClient
{
protected:
	bool			waitingForUpdate;
	unsigned int	clientTicksSinceLogicTick;
	float			tickRate;
	bool			exit;
    GameEngine* 	engine;

public:
            GameClient              ( GameServer** server );     //Constructor
            ~GameClient             ();     //Destructor
    //------------ communication with main -----------------
    bool	GetExit					();
    //------------------------------------------------------
    void    Run                     ();     //everything is done here
};

//#endif