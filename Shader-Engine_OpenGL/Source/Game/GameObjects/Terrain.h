#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "../ElderHex.h"

class Terrain
{

public :
	GameObject bag;
	GameObject floor;

    RigidbodyComponent* TerrainRigidbody;
    ColliderComponent* TerrainCollider;

    Terrain() {};
	Terrain(Camera* camera, rp3d::PhysicsWorld* physicsWorld, glm::vec3 *lightPos, rp3d::PhysicsCommon *physicsCommon)
	{
        Shader litShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");


        const char* terrainPath = "Assets/Models/Terrain/Elderhex_Land/Elderhex_Land.obj";
        Model boxModel(terrainPath);
        floor.Transform->Position = glm::vec3(0, 0, 0);

        floor.addComponent<RenderComponent>(lightPos, camera, floor.Transform, boxModel, litShader);
        TerrainRigidbody = floor.addComponent<RigidbodyComponent>(physicsWorld, floor.Transform);
        TerrainCollider = floor.addComponent<ColliderComponent>(physicsCommon, ColliderComponent::EColliderShape::BOX, TerrainRigidbody->Rigidbody, floor.Transform, rp3d::Vector3(5, 1, 5));
        TerrainRigidbody->SetGravity(false);
        TerrainRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);




	}

    void Update(float deltaTime) {
        floor.Update(deltaTime);
    }

    void Render() {
        floor.Render();
    }
};

#endif
