/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// projectilelifecyclesystem.h
// header file for Projectile Lifecycle System
// -----------------------------------------------------------------------------
#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include "ecs.h"
#include "projectilecomponent.h"

class ProjectileLifecycleSystem : public System {
public:
    ProjectileLifecycleSystem() {
        RequireComponent<ProjectileComponent>();
    }
    
    void Update() {
        for (auto entity : GetSystemEntities()) {
            auto projectile = entity.GetComponent<ProjectileComponent>();

            // kill projectiles after they reach thier duration limit
            if (SDL_GetTicks() - projectile.startTime > projectile.duration) {
                entity.Kill();
            }
        }
    }
};

#endif
