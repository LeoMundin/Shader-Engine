#pragma once
#ifndef ELDERHEX_H
#define ELDERHEX_H

#include "TuftEngine.h"
#include "GameObject.h"
#include "Player.h"
#include "FPSCharacterController.h"

class ElderHex : public TuftEngine 
{

public:
	ElderHex(unsigned int width, unsigned int height) :TuftEngine(width, height) {}; // Constructor

	// Scene Assets
	Player player = Player(&MainCamera);
	GameObject bag;

protected:

	void OnAwake() override;
	void OnUpdate() override;
	void OnRender() override;

};

#endif



