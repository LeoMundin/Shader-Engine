#pragma once
#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <iostream>

#include "glm/ext.hpp" // Provides glm::to_string function!
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../Events/Event.h"


class InputSystem 
{
public:

	static glm::vec2 LookOffset;
    static glm::vec2 MovementInput;
	static bool LeftMousePressed;

	static Event OnLeftMouseButtonDown;


	InputSystem(){};
	InputSystem(GLFWwindow* window) 
	{

		std::cout << "Input System Initalized " << std::endl;

        glfwSetKeyCallback(window, OnKeyCallback);
		glfwSetMouseButtonCallback(window, OnMouseButtonCallback);
		glfwSetCursorPosCallback(window, OnMousePosCallback); // Mouse Position : Camera movement
	}




private:

	static glm::vec2 _lastMousePos;

    static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void OnMouseButtonCallback(GLFWwindow* window,int button, int action, int mods);
	static void OnMousePosCallback(GLFWwindow* window, double xpos, double ypos);

	static void LeftMouseButtonDown();

};

#endif

