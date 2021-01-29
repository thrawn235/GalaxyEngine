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

    Object* tmp = new Object( engine );
    engine->AddObject( tmp );
    tmp = new Object( engine );
    engine->AddObject( tmp );
    tmp = new Object( engine );
    engine->AddObject( tmp );
}
void GameClient::Run()
{
    engine->UpdateGamestateFromNet();

    //debug:
    engine->text->PrintString("this is the client:\n");
    engine->text->PrintString("these are my objects:\n");
    vector<Object*> objects = engine->GetAllObjects();
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        engine->text->PrintString("UID: ");
        engine->text->PrintInt( objects[i]->GetUID() );
        engine->text->EndLine();
    }
    engine->ClientSideUpdateAll();
    engine->PredictAll();
    engine->RenderAll();
}