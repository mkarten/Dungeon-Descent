#include "../include/staticEntity.hpp"
#include "../include/constants.hpp"

void StaticEntity::render(Renderer *renderer)
{
    // calculate the screenspace position
    Vector2f screenspacePos = renderer->worldspaceToScreenspace(pos);
    SDL_Rect destRect = {(int)screenspacePos.x*SCALE_FACTOR, (int)screenspacePos.y*SCALE_FACTOR, width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopy(renderer->getRenderer(), tex, NULL, &destRect);
}