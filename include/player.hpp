#pragma once

#include <SDL2/SDL.h>
#include "../include/entity.hpp"

class Player : public Entity{
public:
    Player() {}
    Player(Vector2f p_pos, SDL_Texture *p_tex, int width, int height, std::pair<int, int> spriteSheetConfiguration);
    void update(std::vector<SDL_Event> &events);
    void render(SDL_Renderer *renderer);
};