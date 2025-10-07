#include <iostream>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>


int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;




/// <summary>
/// A function that is called every time the GLFW window is re-sized, and re-sizes the OpenGL window accordingly.
/// </summary>
/// <param name="width"> The new width for the Render Window. </param>
/// <param name="height"> The new height for the Render Window. </param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{

    // Set Up GLFW for window rendering
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Creates a window object, 
    // Checks that the window has been created succesfully,
    // then sets this window as the main context on the current thread.
    GLFWwindow* mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (mainWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(mainWindow);


    // Instantializes GLAD to allow us to use OpenGls functions easier.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    // Sets the initial size for the OpenGL rendering window.
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Register the "framebuffer_size_callback" function to the GLFW window; for whenever it gets resized.
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

    return 0;
}



   



