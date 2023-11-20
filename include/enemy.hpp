#pragma once

#include "entity.hpp"
#include "event_manager.hpp"

class Enemy : public Entity
{
    public:
        Enemy();
        Enemy(Vector2f p_pos, SDL_Texture *p_tex, int width, int height,int triggerDistance,int damage,Vector2f *PlayerPos);
        void update(EventManager &eventManager);
        void render(SDL_Renderer *renderer);
    private:
        Vector2f *PlayerPos;
        int triggerDistance;
        bool triggered;
        int damage;
};