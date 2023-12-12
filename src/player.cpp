#include <iostream>
#include <valarray>
#include "../include/player.hpp"
#include "../include/event_manager.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"

Player::Player(Vector2f p_pos,Animations *p_anim,SDL_Texture *w_tex, int w, int h)
        : Entity(p_pos, nullptr, w, h)
{
    int w_w, w_h;
    SDL_QueryTexture(w_tex, NULL, NULL, &w_w, &w_h);
    weapon = Weapon(Vector2f(0, 0), w_tex, w_w, w_h, 1, 0.5, 100);
    pos = p_pos;
    anim = p_anim;
    animationTimer = 0;
    currentFrameIndex = 0;
    currentFrame = anim->idleAnimation[currentFrameIndex];
    width = w;
    height = h;
    dead = false;
    health = PLAYER_MAX_HP;
    maxHealth = PLAYER_MAX_HP;
    fullHeart = utils::getHeartFullTexture();
    halfHeart = utils::getHeartHalfTexture();
    emptyHeart = utils::getHeartEmptyTexture();
    flipSprite = false;
    isRunning = false;
    speed = 0;
    maxSpeed = 1.0f;
}

void Player::update(EventManager &eventManager)
{
    if (!dead){
        if (health <= 0){
            dead = true;
            eventManager.sendMessage(Messages::IDs::LEVEL,Messages::IDs::PLAYER,Messages::PLAYER_DIED);
        }
        lastPos = pos;
        Vector2f direction = Vector2f(0, 0);
        // update the entity
        if (eventManager.Keys[SDL_SCANCODE_W] || eventManager.Keys[SDL_SCANCODE_UP]) {
            direction.y -= 1;
        }
        if (eventManager.Keys[SDL_SCANCODE_S] || eventManager.Keys[SDL_SCANCODE_DOWN]) {
            direction.y += 1;
        }
        if (eventManager.Keys[SDL_SCANCODE_A] || eventManager.Keys[SDL_SCANCODE_LEFT]) {
            direction.x -= 1;
            flipSprite = true;
        }
        if (eventManager.Keys[SDL_SCANCODE_D] || eventManager.Keys[SDL_SCANCODE_RIGHT]) {
            direction.x += 1;
            flipSprite = false;
        }

        if (direction.x != 0 || direction.y != 0) {
            direction = utils::normalize(direction);
            // lerp the speed to maxSpeed
            speed = utils::lerpf(speed, maxSpeed, 0.06f);
            pos += direction * speed;
        }else{
            // lerp the speed to 0
            speed = utils::lerpf(speed, 0, 0.06f);
            pos += direction * speed;
        }

        // update the animation
        animationTimer += eventManager.deltaTime;
        // change the animation with the speed
        if (speed > 0.08f) {
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
        if (!weapon.isOnCooldown){
            // put center of the weapon at center of the player
            weapon.newpos = Vector2f(pos.x + width/2-weapon.width/2, pos.y + height/2-weapon.height/2);
        }
        weapon.update(eventManager);
    }




}

void Player::render(Renderer *renderer)
{
    // calculate the screenspace position of the player
    Vector2f screenPos = renderer->worldspaceToScreenspace(pos);
    // render the entity
    SDL_Rect dst{static_cast<int>(screenPos.x*SCALE_FACTOR), static_cast<int>(screenPos.y*SCALE_FACTOR), width*SCALE_FACTOR, height*SCALE_FACTOR};
    SDL_RenderCopyEx(renderer->getRenderer(),currentFrame, NULL, &dst, 0, NULL, flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

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
            SDL_RenderCopy(renderer->getRenderer(), fullHeart, NULL, &dst);
        } else if (tempHealth == 1) {
            SDL_Rect dst{heartX, heartY, heartWidth, heartHeight};
            SDL_RenderCopy(renderer->getRenderer(), halfHeart, NULL, &dst);
        } else {
            SDL_Rect dst{heartX, heartY, heartWidth, heartHeight};
            SDL_RenderCopy(renderer->getRenderer(), emptyHeart, NULL, &dst);
        }
        tempHealth -= 2;
        heartX += heartWidth + (heartSpacing*UI_SCALE_FACTOR);
    }

//    // line around the player
//    utils::drawBoundingBox(renderer->getRenderer(),
//                           screenPos.x*SCALE_FACTOR,
//                           screenPos.y*SCALE_FACTOR,
//                           width*SCALE_FACTOR,
//                           height*SCALE_FACTOR,
//                           {255, 0, 0, 255}
//                           );
}