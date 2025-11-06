#include <iostream>

#include <glad/glad.h> 
#include "VAO.h"
#include "Shader.h"
#include "Texture.h"

// TODO : Turn Camera into class. It is made up of the part which creates the view matrix and, the parts which effect its local vectors.

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};


#pragma region Global Variables

// System
float currentFrameTime;
float lastFrameTime;
float deltaTime;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


// Camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// Camera Feature settings
float cameraFOV = 60;
float cameraPitch;
float cameraYaw;


// Input
bool firstMouseInput;
float mouseLastX = 400, mouseLastY = 300;



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

// Handles camera movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos) 
{
    if (firstMouseInput)
    {
        mouseLastX = xpos;
        mouseLastY = ypos;
        firstMouseInput = false;
    }

    float xoffset = xpos - mouseLastX;
    float yoffset = mouseLastY - ypos;
    mouseLastX = xpos;
    mouseLastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cameraYaw += xoffset;
    cameraPitch += yoffset;

    if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;
    if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    direction.y = sin(glm::radians(cameraPitch));
    direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    cameraForward = glm::normalize(direction);
}

// Scroll movement
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cameraFOV -= (float)yoffset;
    if (cameraFOV < 1.0f)
        cameraFOV = 1.0f;
    if (cameraFOV > 45.0f)
        cameraFOV = 45.0f;
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

    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos +=  cameraSpeed * cameraForward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -=  cameraSpeed * cameraForward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraForward, cameraUp)) *  cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraForward, cameraUp)) * cameraSpeed;

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
    
    // Mouse input callback assignment. camera movement
    glfwSetCursorPosCallback(mainWindow, mouse_callback);

    // Scroll callback assignment. Zoom capabilities.
    glfwSetScrollCallback(mainWindow, scroll_callback);

    // Enable Depth testing
    glEnable(GL_DEPTH_TEST);

    // Allows for alpha transparency.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Hide and capture cursor.
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#pragma endregion

#pragma endregion


    // Copies the vertex data to a buffer on the GPU.
#pragma region Vertex Buffer Object

    VBO vbo= VBO(vertices, sizeof(vertices));

#pragma endregion

    // Decides how a vertex buffer will be interpreted when drawring.
#pragma region Vertex Array Object

    VAO vao = VAO();

    // Configure array attributes
    vao.LinkVBO(vbo);

#pragma endregion

    // Creates and binds the Element buffer which will in turn be tied into the VAO which is currently bound.
#pragma region Element Buffer Object

    //// Bind vao so that the ebo can be linked into the vao for the next time it is called.
    //vao.Bind();

    //// Create an Element buffer object
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);

    //// Bind the new object and copy the "indicies" data over to that buffer with the correct "GL_ELEMENT_ARRAY_BUFFER" target.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //vao.Unbind();


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





    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, 15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, 3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, 2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, 1.5f)
    };






#pragma region Coordinate Space Transformations





#pragma endregion

    // initial Frame Time
    currentFrameTime = (float)glfwGetTime();

    // Render Loop
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Calculate Delta Time;
        lastFrameTime = currentFrameTime;
        currentFrameTime = (float)glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;

        processInput(mainWindow);

        // Rendering Commands here...
        glClearColor(0.22f, 0.45f, 0.22f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind textures to the correct Texture Unit
        glActiveTexture(GL_TEXTURE0);
        texture1.Bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.Bind();


        // Projection Matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(cameraFOV), 800.0f / 600.0f, 0.1f, 100.0f);

        // Camera View Matrix
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraForward, cameraUp);

        vao.Bind();

        for (unsigned int i = 0; i < 10; i++)
        {

            // create a new Model Matrix for each object, then Move and Rotate it.
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i + 1;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            // Send Transform Matricies to Vertex Shader
            ourShader.setMat4("model", model);
            ourShader.setMat4("view", view);
            ourShader.setMat4("projection", projection);
            

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        

        vao.Unbind();


        glfwSwapBuffers(mainWindow);// Swaps the rendered, back buffer, with the front buffer and displays it to the specified window
        glfwPollEvents(); // Checks for event updates such as user input, and calls any registered call-back functions

    }


    // Clean up all GLFW resources
    glfwTerminate();
    return 0;
}



   



