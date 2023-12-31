#pragma once


#include <vector>
#include "../include/renderer.hpp"
#include "../include/level.hpp"
#include "../include/event_manager.hpp"
#include "../include/levelEditor.hpp"
#include "../include/mainMenu.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    void cleanUp(int exitCode); // Ajout de la méthode cleanUp
    void RestartGame();
    float currentTime, accumulator{0.0f}, timeStep; // Membres pour le calcul des frames de logique de jeu
    Player player;
    bool playerDead;
    int levelPtr;
    bool leftTileScreen = false;
    std::vector<Level> levels;
    Level currentLevel;
    LevelEditor levelEditor;
    bool inEditorMode = false;
    MainMenu mainMenu;
    bool inMainMenu = true;
    Renderer *renderer;
    EventManager eventManager;
};
