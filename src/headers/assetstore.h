/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// assetstore.h
// header file for AssetStore class
// -----------------------------------------------------------------------------
#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class AssetStore {
public:
    AssetStore();
    ~AssetStore();

    void ClearAssets();

    void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
    SDL_Texture* GetTexture(const std::string& assetId);

    void AddFont(const std::string& assetId, const std::string& filePath, int fontSize);
    TTF_Font* GetFont(const std::string& assetId);

private:
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};

#endif
