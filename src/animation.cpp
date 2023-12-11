#include "../include/animation.hpp"

namespace animation {

    float timeBetweenFrames = 0.05f;
    Animations big_demonAnimations = Animations();
    Animations big_zombieAnimations = Animations();
    Animations coinAnimations = Animations();
    Animations wizzard_fAnimations = Animations();
    Animations wizzard_mAnimations = Animations();
    Animations impAnimations = Animations();
    Animations lizard_fAnimations = Animations();
    Animations lizard_mAnimations = Animations();
    Animations dwarf_mAnimations= Animations();
    Animations dwarf_fAnimations= Animations();
    Animations knight_fAnimations= Animations();
    Animations knight_mAnimations= Animations();
    Animations wogolAnimations= Animations();
    Animations zombieAnimations= Animations();
    Animations tiny_zombieAnimations= Animations();
    Animations goblinAnimations= Animations();
    Animations ice_zombieAnimations= Animations();
    Animations orc_shamanAnimations= Animations();
    Animations swampyAnimations= Animations();
    Animations muddyAnimations= Animations();
    Animations necromancerAnimations= Animations();
    Animations masked_orcAnimations= Animations();
    Animations orc_warriorAnimations= Animations();
    Animations skeletAnimations= Animations();
    Animations ogreAnimations= Animations();
    Animations docAnimations= Animations();
    Animations pumpkin_dudeAnimations= Animations();
    Animations angelAnimations= Animations();
    Animations chortAnimations= Animations();
    Animations elf_fAnimations= Animations();
    Animations elf_mAnimations= Animations();
    Animations slugAnimations= Animations();
    Animations tiny_slugAnimations= Animations();
    
    
    Animations loadAnimations(std::vector<SDL_Texture*> idleAnimation, bool hasRunAnimation, std::vector<SDL_Texture*> runAnimation){
        Animations animations;
        animations.idleAnimation = idleAnimation;
        animations.hasRunAnimation = hasRunAnimation;
        if (hasRunAnimation){
            animations.runAnimation = runAnimation;
        }else{
            animations.runAnimation = idleAnimation;
        }
        return animations;
    }

    void loadAllAnimations(SDL_Texture *tilesetTex, std::map<std::string, TileInfo> &tilesInfoMap, SDL_Renderer *renderer) {
        big_demonAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["big_demon_idle_anim_f0"],
                                                    tilesInfoMap["big_demon_idle_anim_f1"],
                                                    tilesInfoMap["big_demon_idle_anim_f2"],
                                                    tilesInfoMap["big_demon_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["big_demon_run_anim_f0"],
                                                    tilesInfoMap["big_demon_run_anim_f1"],
                                                    tilesInfoMap["big_demon_run_anim_f2"],
                                                    tilesInfoMap["big_demon_run_anim_f3"]},
                                            renderer)
        );
        big_zombieAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["big_zombie_idle_anim_f0"],
                                                    tilesInfoMap["big_zombie_idle_anim_f1"],
                                                    tilesInfoMap["big_zombie_idle_anim_f2"],
                                                    tilesInfoMap["big_zombie_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["big_zombie_run_anim_f0"],
                                                    tilesInfoMap["big_zombie_run_anim_f1"],
                                                    tilesInfoMap["big_zombie_run_anim_f2"],
                                                    tilesInfoMap["big_zombie_run_anim_f3"]},
                                            renderer)
        );
        coinAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["coin_anim_f0"],
                                                    tilesInfoMap["coin_anim_f1"],
                                                    tilesInfoMap["coin_anim_f2"],
                                                    tilesInfoMap["coin_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>()
        );
        wizzard_fAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["wizzard_f_idle_anim_f0"],
                                                    tilesInfoMap["wizzard_f_idle_anim_f1"],
                                                    tilesInfoMap["wizzard_f_idle_anim_f2"],
                                                    tilesInfoMap["wizzard_f_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["wizzard_f_run_anim_f0"],
                                                    tilesInfoMap["wizzard_f_run_anim_f1"],
                                                    tilesInfoMap["wizzard_f_run_anim_f2"],
                                                    tilesInfoMap["wizzard_f_run_anim_f3"]},
                                            renderer)
        );
        wizzard_mAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["wizzard_m_idle_anim_f0"],
                                                    tilesInfoMap["wizzard_m_idle_anim_f1"],
                                                    tilesInfoMap["wizzard_m_idle_anim_f2"],
                                                    tilesInfoMap["wizzard_m_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["wizzard_m_run_anim_f0"],
                                                    tilesInfoMap["wizzard_m_run_anim_f1"],
                                                    tilesInfoMap["wizzard_m_run_anim_f2"],
                                                    tilesInfoMap["wizzard_m_run_anim_f3"]},
                                            renderer)
        );
        impAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["imp_idle_anim_f0"],
                                                    tilesInfoMap["imp_idle_anim_f1"],
                                                    tilesInfoMap["imp_idle_anim_f2"],
                                                    tilesInfoMap["imp_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["imp_run_anim_f0"],
                                                    tilesInfoMap["imp_run_anim_f1"],
                                                    tilesInfoMap["imp_run_anim_f2"],
                                                    tilesInfoMap["imp_run_anim_f3"]},
                                            renderer)
        );
        lizard_fAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["lizard_f_idle_anim_f0"],
                                                    tilesInfoMap["lizard_f_idle_anim_f1"],
                                                    tilesInfoMap["lizard_f_idle_anim_f2"],
                                                    tilesInfoMap["lizard_f_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["lizard_f_run_anim_f0"],
                                                    tilesInfoMap["lizard_f_run_anim_f1"],
                                                    tilesInfoMap["lizard_f_run_anim_f2"],
                                                    tilesInfoMap["lizard_f_run_anim_f3"]},
                                            renderer)
        );
        lizard_mAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["lizard_m_idle_anim_f0"],
                                                    tilesInfoMap["lizard_m_idle_anim_f1"],
                                                    tilesInfoMap["lizard_m_idle_anim_f2"],
                                                    tilesInfoMap["lizard_m_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["lizard_m_run_anim_f0"],
                                                    tilesInfoMap["lizard_m_run_anim_f1"],
                                                    tilesInfoMap["lizard_m_run_anim_f2"],
                                                    tilesInfoMap["lizard_m_run_anim_f3"]},
                                            renderer)
        );
        dwarf_mAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["dwarf_m_idle_anim_f0"],
                                                    tilesInfoMap["dwarf_m_idle_anim_f1"],
                                                    tilesInfoMap["dwarf_m_idle_anim_f2"],
                                                    tilesInfoMap["dwarf_m_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["dwarf_m_run_anim_f0"],
                                                    tilesInfoMap["dwarf_m_run_anim_f1"],
                                                    tilesInfoMap["dwarf_m_run_anim_f2"],
                                                    tilesInfoMap["dwarf_m_run_anim_f3"]},
                                            renderer)
        );
        dwarf_fAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["dwarf_f_idle_anim_f0"],
                                                    tilesInfoMap["dwarf_f_idle_anim_f1"],
                                                    tilesInfoMap["dwarf_f_idle_anim_f2"],
                                                    tilesInfoMap["dwarf_f_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["dwarf_f_run_anim_f0"],
                                                    tilesInfoMap["dwarf_f_run_anim_f1"],
                                                    tilesInfoMap["dwarf_f_run_anim_f2"],
                                                    tilesInfoMap["dwarf_f_run_anim_f3"]},
                                            renderer)
        );
        knight_fAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["knight_f_idle_anim_f0"],
                                                    tilesInfoMap["knight_f_idle_anim_f1"],
                                                    tilesInfoMap["knight_f_idle_anim_f2"],
                                                    tilesInfoMap["knight_f_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["knight_f_run_anim_f0"],
                                                    tilesInfoMap["knight_f_run_anim_f1"],
                                                    tilesInfoMap["knight_f_run_anim_f2"],
                                                    tilesInfoMap["knight_f_run_anim_f3"]},
                                            renderer)
        );
        knight_mAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["knight_m_idle_anim_f0"],
                                                    tilesInfoMap["knight_m_idle_anim_f1"],
                                                    tilesInfoMap["knight_m_idle_anim_f2"],
                                                    tilesInfoMap["knight_m_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["knight_m_run_anim_f0"],
                                                    tilesInfoMap["knight_m_run_anim_f1"],
                                                    tilesInfoMap["knight_m_run_anim_f2"],
                                                    tilesInfoMap["knight_m_run_anim_f3"]},
                                            renderer)
        );
        wogolAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["wogol_idle_anim_f0"],
                                                    tilesInfoMap["wogol_idle_anim_f1"],
                                                    tilesInfoMap["wogol_idle_anim_f2"],
                                                    tilesInfoMap["wogol_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["wogol_run_anim_f0"],
                                                    tilesInfoMap["wogol_run_anim_f1"],
                                                    tilesInfoMap["wogol_run_anim_f2"],
                                                    tilesInfoMap["wogol_run_anim_f3"]},
                                            renderer)
        );
        zombieAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["zombie_anim_f0"],
                                                    tilesInfoMap["zombie_anim_f1"],
                                                    tilesInfoMap["zombie_anim_f2"],
                                                    tilesInfoMap["zombie_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>{}
        );
        tiny_zombieAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["tiny_zombie_idle_anim_f0"],
                                                    tilesInfoMap["tiny_zombie_idle_anim_f1"],
                                                    tilesInfoMap["tiny_zombie_idle_anim_f2"],
                                                    tilesInfoMap["tiny_zombie_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["tiny_zombie_run_anim_f0"],
                                                    tilesInfoMap["tiny_zombie_run_anim_f1"],
                                                    tilesInfoMap["tiny_zombie_run_anim_f2"],
                                                    tilesInfoMap["tiny_zombie_run_anim_f3"]},
                                            renderer)
        );
        goblinAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["goblin_idle_anim_f0"],
                                                    tilesInfoMap["goblin_idle_anim_f1"],
                                                    tilesInfoMap["goblin_idle_anim_f2"],
                                                    tilesInfoMap["goblin_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["goblin_run_anim_f0"],
                                                    tilesInfoMap["goblin_run_anim_f1"],
                                                    tilesInfoMap["goblin_run_anim_f2"],
                                                    tilesInfoMap["goblin_run_anim_f3"]},
                                            renderer)
        );
        ice_zombieAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["ice_zombie_anim_f0"],
                                                    tilesInfoMap["ice_zombie_anim_f1"],
                                                    tilesInfoMap["ice_zombie_anim_f2"],
                                                    tilesInfoMap["ice_zombie_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>{}
        );
        orc_shamanAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["orc_shaman_idle_anim_f0"],
                                                    tilesInfoMap["orc_shaman_idle_anim_f1"],
                                                    tilesInfoMap["orc_shaman_idle_anim_f2"],
                                                    tilesInfoMap["orc_shaman_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["orc_shaman_run_anim_f0"],
                                                    tilesInfoMap["orc_shaman_run_anim_f1"],
                                                    tilesInfoMap["orc_shaman_run_anim_f2"],
                                                    tilesInfoMap["orc_shaman_run_anim_f3"]},
                                            renderer)
        );
        swampyAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["swampy_anim_f0"],
                                                    tilesInfoMap["swampy_anim_f1"],
                                                    tilesInfoMap["swampy_anim_f2"],
                                                    tilesInfoMap["swampy_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>{}
        );
        muddyAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["muddy_anim_f0"],
                                                    tilesInfoMap["muddy_anim_f1"],
                                                    tilesInfoMap["muddy_anim_f2"],
                                                    tilesInfoMap["muddy_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>{}
        );
        necromancerAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["necromancer_anim_f0"],
                                                    tilesInfoMap["necromancer_anim_f1"],
                                                    tilesInfoMap["necromancer_anim_f2"],
                                                    tilesInfoMap["necromancer_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>{}
        );
        masked_orcAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["masked_orc_idle_anim_f0"],
                                                    tilesInfoMap["masked_orc_idle_anim_f1"],
                                                    tilesInfoMap["masked_orc_idle_anim_f2"],
                                                    tilesInfoMap["masked_orc_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["masked_orc_run_anim_f0"],
                                                    tilesInfoMap["masked_orc_run_anim_f1"],
                                                    tilesInfoMap["masked_orc_run_anim_f2"],
                                                    tilesInfoMap["masked_orc_run_anim_f3"]},
                                            renderer)
        );
        orc_warriorAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["orc_warrior_idle_anim_f0"],
                                                    tilesInfoMap["orc_warrior_idle_anim_f1"],
                                                    tilesInfoMap["orc_warrior_idle_anim_f2"],
                                                    tilesInfoMap["orc_warrior_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["orc_warrior_run_anim_f0"],
                                                    tilesInfoMap["orc_warrior_run_anim_f1"],
                                                    tilesInfoMap["orc_warrior_run_anim_f2"],
                                                    tilesInfoMap["orc_warrior_run_anim_f3"]},
                                            renderer)
        );
        skeletAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["skelet_idle_anim_f0"],
                                                    tilesInfoMap["skelet_idle_anim_f1"],
                                                    tilesInfoMap["skelet_idle_anim_f2"],
                                                    tilesInfoMap["skelet_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["skelet_run_anim_f0"],
                                                    tilesInfoMap["skelet_run_anim_f1"],
                                                    tilesInfoMap["skelet_run_anim_f2"],
                                                    tilesInfoMap["skelet_run_anim_f3"]},
                                            renderer)
        );
        ogreAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["ogre_idle_anim_f0"],
                                                    tilesInfoMap["ogre_idle_anim_f1"],
                                                    tilesInfoMap["ogre_idle_anim_f2"],
                                                    tilesInfoMap["ogre_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["ogre_run_anim_f0"],
                                                    tilesInfoMap["ogre_run_anim_f1"],
                                                    tilesInfoMap["ogre_run_anim_f2"],
                                                    tilesInfoMap["ogre_run_anim_f3"]},
                                            renderer)
        );
        docAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["doc_idle_anim_f0"],
                                                    tilesInfoMap["doc_idle_anim_f1"],
                                                    tilesInfoMap["doc_idle_anim_f2"],
                                                    tilesInfoMap["doc_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["doc_run_anim_f0"],
                                                    tilesInfoMap["doc_run_anim_f1"],
                                                    tilesInfoMap["doc_run_anim_f2"],
                                                    tilesInfoMap["doc_run_anim_f3"]},
                                            renderer)
        );
        pumpkin_dudeAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["pumpkin_dude_idle_anim_f0"],
                                                    tilesInfoMap["pumpkin_dude_idle_anim_f1"],
                                                    tilesInfoMap["pumpkin_dude_idle_anim_f2"],
                                                    tilesInfoMap["pumpkin_dude_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["pumpkin_dude_run_anim_f0"],
                                                    tilesInfoMap["pumpkin_dude_run_anim_f1"],
                                                    tilesInfoMap["pumpkin_dude_run_anim_f2"],
                                                    tilesInfoMap["pumpkin_dude_run_anim_f3"]},
                                            renderer)
        );
        angelAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["angel_idle_anim_f0"],
                                                    tilesInfoMap["angel_idle_anim_f1"],
                                                    tilesInfoMap["angel_idle_anim_f2"],
                                                    tilesInfoMap["angel_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["angel_run_anim_f0"],
                                                    tilesInfoMap["angel_run_anim_f1"],
                                                    tilesInfoMap["angel_run_anim_f2"],
                                                    tilesInfoMap["angel_run_anim_f3"]},
                                            renderer)
        );
        chortAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["chort_idle_anim_f0"],
                                                    tilesInfoMap["chort_idle_anim_f1"],
                                                    tilesInfoMap["chort_idle_anim_f2"],
                                                    tilesInfoMap["chort_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["chort_run_anim_f0"],
                                                    tilesInfoMap["chort_run_anim_f1"],
                                                    tilesInfoMap["chort_run_anim_f2"],
                                                    tilesInfoMap["chort_run_anim_f3"]},
                                            renderer)
        );
        elf_fAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["elf_f_idle_anim_f0"],
                                                    tilesInfoMap["elf_f_idle_anim_f1"],
                                                    tilesInfoMap["elf_f_idle_anim_f2"],
                                                    tilesInfoMap["elf_f_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["elf_f_run_anim_f0"],
                                                    tilesInfoMap["elf_f_run_anim_f1"],
                                                    tilesInfoMap["elf_f_run_anim_f2"],
                                                    tilesInfoMap["elf_f_run_anim_f3"]},
                                            renderer)
        );
        elf_mAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["elf_m_idle_anim_f0"],
                                                    tilesInfoMap["elf_m_idle_anim_f1"],
                                                    tilesInfoMap["elf_m_idle_anim_f2"],
                                                    tilesInfoMap["elf_m_idle_anim_f3"]},
                                            renderer),
                true,
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["elf_m_run_anim_f0"],
                                                    tilesInfoMap["elf_m_run_anim_f1"],
                                                    tilesInfoMap["elf_m_run_anim_f2"],
                                                    tilesInfoMap["elf_m_run_anim_f3"]},
                                            renderer)
        );
        slugAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["slug_anim_f0"],
                                                    tilesInfoMap["slug_anim_f1"],
                                                    tilesInfoMap["slug_anim_f2"],
                                                    tilesInfoMap["slug_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>{}
        );
        tiny_slugAnimations = animation::loadAnimations(
                utils::loadTilesFromTileset(tilesetTex, std::vector<TileInfo>{
                                                    tilesInfoMap["tiny_slug_anim_f0"],
                                                    tilesInfoMap["tiny_slug_anim_f1"],
                                                    tilesInfoMap["tiny_slug_anim_f2"],
                                                    tilesInfoMap["tiny_slug_anim_f3"]},
                                            renderer),
                false,
                std::vector<SDL_Texture *>{}
        );
    }
}