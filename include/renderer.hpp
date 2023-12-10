#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vector.hpp"
#include "constants.hpp"

struct Camera{
    Vector2f pos;
    Vector2f newPos;
    int w = 0;
    int h = 0;
};

class Renderer{
public:
    Renderer(const char* title, int width, int height);
    Renderer() {}
    SDL_Window* getWindow(){
        return window;
    }
    SDL_Renderer* getRenderer(){
        return renderer;
    }
    Vector2f worldspaceToScreenspace(Vector2f worldspacePos){
        return {worldspacePos.x - camera.pos.x, worldspacePos.y - camera.pos.y};
    }
    Vector2f screenspaceToWorldspace(Vector2f screenspacePos){
        return {screenspacePos.x + camera.pos.x*SCALE_FACTOR, screenspacePos.y + camera.pos.y*SCALE_FACTOR};
    }
    Camera camera;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};