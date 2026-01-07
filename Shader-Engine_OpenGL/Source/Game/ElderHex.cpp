#include "ElderHex.h"

SpriteRenderer Renderer;
Texture* SpriteTexture;

void ElderHex::OnAwake() {

    // load shaders
    Shader SpriteShader("Assets/Shaders/SpriteVertShader.vert", "Assets/Shaders/SpriteFragShader.frag");
    // configure shaders

    // set render-specific controls
    Renderer = SpriteRenderer(SpriteShader);
    SpriteTexture = new Texture("Assets/Textures/awesomeface.png", false);

    //std::cout << SpriteShader.ID << std::endl;

    //PhysicsWorld->setGravity(rp3d::Vector3(0, -0.2, 0));
    TerrainGameObject = Terrain(&MainCamera, PhysicsWorld, &lightPos, &PhysicsCommon);

    PlayerGameObject = Player(&MainCamera, PhysicsWorld);
    PlayerGameObject.addComponent<ColliderComponent>(&PhysicsCommon, ColliderComponent::EColliderShape::BOX, PlayerGameObject.Rigidbody->Rigidbody, PlayerGameObject.Transform);

}

void ElderHex::OnUpdate() {
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
    float screenHeight = GetScreenHeight();
    float screenWidth = GetScreenWidth();
    glm::vec2 spritePosition = glm::vec2(screenWidth /2, screenHeight/2);
    glm::vec2 spriteSize = glm::vec2(400.0f, 400.0f);
    float spriteRotation = 0.0f;
    glm::vec3 spriteColour = glm::vec3(1.0f);
    
    Renderer.DrawSprite(screenWidth, screenHeight,*SpriteTexture, spritePosition, spriteSize, spriteRotation, spriteColour);

}
