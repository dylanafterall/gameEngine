/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// ecs.cpp
// implementation file for registry, entity, component, system, and pool classes
// -----------------------------------------------------------------------------
#include "headers/ecs.h"
#include <algorithm>
#include <spdlog/spdlog.h>


// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// COMPONENT
// holds data of an entity, to be manipulated by systems
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
int IComponent::nextId = 0;


// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// ENTITY
// id to keep track of numerous entity instances
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
int Entity::GetId() const {
    return id;
}

void Entity::Kill() {
    registry->KillEntity(*this);
}


// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// SYSTEM
// processes/manipulates data of entities which contain specific signature
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity == other;
    }), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}


// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// REGISTRY
// manages creation and destruction of entities, add systems, and components
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
Entity Registry::CreateEntity() {
    int entityId;

    if (freeIds.empty()) {
        // if there are no free Ids waiting to be reused, expand and resize
        entityId = numEntities++;
        if (entityId >= entityComponentSignatures.size()) {
            entityComponentSignatures.resize(entityId + 1);
        }
    }
    else {
        // reuse an id from the list of previously removed entities
        entityId = freeIds.front();
        freeIds.pop_front();
    }

    Entity entity(entityId);
    entity.registry = this;
    entitiesToBeAdded.insert(entity);

    spdlog::info("Entity created with id = " + std::to_string(entityId));

    return entity;
}

void Registry::KillEntity(Entity entity) {
    entitiesToBeKilled.insert(entity);
}

void Registry::AddEntityToSystems(Entity entity) {
    const auto entityId = entity.GetId();

    const auto& entityComponentSignature = entityComponentSignatures[entityId];
    
    for (auto& system: systems) {
        const auto& systemComponentSignature = system.second->GetComponentSignature();

        bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

        if (isInterested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::RemoveEntityFromSystems(Entity entity) {
    for (auto system : systems) {
        system.second->RemoveEntityFromSystem(entity);
    }
}

void Registry::Update() {
    // process the entities that are waiting to be created to the active Systems
    for (auto entity : entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    // process the entities that are waiting to be killed from active systems
    for (auto entity : entitiesToBeKilled) {
        RemoveEntityFromSystems(entity);
        entityComponentSignatures[entity.GetId()].reset();

        // make the entity id available to be reused
        freeIds.push_back(entity.GetId());
    }
    entitiesToBeKilled.clear();
}
