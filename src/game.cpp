#include "../include/game.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"
#include "../include/levelEditor.hpp"
#include <iostream>
#include <map>
#include "../include/animation.hpp"

//TODO: bombs are enemies in the level

Game::Game()
{
    renderer = new Renderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    RestartGame();
}

void Game::RestartGame()
{
    // clean up all before restarting
    levels.clear();

    currentTime = utils::hireTimeInSeconds();
    timeStep = TIME_STEP;
    utils::TileMap tilesInfoMap = utils::LoadTileInfo("res/tile_offset_map.txt");

    // load the tileset
    SDL_Texture *tileset = IMG_LoadTexture(renderer->getRenderer(), "res/gfx/tileset.png");
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
    SDL_Texture *knightWeaponTex = utils::loadTileFromTileset(tileset, knightWeaponTileInfo, renderer->getRenderer());

    // load all the animations
    animation::loadAllAnimations(tileset, tilesInfoMap, renderer->getRenderer());

    // load the heart textures
    utils::loadHeartTextures(tileset, tilesInfoMap, renderer->getRenderer());

    // load the music and sound effects
    utils::loadMusicAndSoundEffects();

    // create the player
    player = Player(Vector2f(0, 0), &animation::knight_mAnimations,knightWeaponTex, knightIdleTileInfo.w, knightIdleTileInfo.h);

    // create the level
    levels.emplace_back(renderer->getRenderer(), &player, "res/levels/level1.json", tileset, tilesInfoMap);
    levels.emplace_back(renderer->getRenderer(), &player, "res/levels/level2.json", tileset, tilesInfoMap);
    levels.emplace_back(renderer->getRenderer(), &player, "res/levels/level3.json", tileset, tilesInfoMap);
    levels.emplace_back(renderer->getRenderer(), &player, "res/levels/level4.json", tileset, tilesInfoMap);
    levels.emplace_back(renderer->getRenderer(), &player, "res/levels/level5.json", tileset, tilesInfoMap);
    levels.emplace_back(renderer->getRenderer(), &player, "res/levels/level6.json", tileset, tilesInfoMap);
    levelEditor = LevelEditor(renderer->getRenderer(), &player, "res/levels/editor.json", tileset, tilesInfoMap);
    mainMenu = MainMenu(renderer->getRenderer(), &player,"res/levels/mainMenu.json", tileset, tilesInfoMap);

    inMainMenu = true;
    leftTileScreen = false;

    levelPtr = 0;
    currentLevel = levels[levelPtr];
    player.pos = currentLevel.playerSpawnPoint;
    player.weapon.pos = player.pos;

    // set the camera default position
    renderer->camera.pos = Vector2f(0, 0);

    // restart the music
    utils::playMusic();
}




// Destructor
Game::~Game()
{
    cleanUp(0);
}


// Main game loop
void Game::run()
{
    srand( (unsigned)time(NULL) );
    bool GameIsRunning = true;
    utils::playMusic();
    while (GameIsRunning)
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

        // handle the messages from the event manager
        for (auto &message : eventManager.getMessages(Messages::IDs::GAME)) {
            if (message.message == Messages::START_GAME) {
                inMainMenu = false;
                leftTileScreen = true;
                eventManager.clearMessage(message.MessageID);
            }
            if (message.message == Messages::QUIT_GAME) {
                GameIsRunning = false;
                eventManager.clearMessage(message.MessageID);
                continue;
            }
            if (message.message == Messages::ENTER_EDITOR_MODE) {
                inEditorMode = !inEditorMode;
                eventManager.clearMessage(message.MessageID);
            }
            if (message.message == Messages::GO_TO_NEXT_LEVEL) {
                levelPtr++;
                if (levelPtr >= levels.size()) {
                    levelPtr -=1;
                    //send a message to the level to display a win message
                    eventManager.sendMessage(Messages::IDs::LEVEL, Messages::IDs::GAME, Messages::WIN_GAME);
                    eventManager.clearMessage(message.MessageID);
                    continue;
                }
                // add one damage to the weapon
                player.weapon.dammage += 1;
                currentLevel = levels[levelPtr];
                player.weapon.isOnCooldown = false;
                player.pos = currentLevel.playerSpawnPoint;
                player.weapon.pos = player.pos;
                eventManager.clearMessage(message.MessageID);
            }
            if (message.message == Messages::GAME_RESTART) {
                RestartGame();
                eventManager.clearMessage(message.MessageID);
                continue;
            }
        }
        if (inMainMenu){
            mainMenu.update(eventManager);
            mainMenu.render(renderer);
        } else if (inEditorMode){
            levelEditor.update(eventManager);
            levelEditor.render(renderer);
        } else {
            // update the game logic
            currentLevel.update(eventManager);

            // clear the screen
            SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(renderer->getRenderer());
            // render the game
            currentLevel.render(renderer);
        }

        // if i press the plus key, i go to the next level
        if (eventManager.Keys[SDL_SCANCODE_KP_PLUS] && !eventManager.LastKeys[SDL_SCANCODE_KP_PLUS]) {
            eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::GAME, Messages::GO_TO_NEXT_LEVEL);
        }

        if (eventManager.Keys[SDL_SCANCODE_ESCAPE] && !eventManager.LastKeys[SDL_SCANCODE_ESCAPE]) {
            inEditorMode = !inEditorMode;
        }

        if (eventManager.Keys[SDL_SCANCODE_SPACE] && !eventManager.LastKeys[SDL_SCANCODE_SPACE] && leftTileScreen) {
            // put the camera at 0 0
            renderer->camera.pos = Vector2f(0, 0);
            inMainMenu = !inMainMenu;
        }


        SDL_RenderPresent(renderer->getRenderer());
    }
}


// Ressources cleanup
void Game::cleanUp(int exitCode)
{
    IMG_Quit();       // Nettoyage des ressources de SDL_image
    SDL_Quit();       // Nettoyage des ressources de SDL
    exit(exitCode);   // Fermeture du programme
}

