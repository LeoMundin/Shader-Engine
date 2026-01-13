#pragma once
#ifndef FPSCHARACTERCONTROLLER_H
#define FPSCHARACTERCONTROLLER_H

#include "../ElderHex.h"


/// <summary>
/// Handles movement and rotation of a camera to emulate first person control.
/// </summary>
class FpsMovementComponent : public Component
{
public:

	float MovementSpeed = 20.0f;
	

	FpsMovementComponent(Camera* renderCam,TransformComponent *transform, RigidbodyComponent *rigidbody) 
	{
		_camera = renderCam;
		_transformComponent = transform;
		_rigidbodyComponent = rigidbody;
	};


	void Update(float deltaTime) override {
		// Keeps the camaera in the same position as the player transform + a y offset to add a little height to the player
		float playerHeight = 2;
		_camera->Position = _transformComponent->Position + glm::vec3(0, playerHeight,0);

		CameraLook();
		HorizontalMovement(deltaTime);

		if (InputSystem::LeftMousePressed) {
			// call event;
			GameEventsManager::GetInstance()->TakeDamage();
		}

	}

	void CameraLook() {

		_camera->Look(InputSystem::LookOffset.x, InputSystem::LookOffset.y, true);
		InputSystem::LookOffset = glm::vec2(0, 0); // sets the offset back to 0 after moving to prevent continual input

	}

	void HorizontalMovement(float deltaTime) {
		rp3d::Vector3 right = _transformComponent->Vector3GlmToRp3d(_camera->Right) * InputSystem::MovementInput.x * MovementSpeed ;
		_rigidbodyComponent->Rigidbody->applyLocalForceAtCenterOfMass(right);

		rp3d::Vector3 forward = _transformComponent->Vector3GlmToRp3d(_camera->Forward) * InputSystem::MovementInput.y * MovementSpeed ;
		_rigidbodyComponent->Rigidbody->applyLocalForceAtCenterOfMass(forward);

	}


private:

	Camera* _camera;
	TransformComponent* _transformComponent;
	RigidbodyComponent* _rigidbodyComponent;

};

#endif