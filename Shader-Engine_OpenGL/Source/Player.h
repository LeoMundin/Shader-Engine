#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "FPSCharacterController.h"

class Player : public GameObject 
{
public:

	Player(Camera *camera)
	{
		_characterController = addComponent<FPSCharacterController>(camera,Transform);
	};

private:

	FPSCharacterController* _characterController;


};

#endif
