#include "TuftEngine.h"




//bag->addComponent<RenderComponent>(this, transform, backpack, ourShader);

// Backpack
const char* backpackPath = "Assets/Models/backpack/backpack.obj";
Model backpack(backpackPath);
Shader ourShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
glm::mat4 objectModel = glm::mat4(1.0f);


// Light object
const char* cubePath = "Assets/Models/Primatives/cube.obj";
Model cube(cubePath);
Shader lightShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/LightFragmentShader.frag");
glm::vec3 lightPos = glm::vec3(1.0f, 3.0f, 1.0f);
glm::mat4 lightModel = glm::mat4(1.0f);


//------------------------------------------- ENGINE CODE -------------------------------------------------------

void TuftEngine::OnUpdate()
{
   
    std::cout << glm::to_string(transform->Position);
    transform->Position += glm::vec3(1);
    // Move Light
    const float radius = 8.0f;
    float lightX = sin(glfwGetTime()) * radius;
    float lightZ = cos(glfwGetTime()) * radius;
    lightPos = glm::vec3(lightX, lightPos.y, lightZ);
}


void TuftEngine::OnRender()
{
    // Reset to prevent accumulation
    objectModel = glm::mat4(1.0f);
    lightModel = glm::mat4(1.0f);


    // Lit OBJECT -------------------------------------------------
    ourShader.useProgram();

    // Transform
    objectModel = glm::translate(objectModel, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    objectModel = glm::scale(objectModel, glm::vec3(1));	// it's a bit too big for our scene, so scale it down
    ourShader.setMat4("model", objectModel);
    ourShader.setMat4("view", _viewMatrix);
    ourShader.setMat4("projection", _projectionMatrix);

    // Lighting
    ourShader.setVec3("viewPos", CameraPos.x, CameraPos.y, CameraPos.z);
    ourShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

    backpack.Draw(ourShader);


    // LIGHT OBJECT -------------------------------------------------
    lightShader.useProgram();

    // Transform
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));
    lightShader.setMat4("model", lightModel);
    lightShader.setMat4("view", _viewMatrix);
    lightShader.setMat4("projection", _projectionMatrix);

    cube.Draw(lightShader);


}
