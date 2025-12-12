#pragma once
#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"
#include "GameObject.h"

class HealthComponent : public Component
{

public:

	float MaxHealth;

	HealthComponent(float maxHealth)
	{
		MaxHealth = maxHealth;
		_currentHealth = MaxHealth;
	}



	void TakeDamage(float damage) {
		OnTakeDamage();
		_currentHealth -= damage;
		ValidateCurrentHealth();

	}

	// Lifecycle Methods 
	void Update(float deltaTime) override {
		ValidateCurrentHealth();
	}


private:

	float _currentHealth;

	void ValidateCurrentHealth() {
		if (_currentHealth <= 0) {
			Die();
		}
	}

	// Private to prevent accidental destruction of entity.
	void Die() {
		OnDie();
		this->owner->Destroy(); // Disable owining entity
	}


protected:

	// Virtual functions to call child specific functionality such as particle effects or animations.
	virtual void OnTakeDamage() {} 
	virtual void OnDie() {}


};


#endif