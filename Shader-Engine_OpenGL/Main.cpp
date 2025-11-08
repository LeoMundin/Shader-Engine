#include <iostream>

#include <glad/glad.h> 
#include "VAO.h"
#include "Shader.h"
#include "Texture.h"

// TODO : Turn Camera into class. It is made up of the part which creates the view matrix and, the parts which effect its local vectors.

glm::vec3 lightPos = glm::vec3(1.0f, 3.0f, 1.0f);

float lightVertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

float vertices[] = {
    // positions          // texcoords // normals
    // back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

    // front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

    // left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

    // right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

     // bottom face
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

     // top face (FIXED)
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
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

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1200;


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
float mouseLastX = SCREEN_WIDTH/2 , mouseLastY = SCREEN_HEIGHT/2 ;



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


    float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    // BOOST SPEED
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed += cameraSpeed * 2;
    // FORWARDS/BACKWARDS
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos +=  cameraSpeed * cameraForward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -=  cameraSpeed * cameraForward;
    // STRAFE LEFT/RIGHT
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraForward, cameraUp)) *  cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraForward, cameraUp)) * cameraSpeed;
    // UP/DOWN
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;

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

    // Hide and capture cursor.
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Mouse input callback assignment. camera movement
    glfwSetCursorPosCallback(mainWindow, mouse_callback);

    // Scroll callback assignment. Zoom capabilities.
    glfwSetScrollCallback(mainWindow, scroll_callback);



    // Enable Depth testing
    glEnable(GL_DEPTH_TEST);

    // Allows for alpha transparency.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



#pragma endregion

#pragma endregion


    // Copies the vertex data to a buffer on the GPU.
#pragma region Vertex Buffer Object

    VBO vbo= VBO(vertices, sizeof(vertices));
    VBO lightVBO= VBO(lightVertices, sizeof(lightVertices));


#pragma endregion

    // Decides how a vertex buffer will be interpreted when drawring.
#pragma region Vertex Array Object

    VAO vao = VAO();

    // Configure array attributes
    vao.LinkVBO(vbo);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    lightVBO.Bind();
    // set the vertex attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightVBO.Unbind();

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
    // Create a shader for rendering light objects
    Shader lightShader("VertexShader.vert", "LightFragmentShader.frag");

    ourShader.useProgram();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    ourShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    // Bind textures to the correct Texture Unit
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glActiveTexture(GL_TEXTURE1);
    texture2.Bind();








    // initial Frame Time
    currentFrameTime = (float)glfwGetTime();
    // Render Loop
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Rendering Commands here...
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate Delta Time;
        lastFrameTime = currentFrameTime;
        currentFrameTime = (float)glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;


        // Input Handling
        processInput(mainWindow);
        glfwPollEvents(); // Checks for event updates such as user input, and calls any registered call-back functions


#pragma region Transform Matrices

        // Model Matrix
        glm::mat4 model = glm::mat4(1.0f);
        
        // Projection Matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(cameraFOV), 800.0f / 600.0f, 0.1f, 100.0f);

        // Camera View Matrix
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraForward, cameraUp);

#pragma endregion



#pragma region Render Objects


        const float radius = 8.0f;
        float lightX = sin(glfwGetTime()) * radius;
        float lightZ = cos(glfwGetTime()) * radius;
        lightPos = glm::vec3(lightX, lightPos.y, lightZ);
        

        // LIT OBJECT --------------------------------------------------
        ourShader.useProgram();


        vao.Bind();

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        ourShader.setVec3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
        ourShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

        // send transform matricies to vertex shader
        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        vao.Unbind();



        // LIGHT OBJECT -------------------------------------------------
        lightShader.useProgram();
        glBindVertexArray(lightVAO);

        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        // send transform matricies to vertex shader
        lightShader.setMat4("model", model);
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        


#pragma endregion

        // Swaps the rendered, back buffer, with the front buffer to display previous content.
        glfwSwapBuffers(mainWindow);

    }


    // Clean up all GLFW resources
    glfwTerminate();
    return 0;
}




   



