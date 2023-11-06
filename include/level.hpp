#pragma once

#include <SDL2/SDL.h>

class Level
{
public:
    Level();
    void dispatch();
    void update();
    void render(SDL_Renderer *renderer);
private:
    // entities
};