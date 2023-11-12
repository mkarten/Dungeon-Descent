#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/tile_info.hpp"
#include <map>
#include <string>

namespace utils
{
    using TileMap = std::map<std::string, TileInfo>;

    float hireTimeInSeconds(); // Retourne le temps depuis le lancement du programme en secondes

    SDL_Texture* loadTileFromTileset(SDL_Texture* tileset, TileInfo tileInfo, SDL_Renderer* renderer);

    SDL_Texture* rotateTexture(SDL_Texture* texture, SDL_Renderer* renderer, double angle);

    void drawBoundingBox(SDL_Renderer* renderer, float x, float y, float w, float h, SDL_Color color);

    TileMap LoadTileInfo(const std::string& filename);

    void logLastSDLError();
}


