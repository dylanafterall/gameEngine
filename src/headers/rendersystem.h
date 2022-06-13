/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// rendersystem.h
// header file for render system
// -----------------------------------------------------------------------------
#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ecs.h"
#include "transformcomponent.h"
#include "spritecomponent.h"
#include <SDL2/SDL.h>

class RenderSystem: public System {
public:
    RenderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(SDL_Renderer* renderer) {
        for (auto entity : GetSystemEntities()) {
            // update entity position based on its velocity
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();

            SDL_Rect objRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                sprite.width,
                sprite.height
            };
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &objRect);
       }
    }
};

#endif
