#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "FPSCharacterController.h"


class Player : public GameObject 
{
public:

	RigidbodyComponent* Rigidbody;

	Player() {};
	Player(Camera *camera, rp3d::PhysicsWorld *physicsWorld)
	{
		Rigidbody = addComponent<RigidbodyComponent>(physicsWorld, Transform);
		_characterController = addComponent<FPSCharacterController>(camera,Transform,Rigidbody);
	};

private:

	FPSCharacterController* _characterController;


};

#endif
