/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// rendercollidersystem.h
// header file for Render Collider System
// -----------------------------------------------------------------------------
#ifndef RENDERCOLLIDERSYSTEM_H
#define RENDERCOLLIDERSYSTEM_H

#include "ecs.h"
#include "transformcomponent.h"
#include "boxcollidercomponent.h"
#include <SDL2/SDL.h>

class RenderColliderSystem : public System {
public:
    RenderColliderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    } 

    void Update(SDL_Renderer* renderer) {
        for (auto entity : GetSystemEntities()) {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto collider = entity.GetComponent<BoxColliderComponent>();

            SDL_Rect colliderRect = {
                static_cast<int>(transform.position.x + collider.offset.x),
                static_cast<int>(transform.position.y + collider.offset.y),
                static_cast<int>(collider.width),
                static_cast<int>(collider.height)
            };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &colliderRect);
        }
    }
};

#endif
