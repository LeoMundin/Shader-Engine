#pragma once
#ifndef LEVEL_1_H
#define LEVEL_1_H

#include "../../Engine/TuftEngine.h"

#include "../Events/GameEventsManager.h"
#include "../Player/PlayerGameObject.h"
#include "../GameObjects/Terrain.h"
#include "../Components/HealthComponent.h"
#include "../GameObjects/TargetDummy.h"
#include "../GameObjects/Trap.h"


class Level_1 : public Scene
{
public :


	// Scene Assets
	Player PlayerGameObject;
	Terrain TerrainGameObject;

	TargetDummy Dummy;
	Trap spikes;

	Texture _spriteTexture = Texture("Assets/Textures/crosshair.png", false);

	Level_1() : Scene() {
		this->ID = "Level One";
	}


protected:

	void Load(TuftEngine* enginePtr, rp3d::PhysicsWorld* physicsSim) override;

	// External Lifecycle Hooks
	void Awake() override; // Runs once before Game loop starts.
	void Update() override;  // Runs every frame to update game logic. 
	void Render() override; // Updates rendering every frame.
	void RenderUI() override; // Updates rendering for UI which whould be layered ontop of game, every frame.



};

#endif