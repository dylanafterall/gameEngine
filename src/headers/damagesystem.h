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
#include "projectilecomponent.h"
#include "healthcomponent.h"
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
        Entity a = event.a;
        Entity b = event.b;
        spdlog::info("The Damage System received an event collision between entities " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()));
        
        // if enemy projectile hits player / player hits projectile
        if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
            OnProjectileHitsPlayer(a, b); // a is projectile, b is player
        }
        if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
            OnProjectileHitsPlayer(b, a); // b is projectile, a is player
        }

        // if friendly projectile hits enemy / enemy hits projectile
        if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(a, b); // a is projectile, b is enemy
        }
        if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(b, a); // b is projectile, a is enemy
        }
    }

    void OnProjectileHitsPlayer(Entity projectile, Entity player) {
        const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (!projectileComponent.isFriendly) {
            // reduce the health of player by the projectile hitPercentDamage
            auto& health = player.GetComponent<HealthComponent>();
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            if (health.healthPercentage <= 0) {
                player.Kill();
            }

            projectile.Kill();
        }
    }

    void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
        const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (projectileComponent.isFriendly) {
            // reduce the health of enemy by the projectile hitPercentDamage
            auto& health = enemy.GetComponent<HealthComponent>();
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            if (health.healthPercentage <= 0) {
                enemy.Kill();
            }

            projectile.Kill();
        }
    }

    void Update() {

    }
};

#endif
