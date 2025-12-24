#include "ElderHex.h"



void ElderHex::OnAwake() {

    //PhysicsWorld->setGravity(rp3d::Vector3(0, -0.2, 0));
    TerrainGameObject = Terrain(&MainCamera, PhysicsWorld, &lightPos, &PhysicsCommon);

    PlayerGameObject = Player(&MainCamera, PhysicsWorld);
    PlayerGameObject.Transform->Position = glm::vec3(0.0f, 10.0f, 10.0f);
    PlayerGameObject.addComponent<ColliderComponent>(&PhysicsCommon, ColliderComponent::EColliderShape::BOX, PlayerGameObject.Rigidbody->Rigidbody, PlayerGameObject.Transform);



}

void ElderHex::OnUpdate() {
    // Move Light
    const float radius = 8.0f;
    float lightX = sin(glfwGetTime()) * radius;
    float lightZ = cos(glfwGetTime()) * radius;
    lightPos = glm::vec3(lightX, lightPos.y, lightZ);


    PlayerGameObject.Update(DeltaTime);
    TerrainGameObject.Update(DeltaTime);



}

void ElderHex::OnRender() {

    PlayerGameObject.Render();
    TerrainGameObject.Render();
}
