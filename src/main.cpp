#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/utils.hpp"
#include "../include/game.hpp"


// Initialise SDL2 et SDL2_image
bool initSDL()
{
    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }


    // Initialisation de SDL2_image
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Initialisation de SDL2_ttf
    if (TTF_Init() != 0)
    {
        std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    utils::loadFont();

    return true;
}


// Fonction principale du jeu
int runGame()
{
    // On initialise SDL2 et SDL2_image anvant de créer une instance de Game
    // car la classe Game utilise des types de SDL2 et SDL2_image
    if (!initSDL())
        return 1;


    Game game; // Crée une instance du jeu avec les constantes globales
    game.run();  // Exécute le jeu

    utils::logLastSDLError();
    return 0;
}


// Fonction principale du programme
int main(int argc, char *argv[])
{
    return runGame();
}
