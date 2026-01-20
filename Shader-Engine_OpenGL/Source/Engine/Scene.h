#pragma once
#ifndef SCENE_H
#define SCENE_H


#include <list>


class TuftEngine ;
class Scene 
{

public :

	// To-Do: bool IsComplete = false;

	std::string ID = "Scene";
	TuftEngine* Engine;
	rp3d::PhysicsWorld* PhysicSimulation;
	Scene() {};
	
	// Loads game objects into Scene. 
	virtual void Load(TuftEngine* enginePtr, rp3d::PhysicsWorld* physicsSim) {  // To-Do: Could be converted to read from file.
		Engine = enginePtr;
		PhysicSimulation = physicsSim;

		// Add GameObjects to scene list.
	}

	// Lifecycle hooks
	virtual void Awake() {}; // Runs once before Game loop starts.
	virtual void Update() {}; // Runs every frame to update game logic. 
	virtual void Render() {}; // Updates rendering every frame.
	virtual void RenderUI() {}; // Updates rendering for UI which whould be layered ontop of game, every frame.

	// To-Do: void Restart() {};

protected: 

	std::list<Entity> _sceneObjects;
	

	glm::vec3 _lightPosition = glm::vec3(0.0f, 100.0f, 0.0f);;
	Camera _mainCamera = Camera(glm::vec3(0));

	// To-Do: void Complete() {}; // Marks this scene as finished for the engine to move scene.

};

#endif SCENE_H