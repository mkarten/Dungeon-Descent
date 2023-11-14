#pragma once

#include "entity.hpp"
#include <string>

class StaticEntity : public Entity
{
public:
    StaticEntity(Vector2f p_pos, std::string texName, int width, int height, bool collidable)
            : Entity(p_pos, nullptr, width, height)
    {
        this->texName = texName;
        this->collidable = collidable;
    }
    StaticEntity() {}
    SDL_Rect getRect(){return {static_cast<int>(pos.x), static_cast<int>(pos.y), width, height};};
    void render(SDL_Renderer *renderer);
    std::string texName;
    bool collidable = false;

};