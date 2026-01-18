#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <typeindex>

#include "Component.h"

class Entity 
{
public:

	// TODO - Comment


	template <typename T, typename ... TArgs>
	T* AddComponent(TArgs&&... args) {
		auto component = std::make_shared<T>(std::forward<TArgs>(args)...);
		component->owner = this;
		_components[typeid(T)] = component;
		return component.get();
	}

	template <class T>
	T* GetComponent() {
		auto component = _components.find(typeid(T));    
		if (component == _components.end())
			return nullptr;

		return static_cast<T*>(component->second.get());
	}

	void Update(float deltaTime) {
		if (!_isActive) return;
		for (auto& component : _components) {
			component.second->Update(deltaTime);
		}
	};
	
	void Render() {
		if (!_isActive) return;
		for (auto& component : _components) {
			component.second->Render();
		}
	};

	void RenderUI() {
		if (!_isActive) return;
		for (auto& component : _components) {
			component.second->RenderUI();
		}
	};

	void Destroy() {
		_isActive = false;
	}


private:

	bool _isActive = true ;

	std::map<std::type_index, std::shared_ptr<Component>> _components;

};

#endif
