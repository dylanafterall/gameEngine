#include "game.h"   
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include <spdlog/spdlog.h>


Game::Game() {
    isRunning = false;
    spdlog::info("Game constructor called!");
}

Game::~Game() {
    spdlog::info("Game destructor called!");
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        spdlog::critical("Error initializing SDL.");
        return;
    }
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800; //displayMode.w;
    windowHeight = 600; //displayMode.h;
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        spdlog::critical("Error creating SDL window.");
        return;
    }
    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        spdlog::critical("Error creating SDL renderer.");
        return;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void Game::Run() {
    Setup();
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                break;
        }
    }
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
    playerPosition = glm::vec2(10.0f, 20.0f);
    playerVelocity = glm::vec2(100.0f, 0.0f);
}

void Game::Update() {
    // if too fast, waste some time until we reach MILLISECS_PER_FRAME
    // if desired, remove this block - jump to deltaTime for uncapped FPS
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

    // store the current frame time
    millisecsPreviousFrame = SDL_GetTicks();

    playerPosition.x += playerVelocity.x * deltaTime;
    playerPosition.y += playerVelocity.y * deltaTime;
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // draw a PNG texture
    SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // no longer need surface now that we have texture
    SDL_FreeSurface(surface);
    // destination for texture on screen (x, y, w, h)
    SDL_Rect dstRect = {
        static_cast<int>(playerPosition.x), 
        static_cast<int>(playerPosition.y), 
        32, 
        32
    };
    // (renderer, texture, srcRect -NULL for full texture-, dstRect)
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
