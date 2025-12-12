#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Entity.h"
#include "TransformComponent.h"

class GameObject : public Entity 
{
public :

	TransformComponent* Transform;

	GameObject() 
	{
		Transform = this->addComponent<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1));
	}


};


#endif
