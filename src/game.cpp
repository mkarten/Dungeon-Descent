#include "../include/game.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"
#include "../include/levelEditor.hpp"
#include <iostream>
#include <map>



Game::Game()
{
    renderer = Renderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    currentTime = utils::hireTimeInSeconds();
    timeStep = TIME_STEP;
    utils::TileMap tilesInfoMap = utils::LoadTileInfo("res/tile_offset_map.txt");

    // load the tileset
    SDL_Texture *tileset = IMG_LoadTexture(renderer.getRenderer(), "res/gfx/tileset.png");
    // check if the tileset was loaded
    if (tileset == nullptr) {
        utils::logLastSDLError();
        // go to cleanUp
        cleanUp(1);
    }
    // load the player tiles info
    TileInfo knightIdleTileInfo = tilesInfoMap["knight_m_idle_anim_f0"];
    TileInfo knightWeaponTileInfo = tilesInfoMap["weapon_golden_sword"];

    // load the player tiles textures
    SDL_Texture *knightIdleTex = utils::loadTileFromTileset(tileset, knightIdleTileInfo, renderer.getRenderer());
    SDL_Texture *knightWeaponTex = utils::loadTileFromTileset(tileset, knightWeaponTileInfo, renderer.getRenderer());

    // create the player
    player = Player(Vector2f(0, 0), knightIdleTex,knightWeaponTex, knightIdleTileInfo.w, knightIdleTileInfo.h);

    // create the level
    levels.emplace_back(renderer.getRenderer(), &player, "res/levels/debug.json", tileset, tilesInfoMap);
    levelEditor = LevelEditor(renderer.getRenderer(), &player, "res/levels/editor.json", tileset, tilesInfoMap);
    levelPtr = 0;
    currentLevel = levels[levelPtr];

    // TODO: Create the levels based on all the level data files

}



// Destructor
Game::~Game()
{
    cleanUp(0);
}


// Main game loop
void Game::run()
{
    while (eventManager.GameIsRunning)
    {
        // calculate the DeltaTime and sleep if needed
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;

        // if the frameTime is too small, sleep the thread
        if (frameTime < timeStep) {
            SDL_Delay((timeStep - frameTime) * 1000);
        }

        // update the event manager with the events
        eventManager.update();

        // if the user pressed the escape key, change the level
        if (eventManager.Keys[SDL_SCANCODE_ESCAPE] && !eventManager.LastKeys[SDL_SCANCODE_ESCAPE]) {
            inEditorMode = !inEditorMode;
        }
        if (inEditorMode){
            levelEditor.update(eventManager);
            levelEditor.render(renderer.getRenderer());
        } else {
            // update the game logic
            currentLevel.update(eventManager);

            // render the game
            renderer.render(currentLevel);
        }



        int roundFps = static_cast<int>(1.0f / frameTime);
        utils::renderText(renderer.getRenderer(), "FPS: " + std::to_string(roundFps), 0, WINDOW_HEIGHT-50, {0, 0, 0, 255});

        SDL_RenderPresent(renderer.getRenderer());
    }
}


// Ressources cleanup
void Game::cleanUp(int exitCode)
{
    IMG_Quit();       // Nettoyage des ressources de SDL_image
    SDL_Quit();       // Nettoyage des ressources de SDL
    exit(exitCode);   // Fermeture du programme
}
