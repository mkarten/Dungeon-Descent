#pragma once

#include "level.hpp"
#include "constants.hpp"
#include "renderer.hpp"

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

        // set the music volume up button position at right of the screen
        musicVolumeButtonUpPos = Vector2i(WINDOW_WIDTH - 300, WINDOW_HEIGHT - 200);
        musicVolumeButtonUpSize = Vector2i(50, 50);
        musicVolumeButtonUp = {musicVolumeButtonUpPos.x - musicVolumeButtonUpSize.x/2, musicVolumeButtonUpPos.y - musicVolumeButtonUpSize.y/2, musicVolumeButtonUpSize.x, musicVolumeButtonUpSize.y};

        // set the music volume down button position at right of the screen
        musicVolumeButtonDownPos = Vector2i(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 200);
        musicVolumeButtonDownSize = Vector2i(50, 50);
        musicVolumeButtonDown = {musicVolumeButtonDownPos.x - musicVolumeButtonDownSize.x/2, musicVolumeButtonDownPos.y - musicVolumeButtonDownSize.y/2, musicVolumeButtonDownSize.x, musicVolumeButtonDownSize.y};

        // set the sound effects volume up button position at right of the screen
        soundEffectsVolumeButtonUpPos = Vector2i(WINDOW_WIDTH - 300, WINDOW_HEIGHT - 100);
        soundEffectsVolumeButtonUpSize = Vector2i(50, 50);
        soundEffectsVolumeButtonUp = {soundEffectsVolumeButtonUpPos.x - soundEffectsVolumeButtonUpSize.x/2, soundEffectsVolumeButtonUpPos.y - soundEffectsVolumeButtonUpSize.y/2, soundEffectsVolumeButtonUpSize.x, soundEffectsVolumeButtonUpSize.y};

        // set the sound effects volume down button position at right of the screen
        soundEffectsVolumeButtonDownPos = Vector2i(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100);
        soundEffectsVolumeButtonDownSize = Vector2i(50, 50);
        soundEffectsVolumeButtonDown = {soundEffectsVolumeButtonDownPos.x - soundEffectsVolumeButtonDownSize.x/2, soundEffectsVolumeButtonDownPos.y - soundEffectsVolumeButtonDownSize.y/2, soundEffectsVolumeButtonDownSize.x, soundEffectsVolumeButtonDownSize.y};




    }
    MainMenu() {}
    void update(EventManager &eventManager);
    void render(Renderer *renderer);

    Vector2i startButtonPos;
    Vector2i startButtonSize;
    SDL_Rect startGameButton;
    bool startButtonHovered = false;
    Vector2i quitButtonPos;
    Vector2i quitButtonSize;
    SDL_Rect quitGameButton;
    bool quitButtonHovered = false;

    // music volume botton
    Vector2i musicVolumeButtonUpPos;
    Vector2i musicVolumeButtonUpSize;
    SDL_Rect musicVolumeButtonUp;
    bool musicVolumeButtonUpHovered = false;
    Vector2i musicVolumeButtonDownPos;
    Vector2i musicVolumeButtonDownSize;
    SDL_Rect musicVolumeButtonDown;
    bool musicVolumeButtonDownHovered = false;

    // sound effects volume botton
    Vector2i soundEffectsVolumeButtonUpPos;
    Vector2i soundEffectsVolumeButtonUpSize;
    SDL_Rect soundEffectsVolumeButtonUp;
    bool soundEffectsVolumeButtonUpHovered = false;
    Vector2i soundEffectsVolumeButtonDownPos;
    Vector2i soundEffectsVolumeButtonDownSize;
    SDL_Rect soundEffectsVolumeButtonDown;
    bool soundEffectsVolumeButtonDownHovered = false;

    int musicVolume = 50;
    int soundEffectsVolume = 50;




};
