#pragma once

#include "renderer.hpp"
#include "entity.hpp"
#include "event_manager.hpp"

class Enemy : public Entity
{
    public:
        Enemy();
        Enemy(Vector2f p_pos,Animations *e_anim, int width, int height,int triggerDistance,int damage,Vector2f *PlayerPos,int health);
        void update(EventManager &eventManager);
        void render(Renderer *renderer);
        int getDamage() {return damage;}
        int getHealth() {return health;}
        void setHealth(int newHealth) {health = newHealth;}
        void dealDamage(int damage) {health -= damage;}
        Vector2f getLastPos() {return lastPos;}
        bool getWasHit() {return wasHit;}
        void setWasHit(bool newWasHit) {wasHit = newWasHit;}
        bool getTriggered() {return triggered;}
        void setTriggered(bool newTriggered) {triggered = newTriggered;}
        Vector2f *getPlayerPos() {return PlayerPos;}
        void setPlayerPos(Vector2f *newPlayerPos) {PlayerPos = newPlayerPos;}
        std::string texName;
        std::string type;
        bool flipSprite;
        bool randomIdle;
    private:
        int health;
        int maxHealth;
        bool wasHit;
        Vector2f *PlayerPos;
        int triggerDistance;
        bool triggered;
        float randomDirectionTimer;
        Vector2f randomDirection;
        float randomDirectionSpeed;

        int damage;
};