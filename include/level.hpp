#pragma once
#include "../include/renderer.hpp"
#include <SDL2/SDL.h>
#include "../include/entity.hpp"
#include "../include/player.hpp"
#include "../include/tile_info.hpp"
#include "../include/event_manager.hpp"
#include "../include/staticEntity.hpp"
#include <vector>
#include <string>
#include <map>
#include "../include/json.hpp"
#include "../include/enemy.hpp"

// LevelData class
class LevelData : public JSON
{
public:
    LevelData();
    ~LevelData();

    virtual bool Deserialize(const rapidjson::Value& obj);
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

    // getters and setters
    std::string getLevelName() const { return levelName; }
    void setLevelName(std::string lName) { this->levelName = lName; }

    Vector2f getPlayerSpawnPoint() const { return playerSpawnPoint; }
    void setPlayerSpawnPoint(Vector2f pSpawnPoint) { this->playerSpawnPoint = pSpawnPoint; }

    std::vector<StaticEntity> getStaticEntities() const { return staticEntities; }
    void setStaticEntities(std::vector<StaticEntity> sEntities) { this->staticEntities = sEntities; }

    std::vector<Enemy> getEnemies() const { return enemies; }
    void setEnemies(std::vector<Enemy> enemiess) { this->enemies = enemiess; }

    int getLevelWidth() const { return levelWidth; }
    void setLevelWidth(int lWidth) { this->levelWidth = lWidth; }

    int getLevelHeight() const { return levelHeight; }
    void setLevelHeight(int lHeight) { this->levelHeight = lHeight; }

private:
    std::string levelName;
    Vector2f playerSpawnPoint;
    std::vector<StaticEntity> staticEntities;
    std::vector<Enemy> enemies;
    int levelWidth;
    int levelHeight;
};




// Level class
class Level
{
public:
    Level(SDL_Renderer *renderer,Player *player ,std::string levelDataFileName, SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap);
    Level() {}
    void update(EventManager &eventManager);
    void render(Renderer *renderer);

    // getters
    std::string getLevelName() const { return levelData.getLevelName(); }
    std::vector<Entity> *getEntities() const { return (std::vector<Entity> *)&entities; }
    std::vector<StaticEntity> *getStaticEntities() const { return (std::vector<StaticEntity> *)&staticEntities; }
    void setStaticEntities(std::vector<StaticEntity> sEntities) { this->staticEntities = sEntities; }
    Player *getPlayer() const { return player; }
    LevelData *getLevelData() const { return (LevelData *)&levelData; }
    std::vector<Enemy> *getEnemies() const { return (std::vector<Enemy> *)&enemies; }
    void setEnemies(std::vector<Enemy> enemiess) { this->enemies = enemiess; }
    std::vector<Entity> entities;
    std::vector<Enemy> enemies;
    std::vector<StaticEntity> staticEntities;
    float timer;
    Player *player;
    Vector2f playerSpawnPoint;
    bool playerDead;
    bool gameWon;
    LevelData levelData;
};