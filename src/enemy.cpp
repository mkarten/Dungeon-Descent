#include <iostream>
#include "../include/enemy.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"


Enemy::Enemy(Vector2f p_pos, Animations *e_anim, int width, int height,int triggerDistance,int damage,Vector2f *PlayerPos,int health)
    : Entity(p_pos, nullptr, width, height),triggerDistance(triggerDistance),damage(damage),PlayerPos(PlayerPos)
{

    anim = e_anim;
    animationTimer = 0;
    currentFrameIndex = 0;
    currentFrame = anim->idleAnimation[currentFrameIndex];
    isRunning = false;
    wasHit = false;
    triggered = false;
    randomDirectionTimer = 0;
    randomDirection = Vector2f{0, 0};
    this->maxHealth = health;
    this->health = health;
    speed = 0;
    maxSpeed = 0.5f;
}

void Enemy::update(EventManager &eventManager)
{
    lastPos = pos;
    Vector2f direction = Vector2f(0, 0);
    if (triggered) {
        direction = *PlayerPos - pos;
        // need to look if this feature is interesting
//        if (utils::distance(pos, *PlayerPos) > triggerDistance) {
//            triggered = false;
//        }
    }else{
        if (utils::distance(pos, *PlayerPos) < triggerDistance) {
            triggered = true;
        }
        if (randomDirectionTimer <= 0) {
            randomDirectionTimer = 3;
            // pick a random direction to move in between {-1,-1} and {1,1}
            randomDirection = Vector2f{static_cast<float>(rand() % 200 - 100) / 100.0f, static_cast<float>(rand() % 200 - 100) / 100.0f};
            // pick a random speed between 0.01 and 0.2
            randomDirectionSpeed = static_cast<float>(rand() % 20 + 1) / 100.0f;
        }
        randomDirectionTimer -= eventManager.deltaTime;
        // wander in the random direction
        direction = randomDirection;
    }
    if (direction.x != 0 || direction.y != 0) {
        direction = utils::normalize(direction);
        // lerp the speed to maxSpeed
        if (triggered) {
            speed = utils::lerpf(speed, maxSpeed, 0.06f);
        }else{
            speed = utils::lerpf(speed, randomDirectionSpeed, 0.06f);
        }
        pos += direction * speed;
    }else{
        // lerp the speed to 0
        speed = utils::lerpf(speed, 0, 0.06f);
        pos += direction * speed;
    }

    // update the animation
    animationTimer += eventManager.deltaTime;
    // change the animation with the speed
    if (speed > 0.1f) {
        if (isRunning){
            currentFrameIndex = 0;
            isRunning = false;
        }
        currentFrameIndex = (int) (animationTimer * 10) % anim->runAnimation.size();
        currentFrame = anim->runAnimation[currentFrameIndex];
    } else {
        if (!isRunning){
            currentFrameIndex = 0;
            isRunning = true;
        }
        currentFrameIndex = (int) (animationTimer * 10) % anim->idleAnimation.size();
        currentFrame = anim->idleAnimation[currentFrameIndex];
    }
    if (animationTimer > animation::timeBetweenFrames) {
        animationTimer = 0;
        currentFrameIndex += 1;
        if (currentFrameIndex >= anim->idleAnimation.size()) {
            currentFrameIndex = 0;
        }
    }

    // if the enemy is going left, flip the sprite
    if (pos.x < lastPos.x) {
        flipSprite = true;
    }else{
        flipSprite = false;
    }
}

void Enemy::render(Renderer *renderer)
{
    // calculate the screenspace position of the enemy
    Vector2f screenPos = renderer->worldspaceToScreenspace(pos);
    SDL_Rect dst{static_cast<int>(screenPos.x*SCALE_FACTOR), static_cast<int>(screenPos.y*SCALE_FACTOR), width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopyEx(renderer->getRenderer(),currentFrame, NULL, &dst, 0, NULL, flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
//    utils::drawBoundingBox(renderer->getRenderer(),
//                           screenPos.x*SCALE_FACTOR,
//                           screenPos.y*SCALE_FACTOR,
//                           width*SCALE_FACTOR,
//                           height*SCALE_FACTOR,
//                           {255, 0, 0, 255}
//                           );
    // render the health bar centered above the enemy
    int barWidth = 20;
    int barHeightOffset = 5;
    // calculate the x position of the health bar based on the width of the enemy and the width of the health bar
    int barPosX = screenPos.x+(width - barWidth) / 2;
    // render the background of the health bar as a black rectangle
    SDL_Rect healthBarBackground{static_cast<int>(barPosX*SCALE_FACTOR), static_cast<int>((screenPos.y- barHeightOffset)*SCALE_FACTOR), static_cast<int>(barWidth*SCALE_FACTOR), 5};
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(renderer->getRenderer(), &healthBarBackground);

    // render the health bar above the enemy as a red rectangle that shrinks as the enemy takes damage
    SDL_Rect healthBar{static_cast<int>(barPosX*SCALE_FACTOR), static_cast<int>((screenPos.y- barHeightOffset)*SCALE_FACTOR ), static_cast<int>(barWidth*SCALE_FACTOR * (static_cast<float>(health) / static_cast<float>(maxHealth))), 5};
    SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(renderer->getRenderer(), &healthBar);

    // if the enemy is hit, render a white rectangle above the enemy
    if (wasHit) {
        SDL_Rect hitBar{static_cast<int>(barPosX*SCALE_FACTOR), static_cast<int>((screenPos.y- barHeightOffset)*SCALE_FACTOR ), static_cast<int>(barWidth*SCALE_FACTOR * (static_cast<float>(health) / static_cast<float>(maxHealth))), 5};
        SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 255, 255, 255);
        SDL_RenderFillRect(renderer->getRenderer(), &hitBar);
    }

}

