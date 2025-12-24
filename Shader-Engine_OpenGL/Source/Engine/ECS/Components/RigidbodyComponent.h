#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include "reactphysics3d.h"

#include "../Component.h"
#include "TransformComponent.h"


class RigidbodyComponent : public Component
{
public : 

	rp3d::RigidBody *Rigidbody;

	RigidbodyComponent(rp3d::PhysicsWorld *physicsWorld, TransformComponent *transformComponent)
	{
		_physicsWorld = physicsWorld;
		_transformComponent = transformComponent;

		Rigidbody = _physicsWorld->createRigidBody(_transformComponent->GetPhysicsTransform());
		Rigidbody->setType(rp3d::BodyType::DYNAMIC);

	}

	void  Render() override {
		_transformComponent->SetPhysicsTransform(Rigidbody->getTransform());
	}


	void SetGravity(bool enabledStatus) {
		// Disable gravity for this body
		Rigidbody->enableGravity(enabledStatus);
	}


private :
	rp3d::PhysicsWorld* _physicsWorld;
	TransformComponent* _transformComponent;


};

#endif // !RIGIDBODYCOMPONENT_H
