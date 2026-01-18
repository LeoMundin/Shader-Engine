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

// INTERNAL
#include "Core/Core.h"
#include "ECS/GameObject.h"
#include "Input/InputSystem.h"
#include "Events/Event.h"


class TuftEngine {

    public:


        // To-Do : Create game 



        // System
        float DeltaTime;

        // Screen
        GLFWwindow *MainWindow = nullptr;

        // Physics
        const float GRAVITY = -9.83f;
        rp3d::PhysicsCommon PhysicsCommon;
        rp3d::PhysicsWorld* PhysicsWorld;


        // Camera
        Camera MainCamera; // TO:Do Turn into entity
        glm::vec3 CameraPos = glm::vec3(0.0f, 5.0f, 10.0f);
        glm::vec3 lightPos = glm::vec3(0.0f, 100.0f, 0.0f);

        // Input
        InputSystem Input;

       
        // Constructor
        TuftEngine() {};
        TuftEngine(unsigned int width, unsigned int height)
        {

            ScreenWidth = width;
            ScreenHeight = height;
            MainCamera = Camera(CameraPos);

            InitialiseGLFW();
            InitialiseGlad();

            // Create Physics world with appropriate settings.
            settings.defaultVelocitySolverNbIterations = 20;
            settings.isSleepingEnabled = false;
            settings.gravity = rp3d::Vector3(0, GRAVITY, 0);
            PhysicsWorld = PhysicsCommon.createPhysicsWorld(settings);


        }


        /// <summary>
        /// Starts the Game Engine loop initiating lifecycle hooks.
        /// </summary>
        void init() {
            _currentFrameTime = (float)glfwGetTime();

            Awake();

            while (!glfwWindowShouldClose(MainWindow)) {
                _currentFrameTime = (float)glfwGetTime();
                DeltaTime = _currentFrameTime - _lastFrameTime;

                ProcessInput();
                Update(); // Move to Game
                Render();

                _lastFrameTime = _currentFrameTime;
            };
            glfwTerminate();

        }


        // CALLBACK METHODS - NEED UPDATING FOR NEW SYSTEM
        static void OnWindowResize(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

        unsigned int GetScreenWidth() {return ScreenWidth;};
        unsigned int GetScreenHeight() {return ScreenHeight;};
       

    private:
        // Physics world settings object
        rp3d::PhysicsWorld::WorldSettings settings;

        unsigned int ScreenWidth;
        unsigned int ScreenHeight;

        void InitialiseGLFW() {
                // GLFW Libary settings
                glfwInit();
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                MainWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, "Shader Engine", NULL, NULL);
                if (MainWindow == NULL)
                {
                    std::cout << "Failed to create GLFW window" << std::endl;
                    glfwTerminate();
                    return;
                }
                glfwMakeContextCurrent(MainWindow);

                glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// Hide and capture cursor.
                SetGLFWCallbacks(MainWindow);

        }
        void InitialiseGlad(){
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    std::cout << "Failed to initialize GLAD" << std::endl;
                    return;
                }
                // Sets the initial size for the OpenGL rendering window. 
                glViewport(0, 0, ScreenWidth, ScreenHeight);

                DefineGLADSettings();

        }

        // Internal Lifecycle Methods
        void ProcessInput() {
            glfwPollEvents(); // Checks for event updates such as user input, and calls any registered call-back functions
        }
        void Awake(){
            OnAwake();
        }
        void Update() {
            OnUpdate();
            PhysicsWorld->update(DeltaTime);
        }
        void Render() {
            glClearColor(0.388f, 0.588f, 0.684f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            OnRender();

            // Clear depth information and draw UI ontop of 3D elements
            glClear(GL_DEPTH_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);
            glDepthMask(GL_FALSE);
            OnRenderUI();
            glDepthMask(GL_TRUE);
            glEnable(GL_DEPTH_TEST);

            glfwSwapBuffers(MainWindow);// Swaps the rendered, back buffer, with the front buffer to display rendered content.
        }


    protected:
        // Delta Time
        float _currentFrameTime;
        float _lastFrameTime;

        virtual void SetGLFWCallbacks(GLFWwindow* window) {
                    glfwSetFramebufferSizeCallback(window, OnWindowResize);
                    Input = InputSystem(MainWindow);

        }
        virtual void DefineGLADSettings() {

                    glEnable(GL_DEPTH_TEST); // Depth Testing.

                    // Allows for alpha transparency.
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        // External Lifecycle Hooks
        virtual void OnAwake() {}; // Runs once before Game loop starts.
        virtual void OnUpdate() {}; // Runs every frame to update game logic.
        virtual void OnRender() {}; // Updates rendering every frame.
        virtual void OnRenderUI() {}; // Updates rendering for UI which whould be layered ontop of game, every frame.

};


#endif