#pragma once
#ifndef TUFTENGINE_H
#define TUFTENGINE_H

// EXTERNAL
#include <iostream>
#include "glm/ext.hpp" // Provides glm::to_string function!
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <glad.h> 
#include "reactphysics3d/reactphysics3d.h"
#include <unordered_map>
#include <queue>
#include <list>

// INTERNAL
#include "Core/Core.h"
#include "ECS/GameObject.h"
#include "Input/InputSystem.h"
#include "Events/Event.h"
#include "Scene.h"


/// <summary>
/// Initialises a OpenGL and a render window, in which it can manage scenes in a game.
/// </summary>
class TuftEngine {

    public:


        // Screen
        GLFWwindow *Window = nullptr;

        // Physics
        rp3d::PhysicsCommon Physics;
        rp3d::PhysicsWorld::WorldSettings PhysicsSettings;
        const float GRAVITY = -9.83f;
        float DeltaTime;

        // Input
        InputSystem Input;

        TuftEngine() {};
        TuftEngine(unsigned int width, unsigned int height);

        void init(); // Boots up the game engine

        // Scene Management
        void AddScene(Scene *scene);
        Scene* GetScene(std::string sceneName);
        std::string GetNextSceneID();

        static void OnWindowResize(GLFWwindow* window, int width, int height);
        unsigned int GetScreenWidth() {return _screenWidth;};
        unsigned int GetScreenHeight() {return _screenHeight;};
       


    private:

        Scene* _activeScene; // Scene currently being played
        std::unordered_map<std::string, Scene*> _LoadedScenes; // all the scenes stored loaded into the engine
        std::queue<std::string> _sceneLoadOrder; // The ID of the loaded scenes in the order they were added


        unsigned int _screenWidth;
        unsigned int _screenHeight;

        void InitialiseGLFW();
        void InitialiseGlad();

        // Lifecycle Hooks
        void ProcessInput();
        void Awake();
        void Update();
        void Render();




    protected:

        // Delta Time
        float _currentFrameTime;
        float _lastFrameTime;

        virtual void SetGLFWCallbacks();
        virtual void DefineGLADSettings();

};


#endif