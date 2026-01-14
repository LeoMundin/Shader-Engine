#include "GameEventsManager.h"

// Initialize Static Variables.
GameEventsManager* GameEventsManager::sp_instance = nullptr;
std::mutex GameEventsManager::mutex_;

GameEventsManager::GameEventsManager() 
{
    Player = new PlayerEvents();
    Input = new InputEvents();
}

GameEventsManager::~GameEventsManager() {}


GameEventsManager* GameEventsManager::GetInstance(){
    std::lock_guard<std::mutex> lock(mutex_);
    if (!sp_instance)
        sp_instance = new GameEventsManager();
    return sp_instance;
}

