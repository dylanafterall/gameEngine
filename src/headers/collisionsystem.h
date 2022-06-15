/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// collisionsystem.h
// header file for Collision System
// -----------------------------------------------------------------------------
#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ecs.h"
#include "boxcollidercomponent.h"
#include "transformcomponent.h"
#include <spdlog/spdlog.h>

class CollisionSystem : public System {
public:
    CollisionSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    }

    void Update() {
        // check all entities to see if colliding with each other
        auto entities = GetSystemEntities();

        // loop all entities that system is interested in
        for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto aTransform = a.GetComponent<TransformComponent>();
            auto aCollider = a.GetComponent<BoxColliderComponent>();

            // loop all entities still needing check (to right of i)
            for (auto j = i; j != entities.end(); j++) {
                Entity b = *j;

                // bypass checking collision with self
                if (a == b) {
                    continue;
                }

                auto bTransform = b.GetComponent<TransformComponent>();
                auto bCollider = b.GetComponent<BoxColliderComponent>();

                // check for collision between a and b - using AABB
                bool collisionHappened = CheckAABBCollision(
                    aTransform.position.x + aCollider.offset.x,
                    aTransform.position.y + aCollider.offset.y,
                    aCollider.width,
                    aCollider.height,
                    bTransform.position.x + bCollider.offset.x,
                    bTransform.position.y + bCollider.offset.y,
                    bCollider.width,
                    bCollider.height
                );

                if (collisionHappened) {
                    spdlog::info("Entity " + std::to_string(a.GetId()) + " is colliding with entity " + std::to_string(b.GetId()));
                    // emit an event
                }
            }
        }
    }

    bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
        return (
            aX < bX + bW &&
            aX + aW > bX &&
            aY < bY + bH &&
            aY + aH > bY
        );
    }
};

#endif
