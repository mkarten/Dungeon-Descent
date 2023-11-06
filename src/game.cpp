#include "../include/game.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"


// Constructeur
Game::Game()
    : renderer(Renderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT))
    , currentLevel(Level())
{
    currentTime = utils::hireTimeInSeconds();
    timeStep = TIME_STEP;

}


// Destructeur
Game::~Game()
{
    cleanUp();
}


// Boucle principale du jeu
void Game::run()
{
    // for now handle events here
    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }
        // dispatch events
        // update game logic
        // render
        renderer.render(currentLevel);
    }
}


// Nettoyage des ressources
void Game::cleanUp()
{
    SDL_Quit();       // Nettoyage des ressources de SDL
}
