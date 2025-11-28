#include "TuftEngine.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1200;
TuftEngine engine = TuftEngine(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(){
    engine.StartEngine();
    return 0;

}





// Handles camera movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    float xoffset = xpos - engine.mouseLastX;
    float yoffset = engine.mouseLastY - ypos;
    engine.mouseLastX = xpos;
    engine.mouseLastY = ypos;

    engine.MainCamera.Look(xoffset, yoffset, true);

}



// Scroll wheel callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    engine.MainCamera.Zoom(yoffset);
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
        engine.MainCamera.Move(Camera::ECameraInput::SHIFT, engine.DeltaTime);

    // FORWARDS/BACKWARDS
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        engine.MainCamera.Move(Camera::ECameraInput::FORWARD, engine.DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        engine.MainCamera.Move(Camera::ECameraInput::BACKWARD, engine.DeltaTime);
    // STRAFE LEFT/RIGHT
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        engine.MainCamera.Move(Camera::ECameraInput::LEFT, engine.DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        engine.MainCamera.Move(Camera::ECameraInput::RIGHT, engine.DeltaTime);

    // UP/DOWN
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        engine.MainCamera.Move(Camera::ECameraInput::UP, engine.DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        engine.MainCamera.Move(Camera::ECameraInput::DOWN, engine.DeltaTime);

}






   



