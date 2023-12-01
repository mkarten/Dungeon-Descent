#include "../include/enemy.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"


Enemy::Enemy(Vector2f p_pos, SDL_Texture *p_tex, int width, int height,int triggerDistance,int damage,Vector2f *PlayerPos,int health)
    : Entity(p_pos, p_tex, width, height),triggerDistance(triggerDistance),damage(damage),PlayerPos(PlayerPos)
{
    this->maxHealth = health;
    this->health = health;
}

void Enemy::update(EventManager &eventManager)
{
    if (!triggered) {
        if (utils::distance(pos, *PlayerPos) < triggerDistance) {
            triggered = true;
        }
        return;
    }
    lastPos = pos;
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
    // render the health bar centered above the enemy
    int barWidth = 20;
    int barHeightOffset = 5;
    // calculate the x position of the health bar based on the width of the enemy and the width of the health bar
    int barPosX = pos.x+(width - barWidth) / 2;
    // render the background of the health bar as a black rectangle
    SDL_Rect healthBarBackground{static_cast<int>(barPosX*SCALE_FACTOR), static_cast<int>((pos.y- barHeightOffset)*SCALE_FACTOR), static_cast<int>(barWidth*SCALE_FACTOR), 5};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthBarBackground);

    // render the health bar above the enemy as a red rectangle that shrinks as the enemy takes damage
    SDL_Rect healthBar{static_cast<int>(barPosX*SCALE_FACTOR), static_cast<int>((pos.y- barHeightOffset)*SCALE_FACTOR ), static_cast<int>(barWidth*SCALE_FACTOR * (static_cast<float>(health) / static_cast<float>(maxHealth))), 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthBar);

}
