#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "../../Engine/TuftEngine.h"

class Terrain
{

public :
	GameObject mountains;
	GameObject floor;

    GameObject boundingBoxForward;
    GameObject boundingBoxBackward;
    GameObject boundingBoxLeft;
    GameObject boundingBoxRight;

    Terrain() {};
	Terrain(Camera* camera, rp3d::PhysicsWorld* physicsWorld, glm::vec3 *lightPos, rp3d::PhysicsCommon *physicsCommon)
	{
        Shader terrainShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
        terrainShader.setVec3("objectColor", 0.8f, 0.44f, 0.41f);
        Shader floorShader("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FlatColourShader.frag");
        floorShader.setVec3("objectColor", 0.4f, 0.5f, 0.2f);
        
        // FLOOR
        const char* floorPath = "Assets/Models/Primatives/Cube.obj";
        Model floorModel(floorPath);
        glm::vec3 floorSize = glm::vec3(100, 1, 100);
        floor.Transform->Scale = floorSize;
       

        floor.AddComponent<RenderComponent>(lightPos, camera, floor.Transform, floorModel, floorShader);
        RigidbodyComponent* TerrainRigidbody = floor.AddComponent<RigidbodyComponent>(physicsWorld, floor.Transform);
        TerrainRigidbody->SetGravity(false);
        TerrainRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);
        floor.AddComponent<ColliderComponent>
                                            (physicsCommon, 
                                             ColliderComponent::EColliderShape::BOX,
                                             TerrainRigidbody->Rigidbody, 
                                             floor.Transform, 
                                             floor.Transform->Vector3GlmToRp3d(floorSize));


        // MOUNTAINS
        const char* mountainsPath = "Assets/Models/Terrain/Elderhex_Land.obj";
        Model mountainsModel(mountainsPath);
        mountains.Transform->Position = glm::vec3(-10.0f, -0.5f,10.0f);
        mountains.Transform->Scale = glm::vec3(10.0f);
        mountains.AddComponent<RenderComponent>(lightPos, camera, mountains.Transform, mountainsModel, terrainShader);




        // TO-DO (URGENT) : Replace these with objects for optimisation

        // FORWARD BOUNDS
        glm::vec3 forwardBoxSize = glm::vec3(100.0f, 10.0f, 1.0f);
        boundingBoxForward.Transform->Position = glm::vec3(0.0f, 1.0f, 55.0f);
        boundingBoxForward.Transform->Scale = forwardBoxSize;
        RigidbodyComponent* forwardRigidbody = boundingBoxForward.AddComponent<RigidbodyComponent>(physicsWorld, boundingBoxForward.Transform);
        boundingBoxForward.AddComponent<ColliderComponent> (physicsCommon, ColliderComponent::EColliderShape::BOX, forwardRigidbody->Rigidbody,boundingBoxForward.Transform, boundingBoxForward.Transform->Vector3GlmToRp3d(forwardBoxSize));
        forwardRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);    

        // BACKWARD BOUNDS
        glm::vec3 backwardBoxSize = glm::vec3(100.0f, 10.0f, 1.0f);
        boundingBoxBackward.Transform->Position = glm::vec3(0.0f, 1.0f, -5.0f);
        boundingBoxBackward.Transform->Scale = backwardBoxSize;
        RigidbodyComponent* backwardRigidbody = boundingBoxBackward.AddComponent<RigidbodyComponent>(physicsWorld, boundingBoxBackward.Transform);
        boundingBoxBackward.AddComponent<ColliderComponent> (physicsCommon, ColliderComponent::EColliderShape::BOX, backwardRigidbody->Rigidbody, boundingBoxBackward.Transform, boundingBoxBackward.Transform->Vector3GlmToRp3d(backwardBoxSize));
        backwardRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);

        // LEFT BOUNDS
        glm::vec3 leftBoxSize = glm::vec3(1.0f, 10.0f, 100.0f);
        boundingBoxLeft.Transform->Position = glm::vec3(80.0f, 1.0f, 0.0f);
        boundingBoxLeft.Transform->Scale = leftBoxSize;
        RigidbodyComponent* leftRigidbody = boundingBoxLeft.AddComponent<RigidbodyComponent>(physicsWorld, boundingBoxLeft.Transform);
        boundingBoxLeft.AddComponent<ColliderComponent> (physicsCommon, ColliderComponent::EColliderShape::BOX, leftRigidbody->Rigidbody, boundingBoxLeft.Transform, boundingBoxLeft.Transform->Vector3GlmToRp3d(leftBoxSize));
        leftRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);      

        // RIGHT BOUNDS
        glm::vec3 rightBoxSize = glm::vec3(1.0f, 10.0f, 100.0f);
        boundingBoxRight.Transform->Position = glm::vec3(-20.0f, 1.0f, 0.0f);
        boundingBoxRight.Transform->Scale = rightBoxSize;
        RigidbodyComponent* rightRigidbody = boundingBoxRight.AddComponent<RigidbodyComponent>(physicsWorld, boundingBoxRight.Transform);
        boundingBoxRight.AddComponent<ColliderComponent> (physicsCommon, ColliderComponent::EColliderShape::BOX, rightRigidbody->Rigidbody, boundingBoxRight.Transform, boundingBoxRight.Transform->Vector3GlmToRp3d(rightBoxSize));
        rightRigidbody->Rigidbody->setType(rp3d::BodyType::STATIC);

	}

    void Update(float deltaTime) {
        boundingBoxForward.Update(deltaTime);
        boundingBoxBackward.Update(deltaTime);
        boundingBoxLeft.Update(deltaTime);
        boundingBoxRight.Update(deltaTime);



        floor.Update(deltaTime);
        mountains.Update(deltaTime);


        //boundingBox.Transform->Position = glm::vec3(100.0f, 0.0f, 0.0f);

    }

    void Render() {

        boundingBoxForward.Render();
        boundingBoxBackward.Render();
        boundingBoxLeft.Render();
        boundingBoxRight.Render();
        floor.Render();
        mountains.Render();
    }
};

#endif
