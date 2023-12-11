#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../include/utils.hpp"
#include "../include/game.hpp"


// Initialize SDL2 and SDL2_image
bool initSDL()
{
    // SDL2 init
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }


    // SDL2_image init
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // SDL2_mixer init
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Mix_OpenAudio Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    Mix_AllocateChannels(32);
    Mix_Volume(-1, MIX_MAX_VOLUME / 2);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    // SDL2_ttf init
    if (TTF_Init() != 0)
    {
        std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}


// Main function of the game
int runGame()
{
    if (!initSDL())
        return 1;


    Game game; // Create a new instance of the game
    game.run();  // Run the game

    utils::logLastSDLError();
    return 0;
}


// Main function of the program
int main(int argc, char *argv[])
{
    return runGame();
}
