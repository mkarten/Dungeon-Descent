#include "../include/utils.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <windows.h>

namespace utils{

    TTF_Font* OpenSans;
    bool fontLoaded = false;

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

    void logLastSDLError(){
        std::cerr << SDL_GetError() << std::endl;
    }

    void loadFont(){
        OpenSans = TTF_OpenFont("res/fonts/OpenSans.ttf", 32);
        if (OpenSans == nullptr) {
            logLastSDLError();
            exit(1);
        }
        fontLoaded = true;
    }

    TTF_Font* getFont(){
        if (!fontLoaded) {
            loadFont();
        }
        return OpenSans;
    }

    void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color){
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(getFont(), text.c_str(), color);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect Message_rect= {x, y, 0, 0};
        SDL_QueryTexture(Message, nullptr, nullptr, &Message_rect.w, &Message_rect.h);
        SDL_RenderCopy(renderer, Message, nullptr, &Message_rect);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);
    }

    SDL_Texture* textureTiling(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height) {
        // Get the original texture dimensions
        int originalWidth, originalHeight;
        SDL_QueryTexture(texture, NULL, NULL, &originalWidth, &originalHeight);

        // Calculate the number of tiles needed in each direction
        int numTilesX = (width + originalWidth - 1) / originalWidth;
        int numTilesY = (height + originalHeight - 1) / originalHeight;

        // Create a target texture for tiling
        SDL_Texture* tiledTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
        SDL_SetRenderTarget(renderer, tiledTexture);

        // Clear the target texture
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // Assuming black background
        SDL_RenderClear(renderer);

        // Tile the original texture on the target texture
        for (int i = 0; i < numTilesX; ++i) {
            for (int j = 0; j < numTilesY; ++j) {
                SDL_Rect destRect = {i * originalWidth, j * originalHeight, originalWidth, originalHeight};
                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }
        }

        // Reset the render target to the default
        SDL_SetRenderTarget(renderer, NULL);

        return tiledTexture;
    }

    bool isPointInRect(int x, int y, SDL_Rect rect){
        return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
    }

    std::string chooseFile(const std::string& title, const std::string& initialPath, const std::string& filter){
        OPENFILENAME ofn;
        char szFileName[MAX_PATH] = "save.json";

        ZeroMemory(&ofn, sizeof(ofn));

        ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
        ofn.hwndOwner = nullptr;
        ofn.lpstrFilter = filter.c_str();
        ofn.lpstrFile = szFileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = "txt";
        ofn.lpstrTitle = title.c_str();
        ofn.lpstrInitialDir = initialPath.c_str();

        if(GetSaveFileNameA(&ofn)){
            return ofn.lpstrFile;
        }
    }

    std::string getCurrentWorkingDirectory(){
        char* cwd = SDL_GetBasePath();
        std::string path(cwd);
        SDL_free(cwd);
        return path;
    }

}

