#pragma once

#include "entity.hpp"
#include "event_manager.hpp"

class Enemy : public Entity
{
    public:
        Enemy();
        Enemy(Vector2f p_pos, SDL_Texture *p_tex, int width, int height,int triggerDistance,int damage,Vector2f *PlayerPos,int health);
        void update(EventManager &eventManager);
        void render(SDL_Renderer *renderer);
        int getDamage() {return damage;}
        int getHealth() {return health;}
        void setHealth(int newHealth) {health = newHealth;}
        void dealDamage(int damage) {health -= damage;}
        Vector2f getLastPos() {return lastPos;}
    private:
        int health;
        int maxHealth;
        Vector2f *PlayerPos;
        int triggerDistance;
        bool triggered;
        int damage;
};