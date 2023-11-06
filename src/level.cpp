#include "../include/level.hpp"
#include "../include/utils.hpp"
#include <SDL2/SDL.h>
#include <iostream>

struct LevelDataEntry {
    std::string key;
    std::string value;
};

Level::Level(std::string levelDataFileName, std::map<std::string, TileInfo> &tileInfoMap, SDL_Renderer *renderer) {
    // find knight_m_idle_anim_f0 in tileInfoMap
    TileInfo knightIdleTileInfo = tileInfoMap["knight_m_idle_anim_f0"];
    std::cout << "knightIdleTileInfo: " << knightIdleTileInfo.x << ", " << knightIdleTileInfo.y << ", " << knightIdleTileInfo.w << ", " << knightIdleTileInfo.h << std::endl;
    // get the texture from the tileset using the tileInfo
    // load the tileset
    SDL_Texture *tileset = IMG_LoadTexture(renderer, "res/gfx/tileset.png");
    // check if the tileset was loaded
    if (tileset == nullptr) {
        std::cerr << "Error loading tileset: " << SDL_GetError() << std::endl;
        return;
    }
    // get the size of the tileset
    // load the tile from the tileset
    SDL_Texture *knightIdleTex = loadTileFromTileset(tileset, knightIdleTileInfo, renderer);

    Player p = Player(Vector2f(5, 5), knightIdleTex, knightIdleTileInfo.w, knightIdleTileInfo.h, std::pair<int, int>(1, 1));

    player = p;
}


void Level::update(std::vector<SDL_Event> &events){

    player.update(events);
}

void Level::render(SDL_Renderer *renderer){
    // render the player
    player.render(renderer);
}
