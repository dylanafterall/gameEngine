/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// projectilecomponent.h
// header file for Projectile Component
// -----------------------------------------------------------------------------
#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <SDL2/SDL.h>

struct ProjectileComponent {
    bool isFriendly;
    int hitPercentDamage;
    int duration;
    int startTime;

    ProjectileComponent(
        bool isFriendly = false,
        int hitPercentDamage = 0,
        int duration = 0
        ) {
        this->isFriendly = isFriendly;
        this->hitPercentDamage = hitPercentDamage;
        this->duration = duration;
        this->startTime = SDL_GetTicks();
    }
};

#endif
