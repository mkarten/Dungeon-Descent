#include "../include/weapon.hpp"
#include "../include/event_manager.hpp"
#include "../include/constants.hpp"
#include <math.h>
#include <iostream>

Weapon::Weapon(Vector2f p_pos, SDL_Texture *p_tex, int width, int height) :
    Entity(p_pos, p_tex, width, height){
    angle = 0;
}

void Weapon::render(SDL_Renderer *renderer){
    SDL_Rect dst{static_cast<int>(pos.x*SCALE_FACTOR), static_cast<int>(pos.y*SCALE_FACTOR), width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopyEx(renderer,tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void Weapon::update(EventManager &eventManager){
    //point the center of the weapon at the mouse
    angle = atan2(eventManager.mouse.y - ((pos.y + height/2)*SCALE_FACTOR), eventManager.mouse.x - ((pos.x + width/2)*SCALE_FACTOR)) * 180 / M_PI;
}

