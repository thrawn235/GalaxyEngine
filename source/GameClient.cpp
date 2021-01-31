//Client.cpp

#include "GameClient.h"

GameClient::GameClient()
{
    engine = new GameEngine;
    if( engine->net->GetType() == NET_TYPE_LOCAL_BUFFER )
    {
        engine->net->SetAddress( 1 );
        engine->net->SetTarget( 2 );
    }
    engine->SetHighestUID( 1000 );
}
void GameClient::Run()
{
    //debug:
    engine->debug->PrintString("this is the client:\n");

    engine->UpdateGamestateFromNet();
    
    engine->debug->PrintString("these are my objects:\n");
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->debug->PrintString("   UID: %i\n", objects[i]->GetUID() );
    }
    engine->ClientSideUpdateAll();
    engine->PredictAll();
    engine->RenderAll();
}