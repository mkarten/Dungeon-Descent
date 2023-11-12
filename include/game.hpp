#pragma once


#include <vector>
#include "../include/renderer.hpp"
#include "../include/level.hpp"
#include "../include/event_manager.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    void cleanUp(); // Ajout de la méthode cleanUp
    float currentTime, accumulator{0.0f}, timeStep; // Membres pour le calcul des frames de logique de jeu
    Player player;
    Level currentLevel;
    Renderer renderer;
    EventManager eventManager;
};
