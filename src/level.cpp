#include "../include/level.hpp"
#include "../include/utils.hpp"
#include "../include/event_manager.hpp"
#include "../include/constants.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>

Level::Level(SDL_Renderer *renderer, Player &Gplayer , std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap) {
    //TODO: load the level data from the file

    //open the level data file
    std::ifstream levelDataFile(levelDataFileName);
    if(!levelDataFile.is_open()){
        std::cout << "Failed to open the level data file: " << levelDataFileName << std::endl;
        exit(1);
    }

    //read the json in the level data file
    levelDataFile >> levelData.levelName;

    player = Gplayer;
}


void Level::update(EventManager &eventManager){
    player.update(eventManager);
}

void Level::render(SDL_Renderer *renderer){
    // render the player
    player.render(renderer);
    // print the level name for debug purposes
    SDL_Color White = {0, 0, 0};
    utils::renderText(renderer, getLevelName(), 0, 0, White);
}
