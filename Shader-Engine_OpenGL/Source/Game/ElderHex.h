#pragma once
#ifndef ELDERHEX_H
#define ELDERHEX_H

#include "../Engine/TuftEngine.h"

#include "Player/PlayerGameObject.h"
#include "Components/HealthComponent.h"

class ElderHex : public TuftEngine 
{

public:
	ElderHex(unsigned int width, unsigned int height) :TuftEngine(width, height) {};

	// Scene Assets
	Player player;
	GameObject bag;
	GameObject Terrain;

protected:
	void OnAwake()  override;
	void OnUpdate() override;
	void OnRender() override;

};

#endif



