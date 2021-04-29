//====================================
// Object.h
// the Main Parent Class of all Objects in the Game.
// All other Objects (player, enemies etc) are derived vom it-
//====================================

//========== include guard ===========
#ifndef OBJECT
#define OBJECT
//====================================

//========== stdlib includes =========
#include <stdio.h>
#include <cstdint>
using namespace std;
//====================================

//========= galaxy includes ==========
//#include "GameEngine.h"
#include "Vector2D.h"
//====================================

//============= defines ==============
#define OBJECT_TYPE_OBJECT                  0
#define OBJECT_TYPE_PLAYER                  1
#define OBJECT_TYPE_ENEMY                   2
#define OBJECT_TYPE_MAIN_MENU               3
#define OBJECT_TYPE_PERFORMANCE_OVERLAY     4
//====================================

//======= forward declarations =======
class GameEngine;
class GameClient;
class GameServer;
//====================================

//=========== global =================
extern GameServer* server;
extern GameClient* client;
//====================================

struct NetStats
{
            uint32_t            uid;                            //unique identifier
            uint16_t            type;                           //type of the object
            uint16_t            size;
}__attribute__ ((packed));

struct ObjectStats : NetStats
{   
            Vector2D            pos;                            //position of the object
            Vector2D            movement;                       //final movement vector (once all forces are added)

            bool                visible;
            bool                active;
            bool                predict;
            bool                clientActive;
            bool                persistent;
            unsigned char       drawOrder;
};

class Object
{
protected:
            NetStats*           baseNetStats        = NULL;
            ObjectStats*        netStats            = NULL;

            GameEngine*         engine;                         //pointer to the game engine

public:
    

    //------------ Constructor/Destructor: --------------------
                                Object                  ( GameEngine* engine );
                                ~Object                 ();

    //---------------------- Get/Set --------------------------
            void                SetEngine               ( GameEngine* engine );
            GameEngine*         GetEngine               ();
            unsigned long int   GetUID                  ();
            void                SetUID                  ( unsigned long uid );
            unsigned int        GetType                 ();
            void                SetType                 ( unsigned int type );
            bool                GetVisible              ();
            bool                GetActive               ();
            bool                GetPredict              ();
            bool                GetClientActive         ();
            bool                GetPersistent           ();
            void                SetVisible              ( bool visible );
            void                SetActive               ( bool active );
            void                SetPredict              ( bool predict );
            void                SetClientActive         ( bool clientActive );
            void                SetPersistent           ( bool persistent );
            Vector2D            GetPos                  ();
            void                SetPos                  ( Vector2D pos );
            Vector2D            GetMovement             ();
            void                SetMovement             ( Vector2D movement );
            unsigned char       GetDrawOrder            ();
            void                SetDrawOrder            ( unsigned char drawOrder );

    virtual void                PrintStats              ();

    //-------------------- Network ----------------------------
    virtual void                SendStatus              ();                          //serialize all attributes and send them over the net
    virtual void                LoadStatus              ( void* data );              //get data from the net and update all attributes

    //-- Base Engine Funcions (called by engine every Frame) --
    virtual void                Update                  ();                          //is called every tick (usually on the server)
    virtual void                GameLogic               ();                          //is called from Update. handles just the GameLogic (minus netupdate etc)
    virtual void                ClientSideUpdate        ();
    virtual void                UpdateServerIndependend ();
    virtual void                Predict                 ( float tickRate );
    virtual void                Render                  ();

    // ---------------- Object Selection Methods --------------
    //GetAllObjects
};

#endif