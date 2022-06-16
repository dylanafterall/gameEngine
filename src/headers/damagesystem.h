/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// damagesystem.h
// header file for Damgae System
// -----------------------------------------------------------------------------
#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "ecs.h"
#include "boxcollidercomponent.h"
#include "eventbus.h"
#include "collisionevent.h"
#include <spdlog/spdlog.h>

class DamageSystem : public System {
public:
    DamageSystem() {
        RequireComponent<BoxColliderComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
    }

    void onCollision(CollisionEvent& event) {
        spdlog::info("The Damage System received an event collision between entities " + std::to_string(event.a.GetId()) + " and " + std::to_string(event.b.GetId()));
        event.a.Kill();
        event.b.Kill();
    }

    void Update() {

    }
};

#endif
