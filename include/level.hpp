#pragma once

#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "../include/player.hpp"
#include "../include/tile_info.hpp"
#include "../include/event_manager.hpp"
#include <vector>
#include <string>
#include <map>

struct LevelData {
    std::string levelName;
    void loadFromFile(std::string filename);
    void exportToFile(std::string filename);
};

class Level
{
public:
    Level(SDL_Renderer *renderer,Player &player ,std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap);
    Level() {}
    void update(EventManager &eventManager);
    void render(SDL_Renderer *renderer);

    // getters
    std::string getLevelName() const { return levelData.levelName; }
private:
    std::vector<Entity> entities;
    Player player;
    LevelData levelData;
};