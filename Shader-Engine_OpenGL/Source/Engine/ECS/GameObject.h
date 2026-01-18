#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Entity.h"
#include "Components/TransformComponent.h"

// Additional Components
#include "Components/RenderComponent.h"
#include "Components/RigidbodyComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/CameraComponent.h"

class GameObject : public Entity 
{
public :

	TransformComponent* Transform;

	GameObject() 
	{
		Transform = this->AddComponent<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1));
	}


};


#endif
