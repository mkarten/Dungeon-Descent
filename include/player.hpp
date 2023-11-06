#pragma once

#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "event_manager.hpp"

struct Weapon{
    SDL_Texture *texture;
    double angle;
};

class Player : public Entity{
public:
    Player() {}
    Player(Vector2f p_pos, SDL_Texture *p_tex,SDL_Texture *w_tex, int width, int height, std::pair<int, int> spriteSheetConfiguration);
    Weapon weapon;
    void render(SDL_Renderer *renderer);
    void update(EventManager &eventManager);
};