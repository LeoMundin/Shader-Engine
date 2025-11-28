#pragma once
#ifndef TUFTENGINE_H
#define TUFTENGINE_H

#include <iostream>

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <glad.h> 
#include "VAO.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"


class TuftEngine {

    public:

        // System
        float DeltaTime;

        // Screen
        GLFWwindow* MainWindow;
        unsigned int ScreenWidth;
        unsigned int ScreenHeight;

        // Camera
        Camera MainCamera;
        glm::vec3 CameraPos = glm::vec3(0.0f, 1.0f, 7.0f);

        // Input
        float mouseLastX;
        float mouseLastY;


        // Constructor
        TuftEngine() {};
        TuftEngine(unsigned int width, unsigned int height)
        {

            ScreenWidth = width;
            ScreenHeight = height;
            MainCamera = Camera(CameraPos, ScreenWidth, ScreenHeight);
            mouseLastX = ScreenWidth / 2;
            mouseLastY = ScreenHeight / 2;


            InitialiseGLFW();
            InitialiseGlad();

        }
        /// <summary>
        /// Starts the Game Engine loop initiating lifecycle hooks.
        /// </summary>
        void StartEngine() {
            _currentFrameTime = (float)glfwGetTime();
            while (!glfwWindowShouldClose(MainWindow)) {
                _currentFrameTime = (float)glfwGetTime();
                DeltaTime = _currentFrameTime - _lastFrameTime;
                ProcessInput();
                Update();
                Render();
                _lastFrameTime = _currentFrameTime;
            };
            glfwTerminate();
        }



        // External Lifecycle Methods
        void ProcessInput() { 
            OnProcessInput(MainWindow); 
            glfwPollEvents(); // Checks for event updates such as user input, and calls any registered call-back functions
        }
        void Update() { 
            _projectionMatrix = glm::perspective(glm::radians(MainCamera.fov), 800.0f / 600.0f, 0.1f, 100.0f);
            _viewMatrix = MainCamera.GetCameraViewMatrix();

            OnUpdate(); 
        }
        void Render() {
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            OnRender(); 
            
            glfwSwapBuffers(MainWindow);// Swaps the rendered, back buffer, with the front buffer to display rendered content.
        }


        // CALLBACK METHODS - NEED UPDATING FOR NEW SYSTEM
        /// <summary>
        /// A function that is called every time the GLFW window is re-sized, and re-sizes the OpenGL window accordingly.
        /// </summary>
        /// <param name="width"> The new width for the Render Window. </param>
        /// <param name="height"> The new height for the Render Window. </param>
        static void OnWindowResize(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
        static void OnMouseInput(GLFWwindow* window, double xpos, double ypos){}
        static void OnScroll(GLFWwindow* window, double xoffset, double yoffset){}
        static void processInput(GLFWwindow* window) {};


    private:

        // Transformation Matricies
        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;

        // Delta Time
        float _currentFrameTime;
        float _lastFrameTime;

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


    protected:

        virtual void SetGLFWCallbacks(GLFWwindow* window) {
                    glfwSetFramebufferSizeCallback(window, OnWindowResize);
                    glfwSetCursorPosCallback(window, OnMouseInput); // Mouse Position : Camera movement
                    glfwSetScrollCallback(window, OnScroll); // Scroll : Zoom.
        }
        virtual void DefineGLADSettings() {

                    glEnable(GL_DEPTH_TEST); // Depth Testing.

                    // Allows for alpha transparency.
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }

        // Internal Lifecycle methods
        virtual void OnProcessInput(GLFWwindow* window){}
        virtual void OnUpdate();
        virtual void OnRender();

};


#endif