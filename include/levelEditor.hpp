#pragma once
#include "level.hpp"
#include "utils.hpp"
#include <string>
#include "renderer.hpp"


class LevelEditor : public Level
{
public:
    LevelEditor(SDL_Renderer *renderer,Player *player ,std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap)
            : Level(renderer, player, levelDataFileName, tilesetTex, tilesInfoMap)
    {
        this->tilesetTex = tilesetTex;
        this->tilesInfoMap = tilesInfoMap;
        this->renderer = renderer;
        placingCursor.w = 16;
        placingCursor.h = 16;
        // range over the tilesInfoMap and load all the textures
        tilesetTexsIndex = 0;
        for (auto &tileInfo : tilesInfoMap)
        {
            tilesetTexs.push_back(utils::loadTileFromTileset(tilesetTex, tileInfo.second, renderer));
            tilesetTexsNames.push_back(tileInfo.first);
        }
    }
    LevelEditor() {}
    void update(EventManager &eventManager);
    void render(Renderer *renderer);
private:
    SDL_Texture *tilesetTex;
    std::vector<SDL_Texture *> tilesetTexs;
    std::vector<std::string> tilesetTexsNames;
    int tilesetTexsIndex = 0;
    utils::TileMap tilesInfoMap;
    SDL_Rect placingCursor;
    SDL_Renderer *renderer;
    bool isPlacedTileCollidable = false;
    Vector2f mousePos;
    Vector2f mouvingDirection;
};