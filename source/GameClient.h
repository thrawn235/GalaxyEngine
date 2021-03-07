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
	bool			waitingForUpdate;              //true if the server hasnt responded
	unsigned int	clientTicksSinceLogicTick;     //for prediction
	float			tickRate;                      //for prediction
	bool			exit;
    
    GameEngine* 	engine;

public:
            GameClient              ();     //Constructor
            ~GameClient             ();     //Destructor
    //------------ communication with main -----------------
    bool	GetExit					();
    //------------------------------------------------------
    void    Run                     ();     //everything is done here
};

//#endif