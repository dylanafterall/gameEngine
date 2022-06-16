/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// game.h
// header file for game class
// -----------------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H

#include "ecs.h"
#include "assetstore.h"
#include "eventbus.h"
#include <SDL2/SDL.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Setup();
    void LoadLevel(int level);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    static int windowWidth;
    static int windowHeight;
    static int mapWidth;
    static int mapHeight;

private:
    bool isRunning;
    bool isDebug;
    int millisecsPreviousFrame = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect camera;

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    std::unique_ptr<EventBus> eventBus;
};

#endif
