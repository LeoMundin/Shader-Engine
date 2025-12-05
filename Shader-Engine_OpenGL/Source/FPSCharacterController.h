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

	float MovementSpeed = 2.5f;

	FPSCharacterController(Camera* renderCam) 
	{
		_camera = renderCam;
	};

	void Update(float deltaTime) override {
		CameraLook();
		HorizontalMovement(deltaTime);
	}

	void CameraLook() {

		_camera->Look(InputSystem::LookOffset.x, InputSystem::LookOffset.y, true);
		InputSystem::LookOffset = glm::vec2(0, 0); // sets the offset back to 0 after moving to prevent continual input

	}
	void HorizontalMovement(float deltaTime) {
		
		_camera->position += InputSystem::MovementInput.y * deltaTime * _camera->forward * MovementSpeed;
		_camera->position += InputSystem::MovementInput.x * deltaTime * _camera->right * MovementSpeed;
	}


private:

	Camera* _camera;

};

#endif