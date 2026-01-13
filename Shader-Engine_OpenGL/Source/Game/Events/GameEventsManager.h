#pragma once
#ifndef GAME_EVENTS_MANAGER_H
#define GAME_EVENTS_MANAGER_H

#include "../../Engine/Events/Event.h"
#include <mutex>

class GameEventsManager
{
public:
    GameEventsManager(GameEventsManager&) = delete;
    void operator=(const GameEventsManager&) = delete;

    static GameEventsManager* GetInstance();

    Event OnTakeDamage;
    void TakeDamage();

private:
    static GameEventsManager* sp_instance;
    static std::mutex mutex_;

    GameEventsManager();
    ~GameEventsManager();
};

#endif
