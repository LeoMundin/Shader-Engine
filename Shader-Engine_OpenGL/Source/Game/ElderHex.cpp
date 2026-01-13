#include "ElderHex.h"
//
// 
// TO-DO Move all this informatation into seperate scene objects which take in lifecycle methods
//
//

// Enables game events manager.

SpriteRenderer Renderer;
Texture* SpriteTexture;

void ElderHex::OnAwake() {

    //PhysicsWorld->setGravity(rp3d::Vector3(0, -0.2, 0));
    TerrainGameObject = Terrain(&MainCamera, PhysicsWorld, &lightPos, &PhysicsCommon);



    PlayerGameObject = Player(&MainCamera, PhysicsWorld,GetScreenWidth(),GetScreenHeight());
    PlayerGameObject.addComponent<ColliderComponent>(&PhysicsCommon, ColliderComponent::EColliderShape::BOX, PlayerGameObject.Rigidbody->Rigidbody, PlayerGameObject.Transform);

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




}

void ElderHex::OnRender() {

    TerrainGameObject.Render();
    PlayerGameObject.Render();

}

void ElderHex::OnRenderUI() {

    //UI
    PlayerGameObject.PlayerHealthBar.Render();

}
