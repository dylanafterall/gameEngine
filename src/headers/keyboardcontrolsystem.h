/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// keyboardcontrolsystem.h
// header file for Keyboard Control System
// -----------------------------------------------------------------------------
#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "ecs.h"
#include "eventbus.h"
#include "keypressedevent.h"

class KeyboardControlSystem : public System {
public:
    KeyboardControlSystem() {

    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
    }

    void OnKeyPressed(KeyPressedEvent& event) {
        std::string keyCode = std::to_string(event.symbol);
        std::string keySymbol(1, event.symbol);
        spdlog::info("Key pressed event emitted: [" + keyCode + "] " + keySymbol);
    }

    void Update() {

    }
};

#endif
