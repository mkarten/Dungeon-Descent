#include "../include/utils.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

namespace utils{

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

    void drawBoundingBox(SDL_Renderer* renderer, float x, float y, float w, float h, SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        // lines to make the box
        SDL_RenderDrawLine(renderer, x, y, x + w, y);
        SDL_RenderDrawLine(renderer, x + w, y, x + w, y + h);
        SDL_RenderDrawLine(renderer, x + w, y + h, x, y + h);
        SDL_RenderDrawLine(renderer, x, y + h, x, y);
        // lines to across the box
        SDL_RenderDrawLine(renderer, x, y, x + w, y + h);
        SDL_RenderDrawLine(renderer, x + w, y, x, y + h);
    }

    TileMap LoadTileInfo(const std::string& filename) {
        TileMap tileInfoMap;

        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier " << filename << std::endl;
            return tileInfoMap;
        }

        std::string tileName;
        int x, y, w, h;

        while (inputFile >> tileName >> x >> y >> w >> h) {
            // Insérer les informations de la tuile dans la map
            tileInfoMap[tileName] = {x, y, w, h};
        }

        inputFile.close();
        return tileInfoMap;
    }
}

