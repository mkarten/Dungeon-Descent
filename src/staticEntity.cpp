#include "../include/staticEntity.hpp"
#include "../include/constants.hpp"

void StaticEntity::render(SDL_Renderer *renderer)
{
    SDL_Rect destRect = {(int)pos.x*SCALE_FACTOR, (int)pos.y*SCALE_FACTOR, width*SCALE_FACTOR,height*SCALE_FACTOR};
    SDL_RenderCopy(renderer, tex, NULL, &destRect);
}