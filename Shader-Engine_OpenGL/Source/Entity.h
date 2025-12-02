#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include "Component.h"

class Entity 
{
public:


	template <typename T, typename ... TArgs>
	T* addComponent(TArgs&&... args) {
		auto component = std::make_shared<T>(std::forward<TArgs>(args)...);
		_components.emplace_back(component);
		return component.get();
	}

	void Update() {
		for (auto& component : _components) {
			component->Update();
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
