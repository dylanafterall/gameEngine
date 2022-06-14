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
#include "assetstore.h"
#include <SDL2/SDL.h>

class RenderSystem: public System {
public:
    RenderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
        // create a vector with both sprite and transform component of entities
        struct RenderableEntity {
            TransformComponent transformComponent;
            SpriteComponent spriteComponent;
        };
        std::vector<RenderableEntity> renderableEntities;
        for (auto entity : GetSystemEntities()) {
            RenderableEntity renderableEntity;
            renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();
            renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
            renderableEntities.emplace_back(renderableEntity);
        }

        // sort the vector by the z-index value
        std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) {
            return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
        });

        for (auto entity : renderableEntities) {
            // update entity position based on its velocity
            const auto transform = entity.transformComponent;
            const auto sprite = entity.spriteComponent;
            
            // set the source rectangle of our original sprite texture
            SDL_Rect srcRect = sprite.srcRect;
            // set the destination rectangle with x,y position to be rendered
            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y)
            };

            SDL_RenderCopyEx(
                renderer,
                assetStore->GetTexture(sprite.assetId),
                &srcRect,
                &dstRect,
                transform.rotation,
                NULL,
                SDL_FLIP_NONE
            );

            // draw the PNG texture
      }
    }
};

#endif
