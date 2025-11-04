#include <iostream>

#include <glad/glad.h> 
#include "VAO.h"
#include "Shader.h"
#include "Texture.h"

float currentMixAmmount = 0.2;

float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};

float colourTriangle[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f    // top 
};

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

//rectangle
float rectangleVertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};


#pragma region Global Variables

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#pragma endregion


//------------------------------------------- HELPER FUNCTIONS -------------------------------------------------------


/// <summary>
/// A function that is called every time the GLFW window is re-sized, and re-sizes the OpenGL window accordingly.
/// </summary>
/// <param name="width"> The new width for the Render Window. </param>
/// <param name="height"> The new height for the Render Window. </param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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



}


//------------------------------------------- ENGINE CODE -------------------------------------------------------


int main()
{

    // Enables the correct libaries with the right settings and, creates a window for rendering.
#pragma region Libary & Window Setup

    // Set Up GLFW for window rendering
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    // Creates a window object, 
    // Checks that the window has been created succesfully,
    // then sets this window as the main context on the current thread.
    GLFWwindow* mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shader Engine" , NULL, NULL);
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


#pragma region Enable Additional Settings

    // Sets the initial size for the OpenGL rendering window. 
    // Then registers the "framebuffer_size_callback" function to the GLFW window; for whenever it gets resized.
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

    // Allows for alpha transparency.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma endregion

#pragma endregion


    // Copies the vertex data to a buffer on the GPU.
#pragma region Vertex Buffer Object

    VBO vbo = VBO(vertices, sizeof(vertices));

#pragma endregion

    // Decides how a vertex buffer will be interpreted when drawring.
#pragma region Vertex Array Object

    VAO vao = VAO();

    // Configure array attributes
    vao.LinkVBO(vbo);

#pragma endregion

    // Creates and binds the Element buffer which will in turn be tied into the VAO which is currently bound.
#pragma region Element Buffer Object

    // Bind vao so that the ebo can be linked into the vao for the next time it is called.
    vao.Bind();

    // Create an Element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // Bind the new object and copy the "indicies" data over to that buffer with the correct "GL_ELEMENT_ARRAY_BUFFER" target.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    vao.Unbind();

#pragma endregion


#pragma region Texture Object

    Texture texture1 = Texture("container.jpg");
    Texture texture2 = Texture("awesomeface.png", true);


#pragma endregion




    // Create a basic shader for rendering our objects
    Shader ourShader("VertexShader.vert", "FragmentShader.frag");

    ourShader.useProgram();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    

    // Render Loop
    while (!glfwWindowShouldClose(mainWindow))
    {

        processInput(mainWindow);


        if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
        {
            currentMixAmmount += 0.0001f; // change this value accordingly (might be too slow or too fast based on system hardware)
            if (currentMixAmmount >= 1.0f)
                currentMixAmmount = 1.0f;
        }
        else if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
        {
            currentMixAmmount -= 0.0001f; // change this value accordingly (might be too slow or too fast based on system hardware)
            if (currentMixAmmount <= 0.0f)
                currentMixAmmount = 0.0f;
        }




        // Rendering Commands here...
        glClearColor(0.22f, 0.45f, 0.22f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        texture1.Bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.Bind();

        ourShader.useProgram();
        ourShader.setFloat("xOffset", 0);
        
        ourShader.setFloat("mixAmount", currentMixAmmount);

        vao.Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        // Draw Rectangle.
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.Unbind();

        


        glfwSwapBuffers(mainWindow);// Swaps the rendered, back buffer, with the front buffer and displays it to the specified window
        glfwPollEvents(); // Checks for event updates such as user input, and calls any registered call-back functions

    }


    // Clean up all GLFW resources
    glfwTerminate();
    return 0;
}



   



