#pragma once
#ifndef FPSCHARACTERCONTROLLER_H
#define FPSCHARACTERCONTROLLER_H

#include "Component.h"
#include "InputSystem.h"
#include "Camera.h"


/// <summary>
/// Handles movement and rotation of a camera to emulate first person control.
/// </summary>
class FPSCharacterController : public Component
{
public:

	float MovementSpeed = 10.0f;

	FPSCharacterController(Camera* renderCam,TransformComponent *transform) 
	{
		_camera = renderCam;
		_transform = transform;
	};

	void Update(float deltaTime) override {
		_camera->Position = _transform->Position;

		CameraLook();
		HorizontalMovement(deltaTime);
	}

	void CameraLook() {

		_camera->Look(InputSystem::LookOffset.x, InputSystem::LookOffset.y, true);
		InputSystem::LookOffset = glm::vec2(0, 0); // sets the offset back to 0 after moving to prevent continual input

	}
	void HorizontalMovement(float deltaTime) {
		
		// T0-Do : Convert to physics application
		_camera->Position += InputSystem::MovementInput.y * deltaTime * _camera->Forward * MovementSpeed;
		_camera->Position += InputSystem::MovementInput.x * deltaTime * _camera->Right * MovementSpeed;
	}


private:

	Camera* _camera;
	TransformComponent* _transform;

};

#endif