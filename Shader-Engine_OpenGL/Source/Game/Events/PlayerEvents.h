#pragma once
#ifndef PLAYER_EVENTS_H
#define PLAYER_EVENTS_H

#include "../../Engine/Events/Event.h"

class PlayerEvents
{

public:

    PlayerEvents() {};

    Event OnTakeDamage;
    void TakeDamage() {
        if (OnTakeDamage.HasSubscribers()) {
            OnTakeDamage.Invoke();

        }
    }
};

#endif