#pragma once


#include <vector>
#include "../include/renderer.hpp"
#include "../include/level.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    void cleanUp(); // Ajout de la méthode cleanUp
    float currentTime, accumulator{0.0f}, timeStep; // Membres pour le calcul des frames de logique de jeu
    Level currentLevel;
    Renderer renderer;
};
