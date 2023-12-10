#pragma once

#include <SDL2/SDL.h>
#include "../include/vector.hpp"
#include <utility>
#include <vector>
#include "../include/utils.hpp"

struct CollisionInfo
{
    bool isCollidingTop;
    bool isCollidingBottom;
    bool isCollidingLeft;
    bool isCollidingRight;
};

class Entity
{
public:
    Entity(Vector2f p_pos, SDL_Texture *p_tex, int width, int height)
            : pos(p_pos), tex(p_tex), width(width), height(height)
    {
    }
    Entity() {}
    bool isCollidingWith(const Entity &other) const;
    CollisionInfo getCollisionInfo(const Entity &other) const;
    Vector2f pos;
    Vector2f lastPos;
    float speed;
    float maxSpeed;
    SDL_Texture *tex;
    std::string tag;
    int width, height;
};
