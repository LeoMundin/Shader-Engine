#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

class Component 
{
public:
	Component() {};
	virtual ~Component() {}; // Destructor

	// Lifecycle hooks
	virtual void Update(float deltaTime) {};
	virtual void Render() {};

};


#endif
