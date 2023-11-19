#pragma once

#include <SDL2/SDL.h>
#include "../include/vector.hpp"
#include <utility>
#include <vector>

class Entity
{
public:
    Entity(Vector2f p_pos, SDL_Texture *p_tex, int width, int height)
            : pos(p_pos), tex(p_tex), width(width), height(height)
    {
    }
    Entity() {}
    bool isCollidingWith(const Entity &other) const;
    Vector2f pos;
    SDL_Texture *tex;
    int width, height;
};