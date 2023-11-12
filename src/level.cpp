#include "../include/level.hpp"
#include "../include/utils.hpp"
#include "../include/event_manager.hpp"
#include <SDL2/SDL.h>
#include <iostream>

struct LevelDataEntry {
    std::string key;
    std::string value;
};

Level::Level(SDL_Renderer *renderer, Player &Gplayer , std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap) {
    //TODO: load the level data from the file

    player = Gplayer;
}


void Level::update(EventManager &eventManager){
    player.update(eventManager);
}

void Level::render(SDL_Renderer *renderer){
    // render the player
    player.render(renderer);
}
