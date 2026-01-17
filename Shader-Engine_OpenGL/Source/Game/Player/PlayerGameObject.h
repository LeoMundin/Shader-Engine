#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../ElderHex.h"
#include "FPSCharacterController.h"
#include "../Components/HealthComponent.h"
#include "UI/HealthBar.h"


class Player : public GameObject 
{
public:

	RigidbodyComponent* Rigidbody;
	HealthComponent* Health;
	HealthBar PlayerHealthBar;

	Player() {};
	Player(Camera *camera, rp3d::PhysicsWorld *physicsWorld,int screenWidth, int screenHeight)
	{
		
		Transform->Position = glm::vec3(20.0f, 1.0f, 30.0f);
		
		// UI
		PlayerHealthBar = HealthBar(_maxPlayerHealth, screenWidth, screenHeight, glm::vec2(20, 1050));
		PlayerHealthBar.Height = 100.0f;

		// Components
		Rigidbody = addComponent<RigidbodyComponent>(physicsWorld, Transform);
		Rigidbody->Rigidbody->setLinearDamping(2);

		_characterController = addComponent<FpsMovementComponent>(camera,Transform,Rigidbody, physicsWorld);

		Health = addComponent<HealthComponent>(_maxPlayerHealth);

	};


private:

	int _maxPlayerHealth = 3;
	FpsMovementComponent* _characterController;
	


};

#endif
