#pragma once
#ifndef ELDERHEX_H
#define ELDERHEX_H

#include "TuftEngine.h"
#include "GameObject.h"

class ElderHex : public TuftEngine 
{

public:
	ElderHex(unsigned int width, unsigned int height) :TuftEngine(width, height) {}; // Constructor

	// Scene Assets
	GameObject bag;


protected:

	void OnAwake() override;
	void OnUpdate() override;
	void OnRender() override;

};

#endif



