/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// collisionevent.h
// header file for Collision Event
// -----------------------------------------------------------------------------
#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "ecs.h"
#include "event.h"

class CollisionEvent : public Event {
public:
    Entity a;
    Entity b;
    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};

#endif
