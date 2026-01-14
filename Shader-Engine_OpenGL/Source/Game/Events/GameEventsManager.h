#pragma once
#ifndef GAME_EVENTS_MANAGER_H
#define GAME_EVENTS_MANAGER_H

#include "../../Engine/Events/Event.h"
#include "InputEvents.h"
#include "PlayerEvents.h"
#include <mutex>

class GameEventsManager
{
public:

    InputEvents *Input;
    PlayerEvents *Player;

    GameEventsManager(GameEventsManager&) = delete;// Prevents duplication.
    void operator=(const GameEventsManager&) = delete;// Prevents assignability.

    /// <summary>
    /// Retrieves the singleton instance of the GameEventsManager class.
    /// </summary>
    static GameEventsManager* GetInstance();

private:
    static GameEventsManager* sp_instance;
    static std::mutex mutex_;

    GameEventsManager();
    ~GameEventsManager();

};

#endif
