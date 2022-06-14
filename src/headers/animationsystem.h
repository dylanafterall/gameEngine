/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// animationsystem.h
// header file for Animation System
// -----------------------------------------------------------------------------
#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "ecs.h"
#include "spritecomponent.h"
#include "animationcomponent.h"
#include <SDL2/SDL.h>

class AnimationSystem : public System {
public:
    AnimationSystem() {
        RequireComponent<SpriteComponent>();
        RequireComponent<AnimationComponent>();
    }

    void Update() {
        for (auto entity : GetSystemEntities()) {
            auto& animation = entity.GetComponent<AnimationComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();

            // change the current frame
            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;

            // change the src rectangle of the sprite (to next 'frame')
            sprite.srcRect.x = animation.currentFrame * sprite.width;
        }
    }
};

#endif
