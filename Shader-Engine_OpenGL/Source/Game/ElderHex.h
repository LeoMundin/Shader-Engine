#pragma once
#ifndef ELDERHEX_H
#define ELDERHEX_H

#include "../Engine/TuftEngine.h"

#include "Player/PlayerGameObject.h"
#include "GameObjects/Terrain.h"
#include "Components/HealthComponent.h"

class ElderHex : public TuftEngine 
{

public:
	ElderHex(unsigned int width, unsigned int height) :TuftEngine(width, height) {};

	// Scene Assets
	Player PlayerGameObject;
	Terrain TerrainGameObject;

protected:
	void OnAwake()  override;
	void OnUpdate() override;
	void OnRender() override;
	void OnRenderUI() override;

};

#endif



