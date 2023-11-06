#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/level.hpp"

class Renderer{
public:
    Renderer(const char* title, int width, int height);
    Renderer() {}
    void render(Level &level);
    SDL_Window* getWindow(){
        return window;
    }
    SDL_Renderer* getRenderer(){
        return renderer;
    }
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};