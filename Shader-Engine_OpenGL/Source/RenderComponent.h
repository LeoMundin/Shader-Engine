#pragma once
#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "TuftEngine.h"
#include "Component.h"
#include "TransformComponent.h"
#include "Model.h"
#include "Camera.h"


// TODO : Create Camera Component to Help Renderer Function Properly.

class RenderComponent : public Component
{

private:
	TuftEngine _engine ;
	Camera _renderCam;
	TransformComponent _transfrom;

	Model _model;
	Shader _shader;

	glm::mat4 _modelMatrix = glm::mat4(1.0f);
	glm::mat4 _viewMatrix = glm::mat4(1.0f);
	glm::mat4 _projectionMatrix = glm::mat4(1.0f);




public: 


	RenderComponent(TuftEngine engine,Camera renderCam, TransformComponent transformComponent, Model model, Shader shader) 
	{
		_engine = engine;
		_renderCam = renderCam;
		_transfrom = transformComponent;
		_model = model;
		_shader = shader;

	}

	void Render() override {
		_modelMatrix = _transfrom.GetTransfromMatrix();
		_viewMatrix = _engine.GetViewMatrix();
		_projectionMatrix = _engine.GetProjectionMatrix();

		_shader.setMat4("model", _modelMatrix);
		_shader.setMat4("view", _viewMatrix);
		_shader.setMat4("projection", _projectionMatrix);

		_model.Draw(_shader);

	}





};

#endif