#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H


#include <queue>
#include "../../ElderHex.h"

/// <summary>
/// Creates a UI element with a set number of Health Bars.
/// </summary>
class HealthBar 
{
public:

	int MaxNumHealthBars;

	// Transform - 
	glm::vec2 Position;
	float Rotation = 0.0f;
	float Width, Height = 200.0f;

	// Visuals -
	float BarSpacing = 5.0f;
	glm::vec3 Colour = glm::vec3(1.0f, 0.0f, 0.0f);
	

	HealthBar() {};
	HealthBar(int numBars, float screenWidth,float screenHeight, glm::vec2 position = glm::vec2(0))
	{
		MaxNumHealthBars = numBars;
		Position = position;

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		// Set up sprite shader
		Shader spriteShader("Assets/Shaders/SpriteVertShader.vert", "Assets/Shaders/SpriteFragShader.frag");
		spriteShader.setBool("canLoadTexture", true);
		_healthBarSprite = SpriteRenderer(spriteShader);

		// Subscribe to event
		GameEventsManager::GetInstance()->OnTakeDamage.AddSubscriber([this](){ this->OnHealthReduction(); });

	};

	// Lifescycle Hooks
	void Render() {
		// Itterate, drwaring a new bar slightly to the right
		glm::vec2 nextBarPosition = Position;
		for (int i = 1; i <= MaxNumHealthBars; i++) {
			_healthBarSprite.DrawSprite(_screenWidth, _screenHeight, nextBarPosition, glm::vec2(Width,Height), Rotation, Colour, &_spriteTexture);
			nextBarPosition += glm::vec2(Width + BarSpacing, 0);

		}

	}

	void OnHealthReduction() {
	    std::cout << "Player took damage..." << std::endl;
		if (MaxNumHealthBars > 0) {

			MaxNumHealthBars -- ;
		}

	}
	void OnHealthReduction(int numBars) {
		if (MaxNumHealthBars > 0 && numBars <= MaxNumHealthBars) {
			MaxNumHealthBars -= numBars;
		}

	}

private:

	SpriteRenderer _healthBarSprite;
	int _currentNumHealthBars;

	int _screenWidth, _screenHeight;
	Texture _spriteTexture = Texture("Assets/Textures/red-heart.png", false);

};

#endif
