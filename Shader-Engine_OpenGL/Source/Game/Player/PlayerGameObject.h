#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../ElderHex.h"
#include "FPSCharacterController.h"
#include "UI/HealthBar.h"


class Player : public GameObject 
{
public:

	RigidbodyComponent* Rigidbody;
	HealthBar PlayerHealthBar;

	Player() {};
	Player(Camera *camera, rp3d::PhysicsWorld *physicsWorld,int screenWidth, int screenHeight)
	{
		Transform->Position = glm::vec3(20.0f, 1.0f, 30.0f);
		PlayerHealthBar = HealthBar(5, screenWidth, screenHeight, glm::vec2(20, 1050));
		PlayerHealthBar.Height = 100.0f;

		Rigidbody = addComponent<RigidbodyComponent>(physicsWorld, Transform);
		Rigidbody->Rigidbody->setLinearDamping(2);
		_characterController = addComponent<FPSCharacterController>(camera,Transform,Rigidbody);
	};


private:

	FPSCharacterController* _characterController;


};

#endif
