#pragma once
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "reactphysics3d.h"

#include "../Component.h"
#include "TransformComponent.h"

class ColliderComponent : public Component
{
public:

	enum EColliderShape
	{
		BOX,
	};

	rp3d::Collider* Collider;

	ColliderComponent(rp3d::PhysicsCommon *physicsCommon,EColliderShape shape, rp3d::RigidBody *rigidbody, TransformComponent *transform, rp3d::Vector3 boxDimensions = rp3d::Vector3(1,1,1)) {
		switch (shape) {
			// To-Do: Convert to seperate classes
		case BOX:
			// Create the box shape
			rp3d::BoxShape* boxShape = physicsCommon->createBoxShape(boxDimensions);
			Collider = rigidbody->addCollider(boxShape, rigidbody->getTransform().identity());
			Collider->setUserData(this);

			break;
		}
	}


private:

};

#endif // COLLIDERCOMPONENT_H
