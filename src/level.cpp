#include "../include/level.hpp"
#include "../include/utils.hpp"
#include "../include/event_manager.hpp"
#include <SDL2/SDL.h>
#include <iostream>

struct LevelDataEntry {
    std::string key;
    std::string value;
};

Level::Level(std::string levelDataFileName, std::map<std::string, TileInfo> &tileInfoMap, SDL_Renderer *renderer) {
    // find knight_m_idle_anim_f0 in tileInfoMap
    TileInfo knightIdleTileInfo = tileInfoMap["knight_m_idle_anim_f0"];
    TileInfo knightWeaponTileInfo = tileInfoMap["weapon_golden_sword"];

    // load the tileset
    SDL_Texture *tileset = IMG_LoadTexture(renderer, "res/gfx/tileset.png");
    // check if the tileset was loaded
    if (tileset == nullptr) {
        std::cerr << "Error loading tileset: " << SDL_GetError() << std::endl;
        return;
    }
    // get the size of the tileset
    // load the tile from the tileset
    SDL_Texture *knightIdleTex = utils::loadTileFromTileset(tileset, knightIdleTileInfo, renderer);
    SDL_Texture *knightWeaponTex = utils::loadTileFromTileset(tileset, knightWeaponTileInfo, renderer);

    Player p = Player(Vector2f(5, 5), knightIdleTex,knightWeaponTex, knightIdleTileInfo.w, knightIdleTileInfo.h);

    player = p;
}


void Level::update(EventManager &eventManager){
    player.update(eventManager);
}

void Level::render(SDL_Renderer *renderer){
    // render the player
    player.render(renderer);
}
