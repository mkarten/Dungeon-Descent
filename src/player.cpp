#include <iostream>
#include "../include/player.hpp"
#include "../include/constants.hpp"

Player::Player(Vector2f p_pos,SDL_Texture *p_tex, int width, int height, std::pair<int, int> spriteSheetConfiguration)
        : Entity(p_pos, p_tex, width, height, spriteSheetConfiguration)
{
    //create the underlying entity
    pos = p_pos;
    tex = p_tex;
    width = width;
    height = height;
    spriteSheetConfiguration = spriteSheetConfiguration;
}

void Player::update(std::vector<SDL_Event> &events)
{
    // update the entity
    for (SDL_Event &event: events) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    pos.y -= 1;
                    break;
                case SDLK_a:
                    pos.x -= 1;
                    break;
                case SDLK_s:
                    pos.y += 1;
                    break;
                case SDLK_d:
                    pos.x += 1;
                    break;
                default:
                    break;
            }
        }
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