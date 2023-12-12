#include "../include/level.hpp"
#include "../include/constants.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>

Level::Level(SDL_Renderer *renderer, Player *Gplayer , std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap) {

    // read the json in the level data file
    levelData.DeserializeFromFile(levelDataFileName);

    timer = 0;

    // copy the static entities from the level data to the level
    staticEntities = levelData.getStaticEntities();

    // copy the enemies from the level data to the level
    enemies = levelData.getEnemies();

    // set the player to the player passed in from the main game
    player = Gplayer;

    // position the player at the spawn point
    playerSpawnPoint = levelData.getPlayerSpawnPoint();

    gameWon = false;
    playerDead = false;

    // set the texture of the static entities to the tileset texture
    for (int i = 0; i < staticEntities.size(); i++) {

        // get the texture from the tileset
        staticEntities[i].tex = utils::loadTileFromTileset(tilesetTex, tilesInfoMap[staticEntities[i].texName], renderer);

        // check if the texture need to be tiled
        if (staticEntities[i].width > 0 || staticEntities[i].height>0){
            staticEntities[i].tex = utils::textureTiling(staticEntities[i].tex, renderer, staticEntities[i].width, staticEntities[i].height);
        } else{
            SDL_QueryTexture(staticEntities[i].tex, NULL, NULL, &staticEntities[i].width, &staticEntities[i].height);
        }
    }

    for (int i = 0; i < enemies.size(); i++) {
        // set the player position pointer of the enemy
        enemies[i].setPlayerPos(&player->pos);
    }
}


void Level::update(EventManager &eventManager){
        // update the enemies
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].update(eventManager);
    }

    // update the player
    player->update(eventManager);

    // check if the timer has exeded the level time limit
    if (timer>=TIME_LIMIT && !playerDead){
        // kill the player
        player->health = 0;
        playerDead = true;
        // remove trigger from all the entities
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].setTriggered(false);
        }
    }
    if (!playerDead && !gameWon){
        // update the timer with the delta time
        timer += eventManager.deltaTime;
    }

    if (playerDead || gameWon){
        if (eventManager.Keys[SDL_SCANCODE_RETURN] && !eventManager.LastKeys[SDL_SCANCODE_RETURN]){
            // send the restart game event
            eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::LEVEL, Messages::GAME_RESTART);
            return;
        }
    }

    // check for collisions between the player and the static entities
    for (int i = 0; i < staticEntities.size(); i++) {
        if (player->isCollidingWith(staticEntities[i]) && staticEntities[i].collidable) {
            // get the collision info
            CollisionInfo collisionInfo = player->getCollisionInfo(staticEntities[i]);
            // revert the player position based on the collision info
            if (collisionInfo.isCollidingLeft || collisionInfo.isCollidingRight) {
                player->pos.x = player->lastPos.x;
            }
            if (collisionInfo.isCollidingTop || collisionInfo.isCollidingBottom) {
                player->pos.y = player->lastPos.y;
            }
        }
        //check for collisions between the player weapon and the static entities
        if (player->weapon.isCollidingWith(staticEntities[i]) && staticEntities[i].collidable) {
            // get the collision info
            CollisionInfo collisionInfo = player->weapon.getCollisionInfo(staticEntities[i]);
            // revert the player position based on the collision info
            if (collisionInfo.isCollidingLeft || collisionInfo.isCollidingRight) {
                player->weapon.pos.x = player->weapon.lastPos.x;
            }
            if (collisionInfo.isCollidingTop || collisionInfo.isCollidingBottom) {
                player->weapon.pos.y = player->weapon.lastPos.y;
            }
        }
        // check for collisions between the enemies and the static entities
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
            // check for collisions between the player weapon and the enemies
            // check for collisions between the player weapon and the enemies
            if (player->weapon.isCollidingWith(enemies[j])) {
                // to avoid unnecessary calculations, only check for collisions if the weapon is not on cooldown or if the enemy was not already hit by the weapon
                if (player->weapon.isOnCooldown && !enemies[j].getWasHit()) {
                    // get the collision info
                    CollisionInfo collisionInfo = player->weapon.getCollisionInfo(enemies[j]);
                    // revert the enemy position based on the collision info
                    if (collisionInfo.isCollidingLeft || collisionInfo.isCollidingRight) {
                        enemies[j].pos.x = enemies[j].lastPos.x;
                    }
                    if (collisionInfo.isCollidingTop || collisionInfo.isCollidingBottom) {
                        enemies[j].pos.y = enemies[j].lastPos.y;
                    }
                    // deal damage to the enemy
                    enemies[j].dealDamage(player->weapon.dammage);
                    // if the enemy is dead, remove it from the level
                    if (enemies[j].getHealth() <= 0) {
                        enemies.erase(enemies.begin() + j);
                        // play the death sound
                        utils::playEnemyDeathSound();
                        // if all the enemies are dead, send the go to next level event
                        if (enemies.size() == 0) {
                            eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::LEVEL, Messages::GO_TO_NEXT_LEVEL);
                        }

                    }
                    // set the enemy to wasHit so that it doesn't get hit multiple times by the same weapon swing
                    enemies[j].setWasHit(true);

                    // play the hit sound
                    utils::playEnemyHitSound();
                }
            }
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (player->isCollidingWith(enemies[i])) {
            // push the player away from the enemy
//            Vector2f direction = utils::normalize(player->pos - enemies[i].pos);
//            player->pos += direction * (15.0f*SCALE_FACTOR);
            // hurt the player
            player->health -= enemies[i].getDamage();
            utils::playPlayerHitSound();
            // deal damage to the enemy
            enemies[i].dealDamage(5);
            // change its speed to negative so that it gets pushed away from the player
            enemies[i].speed = -8;
            // if the enemy is dead, remove it from the level
            if (enemies[i].getHealth() <= 0) {
                enemies.erase(enemies.begin() + i);
                // play the death sound
                utils::playEnemyDeathSound();
                // if all the enemies are dead, send the go to next level event
                if (enemies.size() == 0) {
                    eventManager.sendMessage(Messages::IDs::GAME, Messages::IDs::LEVEL, Messages::GO_TO_NEXT_LEVEL);
                }
            }
        }
    }
    // process messages
    for (auto &message : eventManager.getMessages(Messages::IDs::LEVEL)) {
        if (message.message == Messages::COOLDOWN_RESET) {
            // range over the enemies and set their wasHit to false
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].setWasHit(false);
            }
            // play the cooldown reset sound
            utils::playCooldownResetSound();
            eventManager.clearMessage(message.MessageID);
        }
        if (message.message == Messages::PLAYER_DIED) {
            playerDead = true;
            // stop the music
            utils::stopMusic();
            // remove trigger from all the entities
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].setTriggered(false);
            }
            eventManager.clearMessage(message.MessageID);
        }
        if (message.message == Messages::WIN_GAME) {
            // set the game to won
            gameWon = true;
            // set the player to dead so that it doesn't move
            player->dead = true;
            // stop the music
            utils::stopMusic();
            // remove trigger from all the entities
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].setTriggered(false);
            }
            eventManager.clearMessage(message.MessageID);
        }
    }
}

void Level::render(Renderer *renderer){
    //center the camera on the player
    // the camera position is the top left corner of the camera
    renderer->camera.newPos.x = player->pos.x + player->width/2- renderer->camera.w/2/SCALE_FACTOR ;
    renderer->camera.newPos.y = player->pos.y + player->height/2- renderer->camera.h/2/SCALE_FACTOR;
    // clamp the camera to the level
    if (renderer->camera.newPos.x < 0) {
        renderer->camera.newPos.x = 0;
    }
    if (renderer->camera.newPos.y < 0) {
        renderer->camera.newPos.y = 0;
    }
    if (renderer->camera.newPos.x > levelData.getLevelWidth()*SCALE_FACTOR - renderer->camera.w+16*SCALE_FACTOR) {
        renderer->camera.newPos.x = levelData.getLevelWidth()*SCALE_FACTOR - renderer->camera.w+16*SCALE_FACTOR;
    }
    if (renderer->camera.newPos.y > levelData.getLevelHeight()*SCALE_FACTOR - renderer->camera.h) {
        renderer->camera.newPos.y = levelData.getLevelHeight()*SCALE_FACTOR - renderer->camera.h;
    }
    // lerping the camera position
    renderer->camera.pos = utils::lerpVector2f(renderer->camera.pos, renderer->camera.newPos, 0.07f);

    // render the static entities
    for (int i = 0; i < staticEntities.size(); i++) {
        staticEntities[i].render(renderer);
    }
    // render the enemies
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].render(renderer);
    }
    // render the player
    player->render(renderer);
    // print the level name for debug purposes
    utils::renderText(renderer->getRenderer(), getLevelName(), WINDOW_WIDTH/2, 20, SDL_Color {255, 255, 255});
    // print the timer with one digit precision
    if (getLevelName() != "Level 1") {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << timer;
        std::string timerText = stream.str();
        utils::renderText(renderer->getRenderer(), "Timer : "+timerText, WINDOW_WIDTH - 120, 20, SDL_Color{255, 255, 255});
    }
    // render the remaining enemies under the timer
        utils::renderText(renderer->getRenderer(), "Remaining :", WINDOW_WIDTH - 120, 60,SDL_Color{255, 255, 255});
        utils::renderText(renderer->getRenderer(), std::to_string(enemies.size()), WINDOW_WIDTH - 120, 90,SDL_Color{255, 255, 255});
    // if the player is dead render the game over overlay
    if (player->health <= 0) {
        // change the blend mode to render the overlay
        SDL_SetRenderDrawBlendMode(renderer->getRenderer(), SDL_BLENDMODE_BLEND);
        // draw the overlay
        SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 100);
        SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderFillRect(renderer->getRenderer(), &rect);
        // render the game over text
        utils::renderText(renderer->getRenderer(), "Game Over", WINDOW_WIDTH/2, WINDOW_HEIGHT/2-40, SDL_Color {255, 0, 0});
        // render the restart text
        utils::renderText(renderer->getRenderer(), "Press Enter to restart", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, SDL_Color {255, 0, 0});
        // add the credits text
        utils::renderText(renderer->getRenderer(), "Made by : Luca Morgado", WINDOW_WIDTH/2, WINDOW_HEIGHT-50, SDL_Color {255, 255, 255});
    }
    // if the game is won render the game won overlay
    if (gameWon) {
        // change the blend mode to render the overlay
        SDL_SetRenderDrawBlendMode(renderer->getRenderer(), SDL_BLENDMODE_BLEND);
        // draw the overlay
        SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 100);
        SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderFillRect(renderer->getRenderer(), &rect);
        // render the game won text
        utils::renderText(renderer->getRenderer(), "You Won", WINDOW_WIDTH/2, WINDOW_HEIGHT/2-40, SDL_Color {0, 255, 0});
        // render the restart text
        utils::renderText(renderer->getRenderer(), "Press Enter to restart", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, SDL_Color {0, 255, 0});
        // add the credits text
        utils::renderText(renderer->getRenderer(), "Made by : Luca Morgado", WINDOW_WIDTH/2, WINDOW_HEIGHT-50, SDL_Color {255, 255, 255});
    }

    // draw tutorial text if the level name is Level 1
    if (getLevelName() == "Level 1") {
        timer = 0;
        // fist tutorial text is on to of the player spawn point
        Vector2f textPos = levelData.getPlayerSpawnPoint();
        textPos.y -= 10*SCALE_FACTOR;

        Vector2f pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "Use ZQSD to move", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 614;
        textPos.y = 87;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "You can left click", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 614;
        textPos.y = 97;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "to deal damage to enemies", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 614;
        textPos.y = 662;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "You need to kill all enemies", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 614;
        textPos.y = 672;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "to progress", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 480;
        textPos.y = 480;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "You have 60 seconds", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 480;
        textPos.y = 490;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "to clear the level", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 750;
        textPos.y = 480;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "Your sword deals +1 damage", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
        textPos.x = 750;
        textPos.y = 490;
        pos = renderer->worldspaceToScreenspace(textPos);
        utils::renderText(renderer->getRenderer(), "for every level you clear", pos.x*SCALE_FACTOR, pos.y*SCALE_FACTOR, SDL_Color {255, 255, 255});
    }



}

LevelData::LevelData() {
    levelName = "default";
}

LevelData::~LevelData() {

}

bool LevelData::Deserialize(const rapidjson::Value &obj) {
    setLevelName(obj["levelName"].GetString());
    // check if the levelname was set
    if (getLevelName().empty()) {
        std::cout << "Error: levelName not found in level data" << std::endl;
        return false;
    }


    // check if the playerSpawnPoint was set
    rapidjson::Value::ConstMemberIterator itr = obj.FindMember("playerSpawnPoint");
    if (itr == obj.MemberEnd()) {
        std::cout << "Error: playerSpawnPoint not found in level data" << std::endl;
        return false;
    }
    // check if the x and y values of the playerSpawnPoint were set
    rapidjson::Value::ConstMemberIterator itr2 = itr->value.FindMember("x");
    if (itr2 == itr->value.MemberEnd()) {
        std::cout << "Error: playerSpawnPoint.x not found in level data" << std::endl;
        return false;
    }
    // check if the x and y values of the playerSpawnPoint were set
    rapidjson::Value::ConstMemberIterator itr3 = itr->value.FindMember("y");
    if (itr3 == itr->value.MemberEnd()) {
        std::cout << "Error: playerSpawnPoint.y not found in level data" << std::endl;
        return false;
    }
    // set the playerSpawnPoint
    setPlayerSpawnPoint(Vector2f(itr2->value.GetDouble(), itr3->value.GetDouble()));

    // check if the staticEntities array was set
    itr = obj.FindMember("staticEntities");
    if (itr == obj.MemberEnd()) {
        std::cout << "Error: staticEntities not found in level data" << std::endl;
        return false;
    }
    // check if the staticEntities array is an array
    if (!itr->value.IsArray()) {
        std::cout << "Error: staticEntities is not an array in level data" << std::endl;
        return false;
    }


    // iterate through the staticEntities array and print each object in the array
    for (rapidjson::SizeType i = 0; i < itr->value.Size(); i++) {
        // check if the object in the array is an object
        if (!itr->value[i].IsObject()) {
            std::cout << "Error: staticEntities[" << i << "] is not an object in level data" << std::endl;
            return false;
        }
        auto tempObj = itr->value[i].GetObject();
        rapidjson::Value::ConstMemberIterator texNameVal = tempObj.FindMember("textureName");
        if (texNameVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].textureName not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator xVal = tempObj.FindMember("x");
        if (xVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].x not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator yVal = tempObj.FindMember("y");
        if (yVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].y not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator collidableVal = tempObj.FindMember("collidable");
        if (collidableVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].collidable not found in level data" << std::endl;
            return false;
        }
        int w = 0;
        int h = 0;
        // if present, get the width and height of the static entity
        rapidjson::Value::ConstMemberIterator widthVal = tempObj.FindMember("width");
        if (widthVal != tempObj.MemberEnd()) {
            w = widthVal->value.GetInt();
        }
        rapidjson::Value::ConstMemberIterator heightVal = tempObj.FindMember("height");
        if (heightVal != tempObj.MemberEnd()) {
            h = heightVal->value.GetInt();
        }

        // add the static entity to the staticEntities vector
        staticEntities.emplace_back(Vector2f(xVal->value.GetDouble(), yVal->value.GetDouble()), texNameVal->value.GetString(),w,h,collidableVal->value.GetBool());
    }

    // check if the enemies array was set
    itr = obj.FindMember("enemies");
    if (itr == obj.MemberEnd()) {
        std::cout << "Error: enemies not found in level data" << std::endl;
        return false;
    }
    // check if the enemies array is an array
    if (!itr->value.IsArray()) {
        std::cout << "Error: enemies is not an array in level data" << std::endl;
        return false;
    }

    // iterate through the enemies array and print each object in the array
    for (rapidjson::SizeType i = 0; i < itr->value.Size(); i++) {
        if (!itr->value[i].IsObject()) {
            std::cout << "Error: enemies[" << i << "] is not an object in level data" << std::endl;
            return false;
        }
        auto tempObj = itr->value[i].GetObject();
        rapidjson::Value::ConstMemberIterator typeVal = tempObj.FindMember("type");
        if (typeVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].textureName not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator xVal = tempObj.FindMember("x");
        if (xVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].x not found in level data" << std::endl;
            return false;
        }
        rapidjson::Value::ConstMemberIterator yVal = tempObj.FindMember("y");
        if (yVal == tempObj.MemberEnd()) {
            std::cout << "Error: staticEntities[" << i << "].y not found in level data" << std::endl;
            return false;
        }
        std::string type = typeVal->value.GetString();
        if (type == "enemy") {
            int w, h;
            SDL_QueryTexture(animation::big_demonAnimations.idleAnimation[0], NULL, NULL, &w, &h);
            enemies.emplace_back(Vector2f(xVal->value.GetDouble(), yVal->value.GetDouble()),&animation::big_demonAnimations, w, h, 100, 1, nullptr, 10);
        }
        if (type == "tutorialEnemy"){
            int w, h;
            SDL_QueryTexture(animation::big_demonAnimations.idleAnimation[0], NULL, NULL, &w, &h);
            enemies.emplace_back(Vector2f(xVal->value.GetDouble(), yVal->value.GetDouble()),&animation::big_demonAnimations, w, h, 100, 1, nullptr, 2);
        }

        if (type == "bigDemon") {
            int w, h;
            SDL_QueryTexture(animation::big_demonAnimations.idleAnimation[0], NULL, NULL, &w, &h);
            enemies.emplace_back(Vector2f(xVal->value.GetDouble(), yVal->value.GetDouble()),&animation::big_demonAnimations, w, h, 100, 2, nullptr, 10);
        }
        if (type == "imp"){
            int w, h;
            SDL_QueryTexture(animation::impAnimations.idleAnimation[0], NULL, NULL, &w, &h);
            enemies.emplace_back(Vector2f(xVal->value.GetDouble(), yVal->value.GetDouble()),&animation::impAnimations, w, h, 100, 1, nullptr, 2);
        }


    }

    //calculate the level width and height based on the static entities
    int levelWidth = 0;
    int levelHeight = 0;
    for (int i = 0; i < staticEntities.size(); i++) {
        if (staticEntities[i].pos.x + staticEntities[i].width > levelWidth) {
            levelWidth = staticEntities[i].pos.x + staticEntities[i].width;
        }
        if (staticEntities[i].pos.y + staticEntities[i].height > levelHeight) {
            levelHeight = staticEntities[i].pos.y + staticEntities[i].height;
        }
    }
    setLevelWidth(levelWidth);
    setLevelHeight(levelHeight);
    return true;
}

bool LevelData::Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const {
    writer->StartObject();
        writer->String("levelName");
        writer->String(levelName.c_str());

        writer->String("playerSpawnPoint");
        writer->StartObject();
            writer->String("x");
            writer->Double(playerSpawnPoint.x);
            writer->String("y");
            writer->Double(playerSpawnPoint.y);
        writer->EndObject();
        writer->String("staticEntities");
            writer->StartArray();
                for (int i = 0; i < staticEntities.size(); i++) {
                    writer->StartObject();
                        writer->String("textureName");
                        writer->String(staticEntities[i].texName.c_str());
                        writer->String("x");
                        writer->Double(staticEntities[i].pos.x);
                        writer->String("y");
                        writer->Double(staticEntities[i].pos.y);
                        writer->String("collidable");
                        writer->Bool(staticEntities[i].collidable);
                        if (staticEntities[i].width > 0 || staticEntities[i].height > 0) {
                            writer->String("width");
                            writer->Int(staticEntities[i].width);
                            writer->String("height");
                            writer->Int(staticEntities[i].height);
                        }
                    writer->EndObject();
                }
        writer->EndArray();
        writer->String("enemies");
        writer->StartArray();
            for (int i = 0; i < enemies.size(); i++) {
                writer->StartObject();
                    writer->String("type");
                    writer->String(enemies[i].type.c_str());
                    writer->String("x");
                    writer->Double(enemies[i].pos.x);
                    writer->String("y");
                    writer->Double(enemies[i].pos.y);
                writer->EndObject();
            }
        writer->EndArray();


    writer->EndObject();
    return true;
}

