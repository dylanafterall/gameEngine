/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// textlabelcomponent.h
// header file for Text Label Component
// -----------------------------------------------------------------------------
#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct TextLabelComponent {
    glm::vec2 position;
    std::string text;
    std::string assetId;
    SDL_Color color;
    bool isFixed;

    TextLabelComponent(glm::vec2 position = glm::vec2(0), std::string text = "", std::string assetId = "", const SDL_Color& color = {0, 0, 0}, bool isFixed = true) {
        this->position = position;
        this->text = text;
        this->assetId = assetId;
        this->color = color;
        this->isFixed = isFixed;
    }
};

#endif
