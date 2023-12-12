#include "../include/levelEditor.hpp"
#include "../include/constants.hpp"
#include "../include/utils.hpp"
#include <iostream>

void LevelEditor::update(EventManager &eventManager) {
    placingCursor.x = (mousePos.x/SCALE_FACTOR - (int)(mousePos.x/SCALE_FACTOR)%16);
    placingCursor.y = (mousePos.y/SCALE_FACTOR - (int)(mousePos.y/SCALE_FACTOR)%16);


    // when the right mouse button is pressed, remove the first tile that is under the cursor
    if (eventManager.mouse.Buttons[SDL_BUTTON_RIGHT] && !eventManager.mouse.LastButtons[SDL_BUTTON_RIGHT]) {
        std::vector<StaticEntity> staticEntities = *getStaticEntities();
        // range over the staticEntities backwards to remove the first one that is under the cursor
        for (int i = staticEntities.size()-1; i >= 0; i--) {
            if (utils::isPointInRect(mousePos.x/SCALE_FACTOR, mousePos.y/SCALE_FACTOR, staticEntities[i].getRect())) {
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
        newStaticEntity.tex = tilesetTexs[tilesetTexsIndex];
        // set the name of the new static entity to the name of the tile under the cursor
        newStaticEntity.texName = tilesetTexsNames[tilesetTexsIndex];
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
        // set the collidable of the new static entity to the isPlacedTileCollidable
        newStaticEntity.collidable = isPlacedTileCollidable;
        // add the new static entity to the static entities
        std::vector<StaticEntity> staticEntities = *getStaticEntities();
        staticEntities.push_back(newStaticEntity);
        setStaticEntities(staticEntities);
        // print the legnth of the static entities
        std::cout << staticEntities.size() << std::endl;
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
    if (eventManager.mouse.ScrolledUp){
        tilesetTexsIndex--;
        if (tilesetTexsIndex<0) tilesetTexsIndex = tilesetTexs.size()-1;
    }
    if (eventManager.mouse.ScrolledDown){
        tilesetTexsIndex++;
        if (tilesetTexsIndex>=tilesetTexs.size()) tilesetTexsIndex = 0;
    }
    if (eventManager.Keys[SDL_SCANCODE_RETURN] && !eventManager.LastKeys[SDL_SCANCODE_RETURN]){
        std::string cwd = utils::getCurrentWorkingDirectory();
        std::string path = utils::chooseFile("Save level", cwd, "Level files (*.json)\0*.lvl\0All files (*.*)\0*.*\0");
        if (path != ""){
            std::cout << path << std::endl;
            levelData.setStaticEntities(*getStaticEntities());
            getLevelData()->SerializeToFile(path);
        }
    }
    // if c is pressed, toggle the isPlacedTileCollidable
    if (eventManager.Keys[SDL_SCANCODE_C] && !eventManager.LastKeys[SDL_SCANCODE_C]){
        isPlacedTileCollidable = !isPlacedTileCollidable;
    }

    // change the mouving direction based on the keys pressed
    mouvingDirection = Vector2f{0, 0};
    if (eventManager.Keys[SDL_SCANCODE_W]) mouvingDirection.y = -1;
    if (eventManager.Keys[SDL_SCANCODE_S]) mouvingDirection.y = 1;
    if (eventManager.Keys[SDL_SCANCODE_A]) mouvingDirection.x = -1;
    if (eventManager.Keys[SDL_SCANCODE_D]) mouvingDirection.x = 1;
    mousePos = Vector2f{static_cast<float>(eventManager.mouse.x), static_cast<float>(eventManager.mouse.y)};
}

void LevelEditor::render(Renderer *renderer) {
    mousePos = renderer->screenspaceToWorldspace(mousePos);

    // move the camera based on the mouving direction
    renderer->camera.pos.x += mouvingDirection.x * 1;
    renderer->camera.pos.y += mouvingDirection.y * 1;

    // make sure the camera is not out of bounds
    if (renderer->camera.pos.x < 0) renderer->camera.pos.x = 0;
    if (renderer->camera.pos.y < 0) renderer->camera.pos.y = 0;


    // clear the screen
    SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 255, 255, 255);
    SDL_RenderClear(renderer->getRenderer());
    // render the tiles
    std::vector<StaticEntity> staticEntities = *getStaticEntities();
    for (auto &staticEntity : staticEntities) {
        staticEntity.render(renderer);
    }
    // render the placingCursor
    SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 0, 0, 255);
    Vector2f screenPos = renderer->worldspaceToScreenspace(Vector2f{static_cast<float>(placingCursor.x), static_cast<float>(placingCursor.y)});
    SDL_Rect scaledPlacingCursor = {static_cast<int>(screenPos.x*SCALE_FACTOR), static_cast<int>(screenPos.y*SCALE_FACTOR), placingCursor.w*SCALE_FACTOR, placingCursor.h*SCALE_FACTOR};
    SDL_RenderDrawRect(renderer->getRenderer(), &scaledPlacingCursor);
    // draw the current selected tile at the bottom right corner
    int w, h;
    SDL_QueryTexture(tilesetTexs[tilesetTexsIndex], NULL, NULL, &w, &h);
    SDL_Rect scaledTilesetTex = {WINDOW_WIDTH-w*UI_SCALE_FACTOR, WINDOW_HEIGHT-h*UI_SCALE_FACTOR, w*UI_SCALE_FACTOR, h*UI_SCALE_FACTOR};
    SDL_RenderCopy(renderer->getRenderer(), tilesetTexs[tilesetTexsIndex], NULL, &scaledTilesetTex);

    if (isPlacedTileCollidable){
        // drawn text C on top of the selected tile at the Top right corner
        utils::renderText(renderer->getRenderer(), "C", WINDOW_WIDTH-w*UI_SCALE_FACTOR, WINDOW_HEIGHT-h*UI_SCALE_FACTOR, SDL_Color{0, 0, 0, 255});
    }
}