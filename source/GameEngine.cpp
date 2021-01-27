#include "GameEngine.h"

GameEngine::GameEngine()
{
    net = new NetEngineLocal;
    #ifdef dos
        text = new TextEngineSTDIO;
    #else
        text = new TextEngineIOStream;
    #endif
}
vector<Object*> GameEngine::GetAllObjects()
{
    return objects;
}
void GameEngine::UpdateAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        objects[i]->Update();
    }
}
void GameEngine::ClientSideUpdateAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        objects[i]->ClientSideUpdate();
    }
}
void GameEngine::PredictAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        objects[i]->Predict();
    }
}
void GameEngine::RenderAll()
{
    for( unsigned int i = 0; i < objects.size(); i++ )
    {
        objects[i]->Render();
    }
}