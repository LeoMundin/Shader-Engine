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



	RigidbodyComponent(rp3d::PhysicsWorld* physicsWorld, TransformComponent* transformComponent)
	{
		_physicsWorld = physicsWorld;
		_transformComponent = transformComponent;

		_rigidbodyTransform = rp3d::Transform(_position, _rotation);
		_rigidbody = _physicsWorld->createRigidBody(_rigidbodyTransform);
	}



private :
	rp3d::PhysicsWorld* _physicsWorld;
	TransformComponent* _transformComponent;
	rp3d::RigidBody* _rigidbody;

	rp3d::Transform _rigidbodyTransform;
	rp3d::Vector3 _position = _transformComponent->GLMVec3ToRp3dVector3(_transformComponent->Position);// needs to send orientation + position to transform, not other way around
	rp3d::Quaternion _rotation = _transformComponent->GlmQuatToRp3dQuat(_transformComponent->GetTransfromQuarternionRotation());



};

#endif // !RIGIDBODYCOMPONENT_H
