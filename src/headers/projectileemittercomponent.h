/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// projectileemittercomponent.h
// header file for Projectile Emitter Component
// -----------------------------------------------------------------------------
#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct ProjectileEmitterComponent {
    glm::vec2 projectileVelocity;
    int repeatFrequency;
    int projectileDuration;
    int hitPercentDamage;
    bool isFriendly;
    int lastEmissionTime;

    ProjectileEmitterComponent(
        glm::vec2 projectileVelocity = glm::vec2(0),
        int repeatFrequency = 0,
        int projectileDuration = 10000,
        int hitPercentDamage = 10,
        bool isFriendly = false
        ) {
        this->projectileVelocity = projectileVelocity;
        this->repeatFrequency = repeatFrequency;
        this->projectileDuration = projectileDuration;
        this->hitPercentDamage = hitPercentDamage;
        this->isFriendly = isFriendly;
        this->lastEmissionTime = SDL_GetTicks();
    }
};

#endif
