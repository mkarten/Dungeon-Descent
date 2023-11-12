#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/tile_info.hpp"
#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>

namespace utils
{
    // variables for the font
    extern TTF_Font* OpenSans;

    using TileMap = std::map<std::string, TileInfo>;

    float hireTimeInSeconds(); // Returns the time since the program started in seconds

    SDL_Texture* loadTileFromTileset(SDL_Texture* tileset, TileInfo tileInfo, SDL_Renderer* renderer);

    SDL_Texture* rotateTexture(SDL_Texture* texture, SDL_Renderer* renderer, double angle);

    void drawBoundingBox(SDL_Renderer* renderer, float x, float y, float w, float h, SDL_Color color);

    TileMap LoadTileInfo(const std::string& filename);

    void logLastSDLError();

    void loadFont();

    TTF_Font* getFont();

    void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color);
}


