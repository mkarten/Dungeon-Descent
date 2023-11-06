#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/tile_info.hpp"


float hireTimeInSeconds(); // Retourne le temps depuis le lancement du programme en secondes

SDL_Texture* loadTileFromTileset(SDL_Texture* tileset, TileInfo tileInfo, SDL_Renderer* renderer);

