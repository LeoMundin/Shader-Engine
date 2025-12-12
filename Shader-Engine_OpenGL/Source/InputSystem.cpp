#include "Header/InputSystem.h"


glm::vec2 InputSystem::LookOffset = glm::vec2(0,0) ;
glm::vec2 InputSystem::MovementInput = glm::vec2(0,0) ;
bool InputSystem::LeftMousePressed = false;

glm::vec2 InputSystem::_lastMousePos = glm::vec2(0,0) ;


void InputSystem::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{



    MovementInput = glm::vec2(0, 0);
    // FORWARDS/BACKWARDS
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) MovementInput.y += 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) MovementInput.y -= 1;
    // STRAFE LEFT/RIGHT
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) MovementInput.x -= 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) MovementInput.x += 1;

}
void InputSystem::OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    LeftMousePressed = false;
    LeftMousePressed = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ;
};

void InputSystem::OnMousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
    LookOffset = glm::vec2(0, 0);
    float xoffset = xpos - _lastMousePos.x;
    float yoffset = _lastMousePos.y - ypos;
    _lastMousePos.x = xpos;
    _lastMousePos.y = ypos;
    
    LookOffset = glm::vec2(xoffset, yoffset);
   

};






