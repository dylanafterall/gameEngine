/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// spritecomponent.h
// header file for sprite component
// -----------------------------------------------------------------------------
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>
#include <SDL2/SDL.h>

struct SpriteComponent {
    std::string assetId;
    int width;
    int height;
    int zIndex;
    bool isFixed;
    SDL_Rect srcRect;

    SpriteComponent(
        std::string assetId = "", 
        int width = 0, 
        int height = 0,
        int zIndex = 0,
        bool isFixed = false,
        int srcRectX = 0,
        int srcRectY = 0
        ) {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->zIndex = zIndex;
        this->isFixed = isFixed;
        this->srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif
