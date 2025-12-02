#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <memory>


#include "Component.h"

class Entity 
{
public:

	// TODO - Implement hash table to store components with ID for easy look up.

	template <typename T, typename ... TArgs>
	T* addComponent(TArgs&&... args) {
		auto component = std::make_shared<T>(std::forward<TArgs>(args)...);
		_components.emplace_back(component);
		return component.get();
	}


	// TO DO : implement a get component function

	void Update(float deltaTime) {
		for (auto& component : _components) {
			component->Update(deltaTime);
		}
	};
	
	void Render() {
		for (auto& component : _components) {
			component->Render();
		}
	};

private:
	std::vector<std::shared_ptr<Component>> _components;
};

#endif
