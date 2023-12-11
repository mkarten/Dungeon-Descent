#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include <string>
#include "tile_info.hpp"
#include "utils.hpp"

class Animations{
    public:
    std::vector<SDL_Texture*> idleAnimation;
    bool hasRunAnimation;
    std::vector<SDL_Texture*> runAnimation;
};



namespace animation{
    Animations loadAnimations(std::vector<SDL_Texture*> idleAnimation, bool hasRunAnimation, std::vector<SDL_Texture*> runAnimation);
    extern float timeBetweenFrames;
    extern Animations big_demonAnimations;
    extern Animations big_zombieAnimations;
    extern Animations coinAnimations;
    extern Animations wizzard_fAnimations;
    extern Animations wizzard_mAnimations;
    extern Animations impAnimations;
    extern Animations lizard_fAnimations;
    extern Animations lizard_mAnimations;
    extern Animations dwarf_mAnimations;
    extern Animations dwarf_fAnimations;
    extern Animations knight_fAnimations;
    extern Animations knight_mAnimations;
    extern Animations wogolAnimations;
    extern Animations zombieAnimations;
    extern Animations tiny_zombieAnimations;
    extern Animations goblinAnimations;
    extern Animations ice_zombieAnimations;
    extern Animations orc_shamanAnimations;
    extern Animations swampyAnimations;
    extern Animations muddyAnimations;
    extern Animations necromancerAnimations;
    extern Animations masked_orcAnimations;
    extern Animations orc_warriorAnimations;
    extern Animations skeletAnimations;
    extern Animations ogreAnimations;
    extern Animations docAnimations;
    extern Animations pumpkin_dudeAnimations;
    extern Animations angelAnimations;
    extern Animations chortAnimations;
    extern Animations elf_fAnimations;
    extern Animations elf_mAnimations;
    extern Animations slugAnimations;
    extern Animations tiny_slugAnimations;
    void loadAllAnimations( SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap, SDL_Renderer *renderer);
}

