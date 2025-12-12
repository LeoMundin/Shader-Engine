#include "Header/ElderHex.h"
RigidbodyComponent* BagRigidbody;
ColliderComponent* BagCollider;
RigidbodyComponent* TerrainRigidbody;
HealthComponent* TerrainHealth;
ColliderComponent* TerrainCollider;

void ElderHex::OnAwake() {

    //PhysicsWorld->setGravity(rp3d::Vector3(0, -0.2, 0));

    player = Player(&MainCamera, PhysicsWorld);
    player.Transform->Position = glm::vec3(0.0f, 10.0f, 10.0f);
    player.addComponent<ColliderComponent>(&PhysicsCommon, ColliderComponent::EColliderShape::BOX, player.Rigidbody->Rigidbody, player.Transform);



    const char* backpackPath = "Assets/Models/backpack/backpack.obj";
    Model backpack(backpackPath);
    Shader ourShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
    bag.Transform->Position = glm::vec3(0, 15, 0);
    bag.addComponent<RenderComponent>(&lightPos, &MainCamera, bag.Transform, backpack, ourShader);
    BagRigidbody = bag.addComponent<RigidbodyComponent>(PhysicsWorld, bag.Transform);
    BagCollider = bag.addComponent<ColliderComponent>(&PhysicsCommon,ColliderComponent::EColliderShape::BOX, BagRigidbody->Rigidbody,bag.Transform);
    //BagRigidbody->SetGravity(false);

    const char* terrainPath = "Assets/Models/Terrain/Elderhex_Land/Elderhex_Land.obj";
    Model boxModel(terrainPath);
    Terrain.Transform->Position = glm::vec3(0, 0, 0);
    Terrain.addComponent<RenderComponent>(&lightPos, &MainCamera, Terrain.Transform, boxModel, ourShader);
    TerrainRigidbody = Terrain.addComponent<RigidbodyComponent>(PhysicsWorld, Terrain.Transform);
    TerrainCollider = Terrain.addComponent<ColliderComponent>(&PhysicsCommon, ColliderComponent::EColliderShape::BOX, TerrainRigidbody->Rigidbody, Terrain.Transform,rp3d::Vector3(5,1,5));
    TerrainHealth = Terrain.addComponent<HealthComponent>(3.0f);
    TerrainRigidbody->SetGravity(false);
    TerrainRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);



}

void ElderHex::OnUpdate() {
    // Move Light
    const float radius = 8.0f;
    float lightX = sin(glfwGetTime()) * radius;
    float lightZ = cos(glfwGetTime()) * radius;
    lightPos = glm::vec3(lightX, lightPos.y, lightZ);


    bag.Update(DeltaTime);
    player.Update(DeltaTime);
    Terrain.Update(DeltaTime);

    if (InputSystem::LeftMousePressed) {
        TerrainHealth->TakeDamage(1.0f);
        std::cout << "Damage Taken" << std::endl;
    }
    //box.Destroy();

}

void ElderHex::OnRender() {
    //float x = BagRigidbody->Rigidbody->getTransform().getPosition().x;
    //float y = BagRigidbody->Rigidbody->getTransform().getPosition().y;
    //float z = BagRigidbody->Rigidbody->getTransform().getPosition().z;
    //printf("Bag Rigidbody: (%f, %f, %f)\n", x, y, z);
    //x = bag.Transform->Position.x;
    //y = bag.Transform->Position.y;
    //z = bag.Transform->Position.z;
    //printf("Bag Transform: (%f, %f, %f)\n", x, y, z);
    //x = BagCollider->Collider->getLocalToWorldTransform().getPosition().x;
    //y = BagCollider->Collider->getLocalToWorldTransform().getPosition().y;
    //z = BagCollider->Collider->getLocalToWorldTransform().getPosition().z;
    //printf("Bag Collider: (%f, %f, %f)\n", x, y, z);

    //x = CubeRigidbody->Rigidbody->getTransform().getPosition().x;
    //y = CubeRigidbody->Rigidbody->getTransform().getPosition().y;
    //z = CubeRigidbody->Rigidbody->getTransform().getPosition().z;
    //printf("Cube Rigidbody: (%f, %f, %f)\n", x, y, z);
    //x = box.Transform->Position.x;
    //y = box.Transform->Position.y;
    //z = box.Transform->Position.z;
    //printf("Cube Transform: (%f, %f, %f)\n", x, y, z);
    //x = CubeCollider->Collider->getLocalToWorldTransform().getPosition().x;
    //y = CubeCollider->Collider->getLocalToWorldTransform().getPosition().y;
    //z = CubeCollider->Collider->getLocalToWorldTransform().getPosition().z;
    //printf("Cube Collider: (%f, %f, %f)\n", x, y, z);

    //printf("collision = %s\n", PhysicsWorld->testOverlap(CubeRigidbody->Rigidbody, BagRigidbody->Rigidbody) ? "=============================================================" : "false");

    player.Render();
    bag.Render();
    Terrain.Render();
}
