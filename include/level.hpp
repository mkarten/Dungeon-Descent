#pragma once

#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "../include/player.hpp"
#include "../include/tile_info.hpp"
#include "../include/event_manager.hpp"
#include <vector>
#include <string>
#include <map>
#include "../include/json.hpp"

// LevelData class
class LevelData : public JSON
{
public:
    LevelData();
    ~LevelData();

    virtual bool Deserialize(const rapidjson::Value& obj);
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

    // getters and setters
    std::string getLevelName() const { return levelName; }
    void setLevelName(std::string lName) { this->levelName = lName; }

private:
    std::string levelName;
};




// Level class
class Level
{
public:
    Level(SDL_Renderer *renderer,Player &player ,std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap);
    Level() {}
    void update(EventManager &eventManager);
    void render(SDL_Renderer *renderer);

    // getters
    std::string getLevelName() const { return levelData.getLevelName(); }
private:
    std::vector<Entity> entities;
    Player player;
    LevelData levelData;
};