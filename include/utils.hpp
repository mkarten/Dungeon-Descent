#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/tile_info.hpp"
#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "vector.hpp"

namespace utils
{

    // variables for the font
    extern TTF_Font* OpenSans;
    extern bool fontLoaded;
    extern SDL_Texture *fullHeart;
    extern SDL_Texture *halfHeart;
    extern SDL_Texture *emptyHeart;
    extern bool heartTexturesLoaded;

    using TileMap = std::map<std::string, TileInfo>;

    float hireTimeInSeconds(); // Returns the time since the program started in seconds

    SDL_Texture* loadTileFromTileset(SDL_Texture* tileset, TileInfo tileInfo, SDL_Renderer* renderer);

    void drawBoundingBox(SDL_Renderer* renderer, float x, float y, float w, float h, SDL_Color color);

    TileMap LoadTileInfo(const std::string& filename);

    void logLastSDLError();

    void loadFont();

    TTF_Font* getFont();

    void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color);

    SDL_Texture* textureTiling(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height);

    bool isPointInRect(int x, int y, SDL_Rect rect);

    std::string chooseFile(const std::string& title, const std::string& initialPath, const std::string& filter);

    std::string getCurrentWorkingDirectory();

    int distance(Vector2f v1, Vector2f v2);

    Vector2f normalize(Vector2f v);

    void loadHeartTextures(SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap,SDL_Renderer *renderer);

    SDL_Texture* getHeartFullTexture();

    SDL_Texture* getHeartHalfTexture();

    SDL_Texture* getHeartEmptyTexture();

    float lerpf(float a, float b, float t);

    Vector2f lerpVector2f(Vector2f a, Vector2f b, float t);


}


