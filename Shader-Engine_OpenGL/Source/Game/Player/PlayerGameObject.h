#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../ElderHex.h"
#include "FPSCharacterController.h"


class Player : public GameObject 
{
public:

	RigidbodyComponent* Rigidbody;


	Player() {};
	Player(Camera *camera, rp3d::PhysicsWorld *physicsWorld)
	{
		Transform->Position = glm::vec3(20.0f, 1.0f, 30.0f);


		Rigidbody = addComponent<RigidbodyComponent>(physicsWorld, Transform);
		Rigidbody->Rigidbody->setLinearDamping(2);
		_characterController = addComponent<FPSCharacterController>(camera,Transform,Rigidbody);
	};

private:

	FPSCharacterController* _characterController;


};

#endif
