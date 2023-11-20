#include "../include/enemy.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"


Enemy::Enemy(Vector2f p_pos, SDL_Texture *p_tex, int width, int height,int triggerDistance,int damage,Vector2f *PlayerPos)
    : Entity(p_pos, p_tex, width, height),triggerDistance(triggerDistance),damage(damage),PlayerPos(PlayerPos)
{
}

void Enemy::update(EventManager &eventManager)
{
    if (!triggered) {
        if (utils::distance(pos, *PlayerPos) < triggerDistance) {
            triggered = true;
        }
        return;
    }
    // move towards the player
    Vector2f direction = utils::normalize(*PlayerPos - pos);
    pos += direction * 0.5f;
}

void Enemy::render(SDL_Renderer *renderer)
{
    SDL_Rect dst{static_cast<int>(pos.x*SCALE_FACTOR), static_cast<int>(pos.y*SCALE_FACTOR), width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopy(renderer,tex, NULL, &dst);
    utils::drawBoundingBox(renderer,
                           pos.x*SCALE_FACTOR,
                           pos.y*SCALE_FACTOR,
                           width*SCALE_FACTOR,
                           height*SCALE_FACTOR,
                           {255, 0, 0, 255}
                           );
}