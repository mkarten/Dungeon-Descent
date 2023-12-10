#pragma once

#include "../include/renderer.hpp"
#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "event_manager.hpp"
#include "../include/weapon.hpp"

class Player : public Entity{
public:
    Player() {}
    Player(Vector2f p_pos, SDL_Texture *p_tex,SDL_Texture *w_tex, int width, int height);
    Weapon weapon;
    int health;
    int maxHealth;
    bool dead;
    SDL_Texture *fullHeart;
    SDL_Texture *halfHeart;
    SDL_Texture *emptyHeart;
    void render(Renderer *renderer);
    void update(EventManager &eventManager);
};