/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// keypressedevent.h
// header file for Key-Pressed Event
// -----------------------------------------------------------------------------
#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "ecs.h"
#include "event.h"
#include <SDL2/SDL.h>

class KeyPressedEvent : public Event {
public:
    SDL_Keycode symbol;
    KeyPressedEvent(SDL_Keycode symbol) : symbol(symbol) {}
};

#endif
