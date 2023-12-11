#include "../include/utils.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <valarray>

namespace utils{

    TTF_Font* OpenSans;
    bool fontLoaded = false;
    SDL_Texture *fullHeart;
    SDL_Texture *halfHeart;
    SDL_Texture *emptyHeart;
    bool heartTexturesLoaded = false;

    Mix_Music *music;
    Mix_Chunk *enemyHitSound;
    Mix_Chunk *enemyDeathSound;

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

    std::vector<SDL_Texture*> loadTilesFromTileset(SDL_Texture* tileset, std::vector<TileInfo> tileInfos, SDL_Renderer* renderer)
    {
        std::vector<SDL_Texture*> tiles;
        for (TileInfo tileInfo : tileInfos)
        {
            tiles.push_back(loadTileFromTileset(tileset, tileInfo, renderer));
        }
        return tiles;
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
        // render the text with x and y being the center of the text
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(getFont(), text.c_str(), color);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect Message_rect; //create a rect
        Message_rect.x = x - surfaceMessage->w/2;  //controls the rect's x coordinate
        Message_rect.y = y - surfaceMessage->h/2; // controls the rect's y coordinte
        Message_rect.w = surfaceMessage->w; // controls the width of the rect
        Message_rect.h = surfaceMessage->h; // controls the height of the rect
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
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

        // Set the blend mode to alpha blending
        SDL_SetTextureBlendMode(tiledTexture, SDL_BLENDMODE_BLEND);

        // Clear the target texture with transparent black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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
        }else{
            return "";
        }
    }

    std::string getCurrentWorkingDirectory(){
        char* cwd = SDL_GetBasePath();
        std::string path(cwd);
        SDL_free(cwd);
        return path;
    }

    int distance(Vector2f v1, Vector2f v2){
        return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
    }

    Vector2f normalize(Vector2f v){
        float length = sqrt(pow(v.x, 2) + pow(v.y, 2));
        return {v.x / length, v.y / length};
    }

    void loadHeartTextures(SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap,SDL_Renderer *renderer){
        fullHeart = utils::loadTileFromTileset(tilesetTex, tilesInfoMap["ui_heart_full"], renderer);
        halfHeart = utils::loadTileFromTileset(tilesetTex, tilesInfoMap["ui_heart_half"], renderer);
        emptyHeart = utils::loadTileFromTileset(tilesetTex, tilesInfoMap["ui_heart_empty"], renderer);
        heartTexturesLoaded = true;
    }

    SDL_Texture* getHeartFullTexture(){
        if (!heartTexturesLoaded) {
            std::cerr << "Heart textures not loaded" << std::endl;
            exit(1);
        }
        return fullHeart;
    }

    SDL_Texture* getHeartHalfTexture(){
        if (!heartTexturesLoaded) {
            std::cerr << "Heart textures not loaded" << std::endl;
            exit(1);
        }
        return halfHeart;
    }

    SDL_Texture* getHeartEmptyTexture(){
        if (!heartTexturesLoaded) {
            std::cerr << "Heart textures not loaded" << std::endl;
            exit(1);
        }
        return emptyHeart;
    }

    float lerpf(float a, float b, float t){
        return a + t * (b - a);
    }

    Vector2f lerpVector2f(Vector2f a, Vector2f b, float t){
        return {lerpf(a.x, b.x, t), lerpf(a.y, b.y, t)};
    }

    void loadMusicAndSoundEffects(){
        music = Mix_LoadMUS("res/sfx/music.wav");
        if (music == nullptr) {
            logLastSDLError();
            exit(1);
        }
        enemyHitSound = Mix_LoadWAV("res/sfx/enemy_hit.wav");
        if (enemyHitSound == nullptr) {
            logLastSDLError();
            exit(1);
        }
        enemyDeathSound = Mix_LoadWAV("res/sfx/enemy_death.wav");
        if (enemyDeathSound == nullptr) {
            logLastSDLError();
            exit(1);
        }
    }

    void playMusic(){
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(music, -1);
        }
    }

    void playEnemyHitSound(){
        Mix_PlayChannel(-1, enemyHitSound, 0);
    }

    void playEnemyDeathSound(){
        Mix_PlayChannel(-1, enemyDeathSound, 0);
    }

}

