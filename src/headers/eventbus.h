/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// eventbus.h
// header file for Event Bus
// -----------------------------------------------------------------------------
#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "event.h"
#include <spdlog/spdlog.h>
#include <map>
#include <typeindex>
#include <list>
#include <functional>

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// EVENT CALLBACK
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
class IEventCallback {
public:
    virtual ~IEventCallback() = default;

    void Execute(Event& e) {
        Call(e);
    }

private:
    virtual void Call(Event& e) = 0;
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
    typedef void (TOwner::*CallbackFunction)(TEvent&);

    TOwner* ownerInstance;
    CallbackFunction callbackFunction;

    virtual void Call(Event& e) override {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
    }

public:
    EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
        this->ownerInstance = ownerInstance;
        this->callbackFunction = callbackFunction;
    }

    virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// EVENT BUS
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
class EventBus {
public:
    EventBus() {
        spdlog::info("EventBus constructor called!");
    }

    ~EventBus() {
        spdlog::info("EventBus destructor called!");
    }

    // clear the subscriber list
    void Reset() {
        subscribers.clear();
    }

    // subscribe to an event type <T>
    template <typename TEvent, typename TOwner>
    void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
        if (!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    // emit an event of type <T>
    template <typename TEvent, typename ...TArgs>
    void EmitEvent(TArgs&& ...args) {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers) {
            for (auto it = handlers->begin(); it != handlers->end(); it++) {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }

private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;
};

#endif
