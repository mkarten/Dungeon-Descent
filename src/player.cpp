#include <iostream>
#include <valarray>
#include "../include/player.hpp"
#include "../include/event_manager.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"

Player::Player(Vector2f p_pos,SDL_Texture *p_tex,SDL_Texture *w_tex, int w, int h)
        : Entity(p_pos, p_tex, w, h)
{
    int w_w, w_h;
    SDL_QueryTexture(w_tex, NULL, NULL, &w_w, &w_h);
    weapon = Weapon(Vector2f(0, 0), w_tex, w_w, w_h, 1, 0.5, 100);
    pos = p_pos;
    tex = p_tex;
    width = w;
    height = h;
    dead = false;
    health = PLAYER_MAX_HP;
    maxHealth = PLAYER_MAX_HP;
    fullHeart = utils::getHeartFullTexture();
    halfHeart = utils::getHeartHalfTexture();
    emptyHeart = utils::getHeartEmptyTexture();
}

void Player::update(EventManager &eventManager)
{
    if (!dead){
        if (health <= 0){
            dead = true;
            eventManager.sendMessage(Messages::IDs::GAME,Messages::IDs::PLAYER,Messages::PLAYER_DIED);
        }
        lastPos = pos;
        // update the entity
        if (eventManager.Keys[SDL_SCANCODE_W] || eventManager.Keys[SDL_SCANCODE_UP]) {
            pos.y -= 1;
        }
        if (eventManager.Keys[SDL_SCANCODE_S] || eventManager.Keys[SDL_SCANCODE_DOWN]) {
            pos.y += 1;
        }
        if (eventManager.Keys[SDL_SCANCODE_A] || eventManager.Keys[SDL_SCANCODE_LEFT]) {
            pos.x -= 1;
        }
        if (eventManager.Keys[SDL_SCANCODE_D] || eventManager.Keys[SDL_SCANCODE_RIGHT]) {
            pos.x += 1;
        }
        if (eventManager.Keys[SDL_SCANCODE_ESCAPE] && !eventManager.LastKeys[SDL_SCANCODE_ESCAPE]) {
            eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::PLAYER, Messages::ENTER_EDITOR_MODE);
        }
        if (!weapon.isOnCooldown){
            // put center of the weapon at center of the player
            weapon.newpos = Vector2f(pos.x + width/2-weapon.width/2, pos.y + height/2-weapon.height/2);
        }
        weapon.update(eventManager);
    }




}

void Player::render(SDL_Renderer *renderer)
{
    // render the entity
    SDL_Rect dst{static_cast<int>(pos.x*SCALE_FACTOR), static_cast<int>(pos.y*SCALE_FACTOR), width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopy(renderer,tex, NULL, &dst);

    //render the weapon
    weapon.render(renderer);

    // render the health bar
    int heartWidth;
    int heartHeight;
    int heartSpacing = 2;
    SDL_QueryTexture(fullHeart, NULL, NULL, &heartWidth, &heartHeight);
    heartWidth *= UI_SCALE_FACTOR;
    heartHeight *= UI_SCALE_FACTOR;
    int heartX = 10;
    int heartY = 10;
    int tempHealth = this->health;
    // each heart is 2 health points
    for (int i = 0; i < maxHealth / 2; i++) {
        if (tempHealth >= 2) {
            SDL_Rect dst{heartX, heartY, heartWidth, heartHeight};
            SDL_RenderCopy(renderer, fullHeart, NULL, &dst);
        } else if (tempHealth == 1) {
            SDL_Rect dst{heartX, heartY, heartWidth, heartHeight};
            SDL_RenderCopy(renderer, halfHeart, NULL, &dst);
        } else {
            SDL_Rect dst{heartX, heartY, heartWidth, heartHeight};
            SDL_RenderCopy(renderer, emptyHeart, NULL, &dst);
        }
        tempHealth -= 2;
        heartX += heartWidth + (heartSpacing*UI_SCALE_FACTOR);
    }

    // line around the player
    utils::drawBoundingBox(renderer,
                           pos.x*SCALE_FACTOR,
                           pos.y*SCALE_FACTOR,
                           width*SCALE_FACTOR,
                           height*SCALE_FACTOR,
                           {255, 0, 0, 255}
                           );
}