#pragma once
#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "../Component.h"
#include "TransformComponent.h"
#include "../Engine/Core/Model_Loading/Model.h"
#include "Camera.h"


// TODO : Create Camera Component to Help Renderer Function Properly.
class RenderComponent : public Component
{

public: 

	RenderComponent(glm::vec3 *lightPos,Camera *renderCam, TransformComponent *transformComponent, Model model, Shader shader) 
	{
		_lightPos = lightPos;
		_renderCam = renderCam;
		_transfrom = transformComponent;
		_model = model;
		_shader = shader;

	}


	void Render() override {


		_modelMatrix = _transfrom->GetTransfromMatrix();
		_viewMatrix = _renderCam->GetCameraViewMatrix();
		_projectionMatrix = glm::perspective(glm::radians(_renderCam->fov), 800.0f / 600.0f, 0.1f, 500.0f);

		_shader.setMat4("model", _modelMatrix);
		_shader.setMat4("view", _viewMatrix);
		_shader.setMat4("projection", _projectionMatrix);

		// Implement lighting
		glm::vec3 camPos = _renderCam->Position;
		_shader.setVec3("viewPos", camPos.x,camPos.y,camPos.z);
		_shader.setVec3("lightPos", _lightPos->x, _lightPos->y,_lightPos->z);

		_model.Draw(_shader);

	}


private:

	Camera* _renderCam;
	TransformComponent* _transfrom;
	glm::vec3* _lightPos;

	Model _model;
	Shader _shader;

	// Transfrom Components
	glm::mat4 _modelMatrix = glm::mat4(1.0f);
	glm::mat4 _viewMatrix = glm::mat4(1.0f);
	glm::mat4 _projectionMatrix = glm::mat4(1.0f);



};

#endif