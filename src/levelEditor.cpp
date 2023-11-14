#include "../include/levelEditor.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include <iostream>

void LevelEditor::update(EventManager &eventManager) {
    // update the placingCursor position according to the mouse position to fit a 16x16 grid
    placingCursor.x = (eventManager.mouse.x/SCALE_FACTOR - (eventManager.mouse.x/SCALE_FACTOR)%16);
    placingCursor.y = (eventManager.mouse.y/SCALE_FACTOR - (eventManager.mouse.y/SCALE_FACTOR)%16);


    // when the right mouse button is pressed, remove the first tile that is under the cursor
    if (eventManager.mouse.Buttons[SDL_BUTTON_RIGHT] && !eventManager.mouse.LastButtons[SDL_BUTTON_RIGHT]) {
        std::vector<StaticEntity> staticEntities = *getStaticEntities();
        // range over the staticEntities backwards to remove the first one that is under the cursor
        for (int i = staticEntities.size()-1; i >= 0; i--) {
            if (utils::isPointInRect(eventManager.mouse.x/SCALE_FACTOR, eventManager.mouse.y/SCALE_FACTOR, staticEntities[i].getRect())) {
                staticEntities.erase(staticEntities.begin()+i);
                break;
            }
        }
        // set the staticEntities to the new vector
        setStaticEntities(staticEntities);
    }
    // when the left mouse button is pressed, add a tile under the cursor
    if (eventManager.mouse.Buttons[SDL_BUTTON_LEFT] && !eventManager.mouse.LastButtons[SDL_BUTTON_LEFT]) {
        // create a new static entity
        StaticEntity newStaticEntity;
        // set the position of the new static entity to the position of the cursor
        newStaticEntity.pos.x = placingCursor.x;
        newStaticEntity.pos.y = placingCursor.y;
        // set the texture of the new static entity to the texture of the tile under the cursor
        newStaticEntity.tex = utils::loadTileFromTileset(tilesetTex,tilesInfoMap["floor_1"],renderer);
        // set the name of the new static entity to the name of the tile under the cursor
        newStaticEntity.texName = "floor_1";
        int w, h;
        SDL_QueryTexture(newStaticEntity.tex, NULL, NULL, &w, &h);
        // check if we need to tile the texture
        if (placingCursor.w>w || placingCursor.h>h){
            newStaticEntity.tex = utils::textureTiling(newStaticEntity.tex,renderer,placingCursor.w,placingCursor.h);
            newStaticEntity.width = placingCursor.w;
            newStaticEntity.height = placingCursor.h;
        }else{
            newStaticEntity.width = w;
            newStaticEntity.height = h;
        }
        // add the new static entity to the static entities
        std::vector<StaticEntity> staticEntities = *getStaticEntities();
        staticEntities.push_back(newStaticEntity);
        setStaticEntities(staticEntities);
    }
    if (eventManager.Keys[SDL_SCANCODE_DOWN] && !eventManager.LastKeys[SDL_SCANCODE_DOWN]){
        placingCursor.h += 16;
    }
    if (eventManager.Keys[SDL_SCANCODE_UP] && !eventManager.LastKeys[SDL_SCANCODE_UP]){
        if (placingCursor.h>16) placingCursor.h -= 16;
    }
    if (eventManager.Keys[SDL_SCANCODE_RIGHT] && !eventManager.LastKeys[SDL_SCANCODE_RIGHT]){
        placingCursor.w += 16;
    }
    if (eventManager.Keys[SDL_SCANCODE_LEFT] && !eventManager.LastKeys[SDL_SCANCODE_LEFT]){
        if (placingCursor.w>16) placingCursor.w -= 16;
    }

    // update the player
    getPlayer()->update(eventManager);

}

void LevelEditor::render(SDL_Renderer *renderer) {
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // render the tiles
    std::vector<StaticEntity> staticEntities = *getStaticEntities();
    for (auto &staticEntity : staticEntities) {
        staticEntity.render(renderer);
    }
    // render the player
    getPlayer()->render(renderer);
    // render the placingCursor
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect scaledPlacingCursor = {placingCursor.x*SCALE_FACTOR, placingCursor.y*SCALE_FACTOR, placingCursor.w*SCALE_FACTOR, placingCursor.h*SCALE_FACTOR};
    SDL_RenderDrawRect(renderer, &scaledPlacingCursor);
}