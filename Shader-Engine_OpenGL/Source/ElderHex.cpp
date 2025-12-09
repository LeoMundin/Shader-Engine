#include "ElderHex.h"


void ElderHex::OnAwake() {

    const char* backpackPath = "Assets/Models/backpack/backpack.obj";
    Model backpack(backpackPath);
    Shader ourShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
    bag.addComponent<RenderComponent>(&lightPos, &MainCamera, bag.Transform, backpack, ourShader);

    player.addComponent<RigidbodyComponent>(PhysicsWorld, player.Transform);
    
}

void ElderHex::OnUpdate() {
    // Move Light
    const float radius = 8.0f;
    float lightX = sin(glfwGetTime()) * radius;
    float lightZ = cos(glfwGetTime()) * radius;
    lightPos = glm::vec3(lightX, lightPos.y, lightZ);


    std::cout << glm::to_string(player.Transform->Position);

    bag.Update(DeltaTime);
    player.Update(DeltaTime);

}

void ElderHex::OnRender() {

    bag.Render();
    player.Render();

}