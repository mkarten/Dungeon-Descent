#include "../include/utils.hpp"

float hireTimeInSeconds()
{
float t = SDL_GetTicks(); // Récupère le temps depuis le lancement du programme en millisecondes
t *= 0.001f; // Convertit le temps en secondes
return t;
}

SDL_Texture* loadTileFromTileset(SDL_Texture* tileset, TileInfo tileInfo, SDL_Renderer* renderer)
{
    SDL_Texture *knightIdleTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tileInfo.w, tileInfo.h);
    SDL_SetRenderTarget(renderer, knightIdleTex);
    SDL_SetTextureBlendMode(knightIdleTex, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Rect srcRect = {tileInfo.x, tileInfo.y, tileInfo.w, tileInfo.h};
    SDL_Rect destRect = {0, 0, tileInfo.w, tileInfo.h};
    SDL_RenderCopy(renderer, tileset, &srcRect, &destRect);
    SDL_SetRenderTarget(renderer, nullptr);
    return knightIdleTex;
}

SDL_Texture* rotateTexture(SDL_Texture* texture, SDL_Renderer* renderer, double angle)
{
    //get the width and height from the texture
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    //since SDL_RenderCopyEx uses the center of the texture use the max
    int max = (w > h) ? w : h;
    SDL_Texture *rotatedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, max, max);
    SDL_SetRenderTarget(renderer, rotatedTexture);
    SDL_SetTextureBlendMode(rotatedTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Rect srcRect = {0, 0, w, h};
    SDL_Rect destRect = {0, 0, max, max};
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, nullptr, SDL_FLIP_NONE);
    SDL_SetRenderTarget(renderer, nullptr);
    return rotatedTexture;
}