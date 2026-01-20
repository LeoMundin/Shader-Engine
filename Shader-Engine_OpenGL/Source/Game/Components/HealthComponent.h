#pragma once
#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "../../Engine/TuftEngine.h"

class HealthComponent : public Component
{

public:

	int MaxHealth;

	HealthComponent(int maxHealth)
	{
		MaxHealth = maxHealth;
		_currentHealth = MaxHealth;
	}

	void TakeDamage(int damage) {
		OnTakeDamage();
		_currentHealth -= damage;
		ValidateCurrentHealth();

	}

	// Lifecycle Methods 
	void Update(float deltaTime) override {
		ValidateCurrentHealth();
	}


private:

	int _currentHealth;

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