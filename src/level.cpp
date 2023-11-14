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
    levelData.DeserializeFromFile(levelDataFileName);

    // copy the static entities from the level data to the level
    staticEntities = levelData.getStaticEntities();

    // set the texture of the static entities to the tileset texture
    for (int i = 0; i < staticEntities.size(); i++) {
        // get the texture from the tileset
        staticEntities[i].tex = utils::loadTileFromTileset(tilesetTex, tilesInfoMap[staticEntities[i].texName], renderer);
        // check if the texture need to be tiled
        if (staticEntities[i].width > 0 || staticEntities[i].height>0){
            staticEntities[i].tex = utils::textureTiling(staticEntities[i].tex, renderer, staticEntities[i].width, staticEntities[i].height);
        } else{
            SDL_QueryTexture(staticEntities[i].tex, NULL, NULL, &staticEntities[i].width, &staticEntities[i].height);
        }

    }

    // set the player to the player passed in from the main game
    player = Gplayer;

    // position the player at the spawn point
    player.pos = levelData.getPlayerSpawnPoint();
}


void Level::update(EventManager &eventManager){
    // detect a right click
    if (eventManager.mouse.Buttons[SDL_BUTTON_LEFT] && !eventManager.mouse.LastButtons[SDL_BUTTON_LEFT]) {
        // set the player position to the mouse position
        player.pos.x = eventManager.mouse.x/SCALE_FACTOR;
        player.pos.y = eventManager.mouse.y/SCALE_FACTOR;
    }

    // update the player
    player.update(eventManager);
}

void Level::render(SDL_Renderer *renderer){
    // render the static entities
    for (int i = 0; i < staticEntities.size(); i++) {
        staticEntities[i].render(renderer);
    }
    // render the player
    player.render(renderer);
    // print the level name for debug purposes
    utils::renderText(renderer, getLevelName(), 0, WINDOW_HEIGHT-100, SDL_Color {0, 0, 0});
}

LevelData::LevelData() {
    levelName = "default";
}

LevelData::~LevelData() {

}

bool LevelData::Deserialize(const rapidjson::Value &obj) {
    setLevelName(obj["levelName"].GetString());
    // check if the levelname was set
    if (getLevelName().empty()) {
        std::cout << "Error: levelName not found in level data" << std::endl;
        return false;
    }


    // check if the playerSpawnPoint was set
    rapidjson::Value::ConstMemberIterator itr = obj.FindMember("playerSpawnPoint");
    if (itr == obj.MemberEnd()) {
        std::cout << "Error: playerSpawnPoint not found in level data" << std::endl;
        return false;
    }
    // check if the x and y values of the playerSpawnPoint were set
    rapidjson::Value::ConstMemberIterator itr2 = itr->value.FindMember("x");
    if (itr2 == itr->value.MemberEnd()) {
        std::cout << "Error: playerSpawnPoint.x not found in level data" << std::endl;
        return false;
    }
    // check if the x and y values of the playerSpawnPoint were set
    rapidjson::Value::ConstMemberIterator itr3 = itr->value.FindMember("y");
    if (itr3 == itr->value.MemberEnd()) {
        std::cout << "Error: playerSpawnPoint.y not found in level data" << std::endl;
        return false;
    }
    // set the playerSpawnPoint
    setPlayerSpawnPoint(Vector2f(itr2->value.GetDouble(), itr3->value.GetDouble()));

    // check if the staticEntities array was set
    itr = obj.FindMember("staticEntities");
    if (itr == obj.MemberEnd()) {
        std::cout << "Error: staticEntities not found in level data" << std::endl;
        return false;
    }
    // check if the staticEntities array is an array
    if (!itr->value.IsArray()) {
        std::cout << "Error: staticEntities is not an array in level data" << std::endl;
        return false;
    }


    // iterate through the staticEntities array and print each object in the array
    for (rapidjson::SizeType i = 0; i < itr->value.Size(); i++) {
        // check if the object in the array is an object
        if (!itr->value[i].IsObject()) {
            std::cout << "Error: staticEntities[" << i << "] is not an object in level data" << std::endl;
            return false;
        }
        auto tempObj = itr->value[i].GetObject();
        rapidjson::Value::ConstMemberIterator texNameVal = tempObj.FindMember("textureName");
        if (texNameVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].textureName not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator xVal = tempObj.FindMember("x");
        if (xVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].x not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator yVal = tempObj.FindMember("y");
        if (yVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].y not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator collidableVal = tempObj.FindMember("collidable");
        if (collidableVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].collidable not found in level data" << std::endl;
            return false;
        }
        int w = 0;
        int h = 0;
        // if present, get the width and height of the static entity
        rapidjson::Value::ConstMemberIterator widthVal = tempObj.FindMember("width");
        if (widthVal != tempObj.MemberEnd()) {
            w = widthVal->value.GetInt();
        }
        rapidjson::Value::ConstMemberIterator heightVal = tempObj.FindMember("height");
        if (heightVal != tempObj.MemberEnd()) {
            h = heightVal->value.GetInt();
        }

        // add the static entity to the staticEntities vector
        staticEntities.emplace_back(Vector2f(xVal->value.GetDouble(), yVal->value.GetDouble()), texNameVal->value.GetString(),w,h,collidableVal->value.GetBool());
    }
    return true;
}

bool LevelData::Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const {
    writer->StartObject();
        writer->String("levelName");
        writer->String(levelName.c_str());

        writer->String("playerSpawnPoint");
        writer->StartObject();
            writer->String("x");
            writer->Double(playerSpawnPoint.x);
            writer->String("y");
            writer->Double(playerSpawnPoint.y);
        writer->EndObject();

    writer->EndObject();
    return true;
}

