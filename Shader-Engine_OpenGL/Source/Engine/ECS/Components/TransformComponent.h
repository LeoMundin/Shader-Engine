#pragma once
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "reactphysics3d.h"
#include <glad.h> 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../Component.h"


class TransformComponent: public Component
{

public:
	glm::vec3 Position = glm::vec3(0,0,0);
	glm::quat Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
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

	// Physics
	rp3d::Transform GetPhysicsTransform() {
		// Create rp3d Position and rotation from transform components position and rotation
		rp3d::Vector3 position = Vector3GlmToRp3d(Position);
		rp3d::Quaternion rotation = QuarternionGlmToRp3d(Rotation);

		return rp3d::Transform(position, rotation);
	}
	void SetPhysicsTransform(rp3d::Transform trans) {
		// Convert rp3d variables to glm then pass them to the transform component
		Position = Vector3Rp3dToGlm(trans.getPosition());
		Rotation = QuarternionRp3dToGlm(trans.getOrientation());

	}

	// Quarternion Conversion
	rp3d::Quaternion QuarternionGlmToRp3d(glm::quat glmQuat) {
		return rp3d::Quaternion(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);
	}
	glm::quat QuarternionRp3dToGlm(rp3d::Quaternion rp3dQuat) {
		return glm::quat(rp3dQuat.w, rp3dQuat.x, rp3dQuat.y, rp3dQuat.z);
	}

	// Vector Conversion
	glm::vec3 Vector3Rp3dToGlm(rp3d::Vector3 rp3dVec3) {
		return glm::vec3(rp3dVec3.x, rp3dVec3.y, rp3dVec3.z);
	}
	rp3d::Vector3 Vector3GlmToRp3d(glm::vec3 glmVec3) {

		return rp3d::Vector3(glmVec3.x, glmVec3.y, glmVec3.z);
	}


private:
	glm::mat4 _transformMatrix;

	void UpdateTransfromMatrix() {
		_transformMatrix = glm::mat4(1.0f);
		_transformMatrix = glm::translate(_transformMatrix, Position);
		_transformMatrix *= glm::mat4_cast(glm::normalize(Rotation));
		_transformMatrix = glm::scale(_transformMatrix, Scale);
	}


	// Physics Helper functions



};

#endif
