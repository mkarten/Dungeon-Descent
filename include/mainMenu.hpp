#pragma once

#include "level.hpp"
#include "constants.hpp"

class MainMenu : public Level
{
public:
    MainMenu(SDL_Renderer *renderer,Player *player ,std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap)
            : Level(renderer, player, levelDataFileName, tilesetTex, tilesInfoMap){

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

        // set the start button position at the center of the screen
        startButtonPos = Vector2i(WINDOW_WIDTH/2, WINDOW_HEIGHT - 400);
        startButtonSize = Vector2i(300, 100);
        startGameButton = {startButtonPos.x - startButtonSize.x/2, startButtonPos.y - startButtonSize.y/2, startButtonSize.x, startButtonSize.y};

        // set the quit button position at the center of the screen
        quitButtonPos = Vector2i(WINDOW_WIDTH/2, WINDOW_HEIGHT - 200);
        quitButtonSize = Vector2i(300, 100);
        quitGameButton = {quitButtonPos.x - quitButtonSize.x/2, quitButtonPos.y - quitButtonSize.y/2, quitButtonSize.x, quitButtonSize.y};

    }
    MainMenu() {}
    void update(EventManager &eventManager);
    void render(SDL_Renderer *renderer);

    Vector2i startButtonPos;
    Vector2i startButtonSize;
    SDL_Rect startGameButton;
    bool startButtonHovered = false;
    Vector2i quitButtonPos;
    Vector2i quitButtonSize;
    SDL_Rect quitGameButton;
    bool quitButtonHovered = false;


};
