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
    weapon = Weapon(Vector2f(0, 0), w_tex, w_w, w_h);
    pos = p_pos;
    tex = p_tex;
    width = w;
    height = h;
    health = PLAYER_MAX_HP;
    maxHealth = PLAYER_MAX_HP;
    fullHeart =
}

void Player::update(EventManager &eventManager)
{
    // update the entity
    if (eventManager.Keys[SDL_SCANCODE_W]) {
        pos.y -= 1;
    }
    if (eventManager.Keys[SDL_SCANCODE_S]) {
        pos.y += 1;
    }
    if (eventManager.Keys[SDL_SCANCODE_A]) {
        pos.x -= 1;
    }
    if (eventManager.Keys[SDL_SCANCODE_D]) {
        pos.x += 1;
    }
    weapon.pos = pos;
    weapon.update(eventManager);


}

void Player::render(SDL_Renderer *renderer)
{
    // render the entity
    SDL_Rect dst{static_cast<int>(pos.x*SCALE_FACTOR), static_cast<int>(pos.y*SCALE_FACTOR), width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopy(renderer,tex, NULL, &dst);

    //render the weapon
    weapon.render(renderer);

    // line around the player
    utils::drawBoundingBox(renderer,
                           pos.x*SCALE_FACTOR,
                           pos.y*SCALE_FACTOR,
                           width*SCALE_FACTOR,
                           height*SCALE_FACTOR,
                           {255, 0, 0, 255}
                           );
}