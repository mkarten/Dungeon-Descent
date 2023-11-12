#include "../include/game.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"
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
    currentLevel = Level(renderer.getRenderer(), player, "res/level_data.txt", tileset, tilesInfoMap);

    // TODO: Create the levels based on all the level data files

}



// Destructeur
Game::~Game()
{
    cleanUp(0);
}


// Boucle principale du jeu
void Game::run()
{
    while (eventManager.GameIsRunning)
    {
        eventManager.update();
        currentLevel.update(eventManager);
        renderer.render(currentLevel);
    }
}


// Nettoyage des ressources
void Game::cleanUp(int exitCode)
{
    IMG_Quit();       // Nettoyage des ressources de SDL_image
    SDL_Quit();       // Nettoyage des ressources de SDL
    exit(exitCode);   // Fermeture du programme
}
