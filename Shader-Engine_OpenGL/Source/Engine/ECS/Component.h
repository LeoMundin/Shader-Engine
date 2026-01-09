#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H


class Entity;
class Component 
{
public:

	Entity* owner = nullptr;

	Component() {};
	virtual ~Component() {}; // Destructor

	// Lifecycle hooks
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
	virtual void RenderUI() {};

};


#endif
