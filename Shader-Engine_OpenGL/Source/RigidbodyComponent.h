#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include "reactphysics3d.h"
#include <glad.h> 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Component.h"
#include "TransformComponent.h"

class RigidbodyComponent : public Component
{
public : 



	RigidbodyComponent(rp3d::PhysicsWorld *physicsWorld, TransformComponent *transformComponent)
	{
		_physicsWorld = physicsWorld;
		_transformComponent = transformComponent;

		// Create rp3d Position and rotation from transform components position and rotation
		rp3d::Vector3 position = Vector3GlmToRp3d(_transformComponent->Position);
		rp3d::Quaternion rotation = QuarternionGlmToRp3d(_transformComponent->Rotation);

		_rigidbody = _physicsWorld->createRigidBody(rp3d::Transform(position, rotation));

	}

	void  Render() override {
		UpdateTransformComponent();
	}

	void UpdateTransformComponent() {
		// Convert rp3d variables to glm then pass them to the transform component
		rp3d::Transform trans = _rigidbody->getTransform();
		_transformComponent->Position = Vector3Rp3dToGlm(trans.getPosition());
		_transformComponent->Rotation = QuarternionRp3dToGlm(trans.getOrientation());
	}



	// Helper Methods


	// Quarternion Conversion
	rp3d::Quaternion QuarternionGlmToRp3d(glm::quat glmQuat) {
		return rp3d::Quaternion(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);
	}
	glm::quat QuarternionRp3dToGlm(rp3d::Quaternion rp3dQuat) {
		return glm::quat(rp3dQuat.x, rp3dQuat.y, rp3dQuat.z, rp3dQuat.w);
	}

	// Vector Conversion
	glm::vec3 Vector3Rp3dToGlm(rp3d::Vector3 rp3dVec3) {
		return glm::vec3(rp3dVec3.x, rp3dVec3.y, rp3dVec3.z);
	}
	rp3d::Vector3 Vector3GlmToRp3d(glm::vec3 glmVec3) {

		return rp3d::Vector3(glmVec3.x, glmVec3.y, glmVec3.z);
	}



private :
	rp3d::PhysicsWorld* _physicsWorld;
	TransformComponent* _transformComponent;
	rp3d::RigidBody* _rigidbody;




};

#endif // !RIGIDBODYCOMPONENT_H
