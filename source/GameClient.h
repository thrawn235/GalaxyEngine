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
#include "GameNode.h"
//====================================

//======= forward declarations =======
class GameServer;
//====================================

class GameClient : public GameNode
{
protected:
	bool			waitingForUpdate;              //true if the server hasnt responded
	unsigned int	clientTicksSinceLogicTick;     //for prediction
	float			tickRate;                      //for prediction
	bool			exit;

public:
                    GameClient              ();     //Constructor
    virtual         ~GameClient             ();     //Destructor
    //------------ communication with main -----------------
            bool	GetExit					();
    //------------------------------------------------------
            void    Run                     ();     //everything is done here
            void    ConnectToServer         ();
};

//#endif