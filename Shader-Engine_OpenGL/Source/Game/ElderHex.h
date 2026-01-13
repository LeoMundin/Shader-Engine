#pragma once
#ifndef ELDERHEX_H
#define ELDERHEX_H

#include "../Engine/TuftEngine.h"

#include "Events/GameEventsManager.h"
#include "Player/PlayerGameObject.h"
#include "GameObjects/Terrain.h"
#include "Components/HealthComponent.h"

// To-Do : Convert to sort through a list of scene objects and manage extra game systems such as Level management and Input.
class ElderHex : public TuftEngine 
{

public:
	ElderHex(unsigned int width, unsigned int height) :TuftEngine(width, height) {};

	// Scene Assets
	Player PlayerGameObject;
	Terrain TerrainGameObject;

	


protected:
	// To-Do : Convert to pass lifecycle changes to all of the scene objects
	void OnAwake()  override;
	void OnUpdate() override;
	void OnRender() override;
	void OnRenderUI() override;

};

#endif



