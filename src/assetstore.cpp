/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// assetstore.cpp
// implementation file for AssetStore class
// -----------------------------------------------------------------------------
#include "headers/assetstore.h"
#include <spdlog/spdlog.h>
#include <SDL2/SDL_image.h>

AssetStore::AssetStore() {
    spdlog::info("AssetStore constructor called!");
}

AssetStore::~AssetStore() {
    ClearAssets();
    spdlog::info("AssetStore destructor called!");
}

void AssetStore::ClearAssets() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // add the texture to the map
    textures.emplace(assetId, texture);

    spdlog::info("New texture added to the Asset Store with id = " + assetId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
    return textures[assetId];
}
