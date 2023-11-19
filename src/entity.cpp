#include "../include/entity.hpp"


bool Entity::isCollidingWith(const Entity &other) const
{
    return pos.x < other.pos.x + other.width &&
           pos.x + width > other.pos.x &&
           pos.y < other.pos.y + other.height &&
           pos.y + height > other.pos.y;
}