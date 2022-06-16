/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// cameramovementsystem.h
// header file for Camera Movement System
// -----------------------------------------------------------------------------
#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "ecs.h"
#include "camerafollowcomponent.h"
#include "transformcomponent.h"
#include <SDL2/SDL.h>

class CameraMovementSystem : public System {
public: 
    CameraMovementSystem() {
        RequireComponent<CameraFollowComponent>(); 
        RequireComponent<TransformComponent>(); 
    }

    void Update(SDL_Rect& camera) {
        for (auto entity : GetSystemEntities()) {
            auto transform = entity.GetComponent<TransformComponent>();

            if (transform.position.x + (camera.w / 2) < Game::mapWidth) {
                camera.x = transform.position.x - (Game::windowWidth / 2);
            }
            if (transform.position.y + (camera.h / 2) < Game::mapHeight) {
                camera.y = transform.position.y - (Game::windowHeight / 2);
            }

            // keep camera rectangle view inside the screen limits
            camera.x = camera.x < 0 ? 0 : camera.x;
            camera.y = camera.y < 0 ? 0 : camera.y;
            camera.x = camera.x > camera.w ? camera.w : camera.x;
            camera.y = camera.y > camera.h ? camera.h : camera.y;
        }
    }
};

#endif
