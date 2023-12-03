#include "../include/mainMenu.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"

void MainMenu::update(EventManager &eventManager)
{
    if (utils::isPointInRect(eventManager.mouse.x, eventManager.mouse.y, startGameButton)){
        startButtonHovered = true;
    } else{
        startButtonHovered = false;
    }
    if (utils::isPointInRect(eventManager.mouse.x, eventManager.mouse.y, quitGameButton)){
        quitButtonHovered = true;
    } else{
        quitButtonHovered = false;
    }


    // check if the start game button is pressed
    if (startButtonHovered && eventManager.mouse.Buttons[SDL_BUTTON_LEFT] && !eventManager.mouse.LastButtons[SDL_BUTTON_LEFT]) {
        eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::GAME, Messages::START_GAME);
    }
    if (quitButtonHovered && eventManager.mouse.Buttons[SDL_BUTTON_LEFT] && !eventManager.mouse.LastButtons[SDL_BUTTON_LEFT]) {
        // quit the game
        eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::GAME, Messages::QUIT_GAME);
    }
}

void MainMenu::render(SDL_Renderer *renderer)
{
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);


    // render the tiles
    std::vector<StaticEntity> staticEntities = *getStaticEntities();
    for (auto &staticEntity : staticEntities) {
        staticEntity.render(renderer);
    }

    // draw an semi transparent gray rectangle over the screen
    SDL_SetRenderDrawColor(renderer, 110, 100, 100, 100);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect rect = {0, 0,WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // draw the start game button the startButtonPos is the center of the button
    SDL_Rect startGameButton = {startButtonPos.x - startButtonSize.x/2, startButtonPos.y - startButtonSize.y/2, startButtonSize.x, startButtonSize.y};
    if (startButtonHovered){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    } else{
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    SDL_RenderFillRect(renderer, &startGameButton);
    // draw the start game text at the center of the button
    utils::renderText(renderer, "START GAME", startButtonPos.x, startButtonPos.y, {0, 0, 0, 255});

    // draw the quit game button the quitButtonPos is the center of the button
    SDL_Rect quitGameButton = {quitButtonPos.x - quitButtonSize.x/2, quitButtonPos.y - quitButtonSize.y/2, quitButtonSize.x, quitButtonSize.y};
       if (quitButtonHovered){
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        } else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
    SDL_RenderFillRect(renderer, &quitGameButton);
    // draw the quit game text at the center of the button
    utils::renderText(renderer, "QUIT GAME", quitButtonPos.x, quitButtonPos.y, {0, 0, 0, 255});

    // render the game name
    utils::renderText(renderer, WINDOW_TITLE, WINDOW_WIDTH/2, 100, {0, 0, 0, 255});
}