#pragma once
#ifndef TRAP_H
#define TRAP_H

#include "../ElderHex.h"


class Trap : public GameObject
{
public:

    Trap() {};
    Trap(Camera* camera, rp3d::PhysicsWorld* physicsWorld, glm::vec3* lightPos, rp3d::PhysicsCommon* physicsCommon)
    {
        Shader terrainShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
        // FLOOR
        const char* floorPath = "Assets/Models/Spikes/Low-Poly_Spikes.obj";
        Model floorModel(floorPath);
        glm::vec3 floorSize = glm::vec3(1, 1, 1);
        Transform->Scale = floorSize;
        Transform->Position = glm::vec3(20.0f, 1.0f, 25.0f);

        AddComponent<RenderComponent>(lightPos, camera, Transform, floorModel, terrainShader);
        RigidbodyComponent* TerrainRigidbody = AddComponent<RigidbodyComponent>(physicsWorld, Transform);
        TerrainRigidbody->SetGravity(false);
        TerrainRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);
        AddComponent<ColliderComponent>
            (physicsCommon,
                ColliderComponent::EColliderShape::BOX,
                TerrainRigidbody->Rigidbody,
                Transform,
                Transform->Vector3GlmToRp3d(floorSize));
    }
};

#endif