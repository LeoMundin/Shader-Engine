#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

class Component 
{
public:
	Component() {};
	virtual ~Component() {}; // Destructor

	// Lifecycle hooks
	virtual void Update() {};
	virtual void Render() {};

};


#endif
