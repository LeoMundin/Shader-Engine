#include "ElderHex.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1200;

ElderHex game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(){
    game.StartEngine();
    return 0;

}



// Handles camera movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    float xoffset = xpos - game.mouseLastX;
    float yoffset = game.mouseLastY - ypos;
    game.mouseLastX = xpos;
    game.mouseLastY = ypos;

    game.MainCamera.Look(xoffset, yoffset, true);

}



// Scroll wheel callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    game.MainCamera.Zoom(yoffset);
}



/// <summary>
/// Processes all of the relevant input events which occur within the given window.
/// </summary>
/// <param name="window"> The window from which to read the appropriate input events, </param>
void processInput(GLFWwindow* window)
{
    // Close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }


    // BOOST SPEED
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        game.MainCamera.Move(Camera::ECameraInput::SHIFT, game.DeltaTime);

    // FORWARDS/BACKWARDS
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        game.MainCamera.Move(Camera::ECameraInput::FORWARD, game.DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        game.MainCamera.Move(Camera::ECameraInput::BACKWARD, game.DeltaTime);
    // STRAFE LEFT/RIGHT
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        game.MainCamera.Move(Camera::ECameraInput::LEFT, game.DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        game.MainCamera.Move(Camera::ECameraInput::RIGHT, game.DeltaTime);

    // UP/DOWN
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        game.MainCamera.Move(Camera::ECameraInput::UP, game.DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        game.MainCamera.Move(Camera::ECameraInput::DOWN, game.DeltaTime);

}






   



