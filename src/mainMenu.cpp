#include <iostream>
#include "../include/mainMenu.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include "../include/renderer.hpp"

void MainMenu::update(EventManager &eventManager)
{
    bool lastStartButtonHovered = startButtonHovered;
    bool lastQuitButtonHovered = quitButtonHovered;
    if (utils::isPointInRect(eventManager.mouse.x, eventManager.mouse.y, startGameButton)){
        startButtonHovered = true;
        if (!lastStartButtonHovered){
            utils::playSelectSound();
        }
    } else{
        startButtonHovered = false;
    }
    if (utils::isPointInRect(eventManager.mouse.x, eventManager.mouse.y, quitGameButton)){
        quitButtonHovered = true;
        if (!lastQuitButtonHovered){
            utils::playSelectSound();
        }
    } else{
        quitButtonHovered = false;
    }


    // check if the start game button is pressed
    if (startButtonHovered && eventManager.mouse.Buttons[SDL_BUTTON_LEFT] && !eventManager.mouse.LastButtons[SDL_BUTTON_LEFT]) {
        // play click sound
        utils::playClickSound();
        eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::GAME, Messages::START_GAME);
    }
    if (quitButtonHovered && eventManager.mouse.Buttons[SDL_BUTTON_LEFT] && !eventManager.mouse.LastButtons[SDL_BUTTON_LEFT]) {
        // play click sound
        utils::playClickSound();
        eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::GAME, Messages::QUIT_GAME);
    }
    // update the enemies
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].update(eventManager);
    }
    for (int i = 0; i < staticEntities.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            if (enemies[j].isCollidingWith(staticEntities[i]) && staticEntities[i].collidable) {
                // get the collision info
                CollisionInfo collisionInfo = enemies[j].getCollisionInfo(staticEntities[i]);
                // revert the enemy position based on the collision info
                if (collisionInfo.isCollidingLeft || collisionInfo.isCollidingRight) {
                    enemies[j].pos.x = enemies[j].lastPos.x;
                }
                if (collisionInfo.isCollidingTop || collisionInfo.isCollidingBottom) {
                    enemies[j].pos.y = enemies[j].lastPos.y;
                }
            }
            //check for collisions between the enemy and other enemies
            for (int i = 0; i < enemies.size(); i++) {
                if (enemies[j].isCollidingWith(enemies[i]) && i != j) {
                    // get the collision info
                    CollisionInfo collisionInfo = enemies[j].getCollisionInfo(enemies[i]);
                    // revert the enemy position based on the collision info
                    if (collisionInfo.isCollidingLeft || collisionInfo.isCollidingRight) {
                        enemies[j].pos.x = enemies[j].lastPos.x;
                    }
                    if (collisionInfo.isCollidingTop || collisionInfo.isCollidingBottom) {
                        enemies[j].pos.y = enemies[j].lastPos.y;
                    }
                }
            }
        }
    }
}

void MainMenu::render(Renderer *renderer)
{

    // clear the screen
    SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 255, 255, 255);
    SDL_RenderClear(renderer->getRenderer());


    for (int i = 0; i < staticEntities.size(); i++) {
        staticEntities[i].render(renderer);
    }
    // render the enemies
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].render(renderer);
        enemies[i].setTriggered(false);
    }

    // draw an semi transparent gray rectangle over the screen
    SDL_SetRenderDrawColor(renderer->getRenderer(), 110, 100, 100, 100);
    SDL_SetRenderDrawBlendMode(renderer->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_Rect rect = {0, 0,WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer->getRenderer(), &rect);
    SDL_SetRenderDrawBlendMode(renderer->getRenderer(), SDL_BLENDMODE_NONE);

    // draw the start game button the startButtonPos is the center of the button
    startGameButton = {startButtonPos.x - startButtonSize.x/2, startButtonPos.y - startButtonSize.y/2, startButtonSize.x, startButtonSize.y};
    if (startButtonHovered){
        SDL_SetRenderDrawColor(renderer->getRenderer(), 200, 200, 200, 255);
    } else{
        SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 255, 255, 255);
    }
    SDL_RenderFillRect(renderer->getRenderer(), &startGameButton);
    // draw the start game text at the center of the button
    utils::renderText(renderer->getRenderer(), "START GAME", startButtonPos.x, startButtonPos.y, {0, 0, 0, 255});

    // draw the quit game button the quitButtonPos is the center of the button
    quitGameButton = {quitButtonPos.x - quitButtonSize.x/2, quitButtonPos.y - quitButtonSize.y/2, quitButtonSize.x, quitButtonSize.y};
   if (quitButtonHovered){
        SDL_SetRenderDrawColor(renderer->getRenderer(), 200, 200, 200, 255);
    } else{
        SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 255, 255, 255);
    }
    SDL_RenderFillRect(renderer->getRenderer(), &quitGameButton);
    // draw the quit game text at the center of the button
    utils::renderText(renderer->getRenderer(), "QUIT GAME", quitButtonPos.x, quitButtonPos.y, {0, 0, 0, 255});
    // render the game name
    utils::renderText(renderer->getRenderer(), WINDOW_TITLE, WINDOW_WIDTH/2, 100, {0, 0, 0, 255});
}