#include "../include/level.hpp"
#include <SDL2/SDL.h>

Level::Level() {

}

void Level::dispatch() {
    // dispatch events to the entities
}

void Level::update() {
    // update the entities
}

void Level::render(SDL_Renderer *renderer){
    // for testing purposes just render a red rectangle
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 100;
    rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}