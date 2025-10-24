#include <iostream>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "VAO.h"

#pragma region Shader Code

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
                                 "}\0";


const char* fragmentShaderSource = "#version 330 core\n"
                                   "uniform vec4 ourColor;\n"
                                   "in vec4 vertexColor;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = ourColor;\n"
                                   "}\n";

#pragma endregion




float lefTriangleVertices[] = {
     -1.0f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
     -0.5f,  0.5f, 0.0f,

     
};

float rightTriangleVertices[]{
     0.0f, -0.5f, 0.0f,
     1.0f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f
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

    // Sets the initial size for the OpenGL rendering window. 
    // Then registers the "framebuffer_size_callback" function to the GLFW window; for whenever it gets resized.
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

#pragma endregion


    // Copies the vertex data to a buffer on the GPU.
#pragma region Vertex Buffer Object

    VBO vbo1 = VBO(lefTriangleVertices, sizeof(lefTriangleVertices));
    VBO vbo2 = VBO(rightTriangleVertices, sizeof(rightTriangleVertices));

#pragma endregion

    // Decides how a vertex buffer will be interpreted when drawring.
#pragma region Vertex Array Object

    VAO vao1,vao2 = VAO();

    // Configure array attributes
    vao1.LinkVBO(vbo1);
    vao2.LinkVBO(vbo2);

#pragma endregion

    // Creates and binds the Element buffer which will in turn be tied into the VAO which is currently bound.
#pragma region Element Buffer Object


    // Create an Element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // Bind the new object and copy the "indicies" data over to that buffer with the correct "GL_ELEMENT_ARRAY_BUFFER" target.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma endregion





    // Compiles the Vertex Shader.
#pragma region Vertex Shader

    // Creates our shader object and defines it as a Vertex Shader.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Our Shader code is then attached to the Shader Object which then gets compiled at runtime.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // We then check if the Shader compiled correctly.
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

#pragma endregion

    // Compiles the Fragment Shader.
#pragma region Fragment Shader

    // The same process is then repeated for the Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

    }

#pragma endregion

    // Links the shaders together so that their inputs and outputs match up for render calls.
#pragma region Shader Program

    // An ID is generated for our shader program.
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Our shaders are then attached together inside the shader program.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Our Specifed and set up shader program is then linked as the active shader program for future use.
    glLinkProgram(shaderProgram);

    // Then like always, we check this process has linked and been set up correctly.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Sets the created,linked and tested shader program as a part of the current render state.
   // glUseProgram(shaderProgram);

    // Now that the shader objects have been used and linked into the shader program, they can now be deleted to save memory space. <- not essential but recommended
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

#pragma endregion

    


    // Render Loop
    while (!glfwWindowShouldClose(mainWindow))
    {

        processInput(mainWindow);


        // Rendering Commands here...
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



        // Samples the time and varies the green value from 0-1 by time and a sine wave
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

        // Queries the uniform location on our shader program, with the name of the uniform variable.
        // Note: -1 from this query means it could not be found.
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        // Activate the shader then update the uniform at the position we found on our active shader program.
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);




        // Draw Rectangle.
        glUseProgram(shaderProgram);
        vao1.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        vao2.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        vao2.Unbind();
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(mainWindow);// Swaps the rendered, back buffer, with the front buffer and displays it to the specified window
        glfwPollEvents(); // Checks for event updates such as user input, and calls any registered call-back functions

    }


    // Clean up all GLFW resources
    glfwTerminate();
    return 0;
}



   



