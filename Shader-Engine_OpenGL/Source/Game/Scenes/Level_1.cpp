#include "Level_1.h"

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

void Level_1::Load(TuftEngine* enginePtr, rp3d::PhysicsWorld* physicsSim) {
    Scene::Load(enginePtr, physicsSim);

    TerrainGameObject = Terrain(&_mainCamera, PhysicSimulation, &_lightPosition, &Engine->Physics);
    Dummy = TargetDummy(&_mainCamera, PhysicSimulation, &_lightPosition, &Engine->Physics);
    spikes = Trap(&_mainCamera, PhysicSimulation, &_lightPosition, &Engine->Physics);


    Shader spriteShader("Assets/Shaders/SpriteVertShader.vert", "Assets/Shaders/SpriteFragShader.frag");
    spriteShader.setBool("canLoadTexture", true);
    CrossHair = SpriteRenderer(spriteShader);

    PlayerGameObject = Player(&_mainCamera, PhysicSimulation, Engine->GetScreenWidth(), Engine->GetScreenHeight());
    PlayerGameObject.AddComponent<ColliderComponent>(&Engine->Physics, ColliderComponent::EColliderShape::BOX, PlayerGameObject.Rigidbody->Rigidbody, PlayerGameObject.Transform);

    //std::cout << glm::to_string(PlayerGameObject.GetComponent<TransformComponent>()->Position);



}

void Level_1::Awake() {

}

void Level_1::Update() {

    // To-Do : Create sun object.

    // Move Light
    //const float SUN_HEIGHT = 100.0f;
    //const float SUN_DURATION = 24.0f;
    //float sunY = sin(glfwGetTime() / SUN_DURATION) * SUN_HEIGHT;
    //float sunX = cos(glfwGetTime() / SUN_DURATION) * SUN_HEIGHT;
    //_lightPosition = glm::vec3(sunX, sunY, _lightPosition.z);


    TerrainGameObject.Update(Engine->DeltaTime);
    PlayerGameObject.Update(Engine->DeltaTime);
    Dummy.Update(Engine->DeltaTime);
    spikes.Update(Engine->DeltaTime);




}

void Level_1::Render() {

    TerrainGameObject.Render();
    PlayerGameObject.Render();
    Dummy.Render();
    spikes.Render();

}

void Level_1::RenderUI() {

    //UI

    float corsshairSize = 70;
    CrossHair.DrawSprite(Engine->GetScreenWidth(), Engine->GetScreenHeight(), glm::vec2(Engine->GetScreenWidth() / 2 - corsshairSize / 2, Engine->GetScreenHeight() / 2 - corsshairSize / 2), glm::vec2(corsshairSize), 0, glm::vec3(0.0f), &_spriteTexture);
    PlayerGameObject.PlayerHealthBar.Render();
}
