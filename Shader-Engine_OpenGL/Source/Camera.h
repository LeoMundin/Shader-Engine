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
    glm::vec3 position;
    glm::vec3 forward = glm::vec3(0, 0, -1);
    glm::vec3 up;
    glm::vec3 right;

    // Camera settings
    float fov = 60;
    float sensitivity = 0.1f;
    float pitch = 0; // Rotation around x
    float yaw = -90; // Rotation around y


    Camera(){};
    Camera(glm::vec3 pos, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
    {

        position = pos;

        up = glm::vec3(0,1,0);
        UpdateCameraForwards();

	}


    glm::mat4 GetCameraViewMatrix()
    {
        return glm::lookAt(position, position + forward, up);
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


    void Move(ECameraInput input, float deltaTime) {


        float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
        // BOOST SPEED
        if (input == SHIFT)
            cameraSpeed += cameraSpeed * 2;

        // FORWARDS/BACKWARDS
        if (input == FORWARD)
            position += cameraSpeed * forward;
        if (input == BACKWARD)
            position -= cameraSpeed * forward;
        // STRAFE LEFT/RIGHT
        if (input == LEFT)
            position -= right * cameraSpeed;
        if (input == RIGHT)
            position += right * cameraSpeed;

        // UP/DOWN
        if (input == UP)
            position += cameraSpeed * up;
        if (input == DOWN)
            position -= cameraSpeed * up;
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

    void UpdateCameraForwards() 
    {

        // Calculate new forward
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        // Update transform values
        forward = glm::normalize(direction);
        right = glm::normalize(glm::cross(forward, up));


    }


};


#endif