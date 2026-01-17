#pragma once
#ifndef TARGET_DUMMY_H
#define TARGET_DUMMY_H

#include "../ElderHex.h"


class TargetDummy : public GameObject
{
public:

    TargetDummy() {};
    TargetDummy(Camera* camera, rp3d::PhysicsWorld* physicsWorld, glm::vec3* lightPos, rp3d::PhysicsCommon* physicsCommon)
    {
        Shader terrainShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
        // FLOOR
        const char* floorPath = "Assets/Models/Dummy/Low-Poly_Training-Dummy.obj";
        Model floorModel(floorPath);
        Transform->Position = glm::vec3(20.0f, 1.0f, 35.0f);


        addComponent<RenderComponent>(lightPos, camera, Transform, floorModel, terrainShader);
        RigidbodyComponent* TerrainRigidbody = addComponent<RigidbodyComponent>(physicsWorld, Transform);
        TerrainRigidbody->SetGravity(false);
        TerrainRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);
        addComponent<ColliderComponent>
            (physicsCommon,
                ColliderComponent::EColliderShape::BOX,
                TerrainRigidbody->Rigidbody,
                Transform,
                Transform->Vector3GlmToRp3d(Transform->Scale));
    }
};

#endif