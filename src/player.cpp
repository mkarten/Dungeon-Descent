#include <iostream>
#include <valarray>
#include "../include/player.hpp"
#include "../include/event_manager.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"

Player::Player(Vector2f p_pos,SDL_Texture *p_tex,SDL_Texture *w_tex, int w, int h, std::pair<int, int> spriteSheetConfiguration)
        : Entity(p_pos, p_tex, w, h, spriteSheetConfiguration)
{
    //create the underlying entity
    pos = p_pos;
    tex = p_tex;
    width = w;
    height = h;
    weapon.texture = w_tex;
    weapon.angle = 0;
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
    //point the center of the weapon at the mouse
    int w, h;
    SDL_QueryTexture(weapon.texture, NULL, NULL, &w, &h);
    std::cout << "width: " << w << " height: " << h << std::endl;
    int centerX = pos.x + w/2;
    int centerY = pos.y + h/2;
    weapon.angle = atan2(eventManager.mouse.y - centerY, eventManager.mouse.x - centerX) * 180 / M_PI;

}

void Player::render(SDL_Renderer *renderer)
{
    // render the entity
    SDL_Rect dst;
    dst.x = pos.x*SCALE_FACTOR;
    dst.y = pos.y*SCALE_FACTOR;
    dst.w = width*SCALE_FACTOR;
    dst.h = height*SCALE_FACTOR;
    SDL_RenderCopy(renderer,tex, NULL, &dst);
    //render the weapon
    // get the width and height of the weapon
    int w, h;
    SDL_QueryTexture(weapon.texture, NULL, NULL, &w, &h);
    SDL_Rect dst2;
    dst2.x = pos.x*SCALE_FACTOR;
    dst2.y = pos.y*SCALE_FACTOR;
    dst2.w = w*SCALE_FACTOR;
    dst2.h = h*SCALE_FACTOR;
    SDL_RenderCopyEx(renderer, weapon.texture, NULL, &dst2, weapon.angle, NULL, SDL_FLIP_NONE);
    // draw a line from the center of the weapon 100 pixels in the direction of the mouse
    int centerX = pos.x + w/2;
    int centerY = pos.y + h/2;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, centerX*SCALE_FACTOR, centerY*SCALE_FACTOR, (centerX + 100*cos(weapon.angle*M_PI/180))*SCALE_FACTOR, (centerY + 100*sin(weapon.angle*M_PI/180))*SCALE_FACTOR);
}