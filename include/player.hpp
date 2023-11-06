#pragma once

#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "event_manager.hpp"

class Player : public Entity{
public:
    Player() {}
    Player(Vector2f p_pos, SDL_Texture *p_tex, int width, int height, std::pair<int, int> spriteSheetConfiguration);
    void render(SDL_Renderer *renderer);
    void update(EventManager &eventManager);
};