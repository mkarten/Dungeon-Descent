#pragma once

#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "event_manager.hpp"


class Weapon : public Entity{
public:
    Weapon() {}
    Weapon(Vector2f p_pos, SDL_Texture *p_tex, int width, int height);
    double angle;
    void render(SDL_Renderer *renderer);
    void update(EventManager &eventManager);
};