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
}
void GameClient::Run()
{
    engine->ClientSideUpdateAll();
    engine->PredictAll();
    engine->RenderAll();
}