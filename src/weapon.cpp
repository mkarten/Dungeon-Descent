#include "../include/weapon.hpp"
#include "../include/event_manager.hpp"
#include "../include/constants.hpp"
#include <math.h>
#include <iostream>

Weapon::Weapon(Vector2f p_pos, SDL_Texture *p_tex, int width, int height, int dammage, float cooldown, float range)
        :
    Entity(p_pos, p_tex, width, height){
    this->angle = 0;
    this->dammage = dammage;
    this->cooldown = cooldown;
    this->cooldownTimer = 0;
    this->range = range;
}

void Weapon::render(Renderer *renderer){

    // calculate the screenspace position of the weapon
    Vector2f screenPos = renderer->worldspaceToScreenspace(pos);
    // render the weapon with x and y as the center of the weapon
    SDL_Rect dst{static_cast<int>(screenPos.x*SCALE_FACTOR), static_cast<int>(screenPos.y*SCALE_FACTOR), width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopyEx(renderer->getRenderer(),tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void Weapon::update(EventManager &eventManager){
    //point the center of the weapon at the mouse when it is not on cooldown
    if (!isOnCooldown){
        newAngle = atan2(eventManager.mouse.y - ((pos.y + height/2)*SCALE_FACTOR), eventManager.mouse.x - ((pos.x + width/2)*SCALE_FACTOR)) * 180 / M_PI;
    }
    // when the left mouse button is pressed attack with the weapon if it is not on cooldown
    if (eventManager.mouse.Buttons[SDL_BUTTON_LEFT] && !eventManager.mouse.LastButtons[SDL_BUTTON_LEFT] && !isOnCooldown){
        isOnCooldown = true;
        // send the sword forward in the direction it is facing to the max range
        lastPos = pos;
        newpos.x += cos(newAngle * M_PI / 180) * range;
        newpos.y += sin(newAngle * M_PI / 180) * range;
        // rotate the weapon 90 degrees to the right
        newAngle = angle + 90;
    }
    // if the weapon is on cooldown, increment the cooldown timer
    if (isOnCooldown){
        cooldownTimer += eventManager.deltaTime;
        if (cooldownTimer >= cooldown){
            isOnCooldown = false;
            eventManager.sendMessage(Messages::IDs::LEVEL, Messages::IDs::PLAYER_WEAPON, Messages::COOLDOWN_RESET);
            cooldownTimer = 0;
        }
    }
    // lerp the angle to the new angle
    angle = utils::lerpf(angle, newAngle, 0.1);
    // lerp the position to the new position
    lastPos = pos;
    // if the weapon is not on cooldown, increase the lerping speed
    if (!isOnCooldown){
        pos = utils::lerpVector2f(pos, newpos, 0.2);
    }else{
        pos = utils::lerpVector2f(pos, newpos, 0.1);
    }
}

