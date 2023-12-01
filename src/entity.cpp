#include <limits>
#include <iostream>
#include "../include/entity.hpp"


bool Entity::isCollidingWith(const Entity &other) const
{
    return pos.x < other.pos.x + other.width &&
           pos.x + width > other.pos.x &&
           pos.y < other.pos.y + other.height &&
           pos.y + height > other.pos.y;
}

CollisionInfo Entity::getCollisionInfo(const Entity &other) const
{
    CollisionInfo info;
    info.isCollidingTop = false;
    info.isCollidingBottom = false;
    info.isCollidingLeft = false;
    info.isCollidingRight = false;

    // implement swept AABB collision detection

    // get the velocity of the current entity from the last position
    Vector2f velocity = pos - lastPos;

    // create dxEntry , dxExit , dyEntry , dyExit
    float dxEntry, dxExit;
    float dyEntry, dyExit;

    // if the velocity is positive, the entry point is the current position

    if(velocity.x > 0.0f)
    {
        dxEntry = other.pos.x - (pos.x + width);
        dxExit = (other.pos.x + other.width) - pos.x;
    }
    else
    {
        dxEntry = (other.pos.x + other.width) - pos.x;
        dxExit = other.pos.x - (pos.x + width);
    }

    if(velocity.y > 0.0f)
    {
        dyEntry = other.pos.y - (pos.y + height);
        dyExit = (other.pos.y + other.height) - pos.y;
    }
    else
    {
        dyEntry = (other.pos.y + other.height) - pos.y;
        dyExit = other.pos.y - (pos.y + height);
    }

    // create txEntry , txExit , tyEntry , tyExit
    float txEntry, txExit;
    float tyEntry, tyExit;

    if (velocity.x == 0.0f)
    {
        txEntry = -std::numeric_limits<float>::infinity();
        txExit = std::numeric_limits<float>::infinity();
    }
    else
    {
        txEntry = dxEntry / velocity.x;
        txExit = dxExit / velocity.x;
    }

    if (velocity.y == 0.0f)
    {
        tyEntry = -std::numeric_limits<float>::infinity();
        tyExit = std::numeric_limits<float>::infinity();
    }
    else
    {
        tyEntry = dyEntry / velocity.y;
        tyExit = dyExit / velocity.y;
    }

    float entryTime = std::max(txEntry, tyEntry);
    float exitTime = std::min(txExit, tyExit);
    if (entryTime > exitTime ||  txEntry > 1.0f || tyEntry > 1.0f)
    {
        info.isCollidingTop = false;
        info.isCollidingBottom = false;
        info.isCollidingLeft = false;
        info.isCollidingRight = false;
        return info;
    }

    if (txEntry > tyEntry)
    {
        if (dxEntry < 0.0f)
        {
            info.isCollidingLeft = true;
        }
        else
        {
            info.isCollidingRight = true;
        }
    }
    else
    {
        if (dyEntry < 0.0f)
        {
            info.isCollidingTop = true;
        }
        else
        {
            info.isCollidingBottom = true;
        }
    }
    return info;
}