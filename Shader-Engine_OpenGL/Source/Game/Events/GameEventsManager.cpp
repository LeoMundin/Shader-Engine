#include "GameEventsManager.h"

GameEventsManager* GameEventsManager::sp_instance = nullptr;
std::mutex GameEventsManager::mutex_;

GameEventsManager* GameEventsManager::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!sp_instance)
        sp_instance = new GameEventsManager();
    return sp_instance;
}

GameEventsManager::GameEventsManager() {}
GameEventsManager::~GameEventsManager() {}

void GameEventsManager::TakeDamage()
{
    if (OnTakeDamage.HasSubscribers()) {
        OnTakeDamage.Invoke();

    }
}
