#include "ElderHex.h"
//
// 
// TO-DO Move all this informatation into seperate scene objects which take in lifecycle methods
//
//

// Enables game events manager.
//
SpriteRenderer Renderer;
Texture* SpriteTexture;

SpriteRenderer CrossHair;

void ElderHex::OnAwake() {
    //PhysicsWorld->setGravity(rp3d::Vector3(0, -0.2, 0));
    TerrainGameObject = Terrain(&MainCamera, PhysicsWorld, &lightPos, &PhysicsCommon);
    Dummy = TargetDummy(&MainCamera, PhysicsWorld, &lightPos, &PhysicsCommon);
    spikes = Trap(&MainCamera, PhysicsWorld, &lightPos, &PhysicsCommon);


    Shader spriteShader("Assets/Shaders/SpriteVertShader.vert", "Assets/Shaders/SpriteFragShader.frag");
    spriteShader.setBool("canLoadTexture", true);
    CrossHair = SpriteRenderer(spriteShader);

    PlayerGameObject = Player(&MainCamera, PhysicsWorld,GetScreenWidth(),GetScreenHeight());
    PlayerGameObject.AddComponent<ColliderComponent>(&PhysicsCommon, ColliderComponent::EColliderShape::BOX, PlayerGameObject.Rigidbody->Rigidbody, PlayerGameObject.Transform);
    
    std::cout << glm::to_string(PlayerGameObject.GetComponent<TransformComponent>()->Position);

  

}

void ElderHex::OnUpdate() {

    // To-Do : Create sun object.

    // Move Light
    //const float SUN_HEIGHT = 100.0f;
    //const float SUN_DURATION = 24.0f;
    //float sunY = sin(glfwGetTime() / SUN_DURATION) * SUN_HEIGHT;
    //float sunX = cos(glfwGetTime() / SUN_DURATION) * SUN_HEIGHT;
    //lightPos = glm::vec3(sunX, sunY,lightPos.z);


    TerrainGameObject.Update(DeltaTime);
    PlayerGameObject.Update(DeltaTime);
    Dummy.Update(DeltaTime);
    spikes.Update(DeltaTime);




}

void ElderHex::OnRender() {

    TerrainGameObject.Render();
    PlayerGameObject.Render();
    Dummy.Render();
    spikes.Render();

}

void ElderHex::OnRenderUI() {

    //UI
    
    float corsshairSize = 70;
    CrossHair.DrawSprite(GetScreenWidth(), GetScreenHeight(), glm::vec2(GetScreenWidth()/2- corsshairSize/2, GetScreenHeight()/2- corsshairSize/2), glm::vec2(corsshairSize), 0, glm::vec3(0.0f) , &_spriteTexture);
    PlayerGameObject.PlayerHealthBar.Render();
}
