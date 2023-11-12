#include "../include/game.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"
#include "../include/tile_info.hpp"
#include <iostream>
#include <map>
#include <fstream>

using TileMap = std::map<std::string, TileInfo>;


TileMap LoadTileInfo(const std::string& filename) {
    TileMap tileInfoMap;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << filename << std::endl;
        return tileInfoMap;
    }

    std::string tileName;
    int x, y, w, h;

    while (inputFile >> tileName >> x >> y >> w >> h) {
        // Insérer les informations de la tuile dans la map
        tileInfoMap[tileName] = {x, y, w, h};
    }

    inputFile.close();
    return tileInfoMap;
}


Game::Game()
{
    renderer = Renderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    currentTime = utils::hireTimeInSeconds();
    timeStep = TIME_STEP;
    TileMap tileInfoMap = LoadTileInfo("res/tile_offset_map.txt");
    currentLevel = Level("res/level1.txt", tileInfoMap, renderer.getRenderer());
}



// Destructeur
Game::~Game()
{
    cleanUp();
}


// Boucle principale du jeu
void Game::run()
{
    // store events in a vector
    std::vector<SDL_Event> events;
    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT){
                running = false;
                continue;
            }else{
                events.push_back(event);
            }
        }
        eventManager.update(events);
        currentLevel.update(eventManager);
        events.clear();
        renderer.render(currentLevel);
    }
}


// Nettoyage des ressources
void Game::cleanUp()
{
    SDL_Quit();       // Nettoyage des ressources de SDL
}
