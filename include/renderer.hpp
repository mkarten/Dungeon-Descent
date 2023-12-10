#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vector.hpp"

struct Camera{
    int x = 0;
    int y = 0;
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
        return {worldspacePos.x - camera.x, worldspacePos.y - camera.y};
    }
    Vector2f screenspaceToWorldspace(Vector2f screenspacePos){
        return {screenspacePos.x + camera.x, screenspacePos.y + camera.y};
    }
    Camera camera;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};