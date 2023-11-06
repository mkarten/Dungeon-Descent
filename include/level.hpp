#pragma once

#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "../include/player.hpp"
#include "../include/tile_info.hpp"
#include <vector>
#include <string>
#include <map>

class Level
{
public:
    Level(std::string basicString, std::map<std::string, TileInfo> &tileInfoMap, SDL_Renderer *renderer);
    Level() {}
    void update(std::vector<SDL_Event> &events);
    void render(SDL_Renderer *renderer);
private:
    std::vector<Entity> entities;
    Player player;
};