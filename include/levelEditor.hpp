#pragma once
#include "level.hpp"
#include "utils.hpp"
#include <string>


class LevelEditor : public Level
{
public:
    LevelEditor(SDL_Renderer *renderer,Player &player ,std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap)
            : Level(renderer, player, levelDataFileName, tilesetTex, tilesInfoMap)
    {
        this->tilesetTex = tilesetTex;
        this->tilesInfoMap = tilesInfoMap;
        this->renderer = renderer;
        placingCursor.w = 16;
        placingCursor.h = 16;
    }
    LevelEditor() {}
    void update(EventManager &eventManager);
    void render(SDL_Renderer *renderer);
private:
    SDL_Texture *tilesetTex;
    utils::TileMap tilesInfoMap;
    SDL_Rect placingCursor;
    SDL_Renderer *renderer;

};