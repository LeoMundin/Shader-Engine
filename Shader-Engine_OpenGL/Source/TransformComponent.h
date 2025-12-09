#pragma once
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glad.h> 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Component.h"


class TransformComponent: public Component
{

public:
	glm::vec3 Position = glm::vec3(0,0,0);
	glm::quat Rotation = glm::vec3(0, 0, 0);
	glm::vec3 Scale = glm::vec3(1,1,1);

	TransformComponent() {};
	TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;

		UpdateTransfromMatrix();
	}
	~TransformComponent() {};
#

	// Lifecycle Methods
	void Update(float deltaTime) override {
		UpdateTransfromMatrix();
	}


	// Helper Methods
	glm::mat4 GetTransfromMatrix() {
		UpdateTransfromMatrix();

		return _transformMatrix;
	}



private:
	glm::mat4 _transformMatrix;

	void UpdateTransfromMatrix() {
		_transformMatrix = glm::mat4(1.0f);
		_transformMatrix = glm::translate(_transformMatrix, Position);
		_transformMatrix = glm::rotate(_transformMatrix, Rotation.x, glm::vec3(1, 0, 0));
		_transformMatrix = glm::rotate(_transformMatrix, Rotation.y, glm::vec3(0, 1, 0));
		_transformMatrix = glm::rotate(_transformMatrix, Rotation.z, glm::vec3(0, 0, 1));
		_transformMatrix = glm::scale(_transformMatrix, Scale);
	}

};

#endif
