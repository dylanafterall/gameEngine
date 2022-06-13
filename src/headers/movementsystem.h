/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// movementsystem.h
// header file for movement system
// -----------------------------------------------------------------------------
#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ecs.h"
#include "transformcomponent.h"
#include "rigidbodycomponent.h"

class MovementSystem: public System {
public:
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update(double deltaTime) {
        for (auto entity : GetSystemEntities()) {
            // update entity position based on its velocity
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidbody.velocity.x * deltaTime;
            transform.position.y += rigidbody.velocity.y * deltaTime;
       }
    }
};

#endif
