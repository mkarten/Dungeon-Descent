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

    // read the json in the level data file
    // https://gotask.net/programming/serialize-and-deserialize-object-in-cpp-using-rapidjson/
    levelData.DeserializeFromFile(levelDataFileName);
    std::cout << "Level name: " << levelData.getLevelName() << std::endl;
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

LevelData::LevelData() {
    levelName = "default";
}

LevelData::~LevelData() {

}

bool LevelData::Deserialize(const rapidjson::Value &obj) {
    setLevelName(obj["levelName"].GetString());
    return true;
}

bool LevelData::Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const {
    writer->StartObject();
        writer->String("levelName");
        writer->String(levelName.c_str());
    writer->EndObject();
    return true;
}

