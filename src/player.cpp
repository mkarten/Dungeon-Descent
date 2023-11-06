#include <iostream>
#include "../include/player.hpp"
#include "../include/event_manager.hpp"
#include "../include/constants.hpp"

Player::Player(Vector2f p_pos,SDL_Texture *p_tex, int w, int h, std::pair<int, int> spriteSheetConfiguration)
        : Entity(p_pos, p_tex, w, h, spriteSheetConfiguration)
{
    //create the underlying entity
    pos = p_pos;
    tex = p_tex;
    width = w;
    height = h;
    spriteSheetConfiguration = spriteSheetConfiguration;
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
}

void Player::render(SDL_Renderer *renderer)
{
    // render the entity
    SDL_Rect dst;
    dst.x = pos.x*SCALE_FACTOR;
    dst.y = pos.y*SCALE_FACTOR;
    dst.w = width*SCALE_FACTOR;
    dst.h = height*SCALE_FACTOR;
    SDL_RenderCopy(renderer, tex, NULL, &dst);
}