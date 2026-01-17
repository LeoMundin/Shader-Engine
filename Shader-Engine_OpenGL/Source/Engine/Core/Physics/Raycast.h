#pragma once
#ifndef RAYCAST_H
#define RAYCAST_H

#include "reactphysics3d.h"
#include "../../ECS/Components/ColliderComponent.h"

class Raycast : public rp3d::RaycastCallback {

public:
    bool hit = false;
    rp3d::Vector3 hitPoint;
    rp3d::Vector3 hitNormal;
    rp3d::decimal hitFraction;

    ColliderComponent* hitCollider = nullptr;

    virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) {
        hit = true;
        hitPoint = info.worldPoint;
        hitNormal = info.worldNormal;
        hitFraction = info.hitFraction;


        // Pulling collider component from physics collider.
        hitCollider = static_cast<ColliderComponent*>(info.collider->getUserData());

        // Return value controls ray continuation:
        // 0   -> stop raycast immediately
        // 1   -> continue and check all hits
        // fraction -> clip ray to this hit
        return info.hitFraction;
    }
};

#endif // !RAYCAST_H
