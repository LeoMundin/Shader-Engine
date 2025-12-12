#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera 
{

public:

    // Defines several possible options for camera movement. 
    // Used as abstraction to stay away from window-system specific input methods
    enum ECameraInput {
        SHIFT,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };



    // Camera Transform
    glm::vec3 Position;
    glm::vec3 Forward = glm::vec3(0, 0, -1);
    glm::vec3 Up = glm::vec3(0, 1, 0);
    glm::vec3 Right;

    // Camera settings
    float fov = 60;
    float sensitivity = 0.1f;
    float pitch = 0; // Rotation around x
    float yaw = -90; // Rotation around y


    Camera(){};
    Camera(glm::vec3 pos)
    {
        Position = pos;
        UpdateCameraForwards();

	}


    glm::mat4 GetCameraViewMatrix()
    {
        return glm::lookAt(Position, Position + Forward, Up);
    }



    void Look(double xOffset, double yOffset, bool constrainedPitch)
    {

        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (constrainedPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        UpdateCameraForwards();

    }
    void Zoom(float yoffset)
    {
        fov -= (float)yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
    };



private:

    void UpdateCameraForwards(){
        // Calculate new forward
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        // Update transform values
        Forward = glm::normalize(direction);
        Right = glm::normalize(glm::cross(Forward, Up));

    }

};


#endif