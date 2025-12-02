#pragma once
#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "TuftEngine.h"
#include "Component.h"
#include "TransfromComponent.h"
#include "Model.h"

class RenderComponent : public Component
{

public: 


	RenderComponent(TuftEngine engine, TransformComponent transformComponent, Model model, Shader shader) 
	{
		_engine = engine;
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


private: 
	TuftEngine _engine;
	TransformComponent _transfrom;

	Model _model;
	Shader _shader;

	glm::mat4 _modelMatrix = glm::mat4(1.0f);
	glm::mat4 _viewMatrix = glm::mat4(1.0f);
	glm::mat4 _projectionMatrix = glm::mat4(1.0f);




};

#endif