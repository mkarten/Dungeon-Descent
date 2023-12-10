#pragma once

#include <SDL2/SDL.h>
#include "entity.hpp"
#include "event_manager.hpp"
#include "utils.hpp"
#include "renderer.hpp"

class Weapon : public Entity{
public:
    Weapon() {}
    Weapon(Vector2f p_pos, SDL_Texture *p_tex, int width, int height, int dammage, float cooldown, float range);
    double angle;
    double newAngle;
    Vector2f newpos;
    Vector2f targetPos;
    Vector2f mousePos;
    int dammage;
    float cooldown;
    float cooldownTimer;
    bool isOnCooldown;
    float range;
    void render(Renderer *renderer);
    void update(EventManager &eventManager);
};