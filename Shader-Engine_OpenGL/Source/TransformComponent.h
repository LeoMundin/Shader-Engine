#pragma once
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glad.h> 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "reactphysics3d.h"

#include "Component.h"


class TransformComponent: public Component
{

public:
	glm::vec3 Position = glm::vec3(0,0,0);
	glm::vec3 Rotation = glm::vec3(0, 0, 0);
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

	glm::quat GetTransfromQuarternionRotation() {
		return glm::quat(Rotation);
	}
	/// <summary>
	/// Converts a glm Quarternion into a react physics 3D Quarternion
	/// </summary>
	/// <param name="glmQuat"> The GLM Quarternion to be converted. </param>
	rp3d::Quaternion GlmQuatToRp3dQuat(glm::quat glmQuat) {
		return rp3d::Quaternion(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);
	}

	/// <summary>
	/// Converts a glm vec3 into a react physics 3D Vector3
	/// </summary>
	/// <param name="glmQuat"> The GLM vec3 to be converted. </param>
	rp3d::Vector3 GLMVec3ToRp3dVector3(glm::vec3 glmVec3) {
		return rp3d::Vector3(glmVec3.x, glmVec3.y, glmVec3.z);
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
