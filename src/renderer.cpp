#pragma once
#include "../include/renderer.hpp"
#include "../include/utils.hpp"


Renderer::Renderer(const char* title, int width, int height){
    int succes = SDL_Init(SDL_INIT_VIDEO);
    if(succes != 0){
        utils::logLastSDLError();
        exit(1);
    }
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        utils::logLastSDLError();
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        utils::logLastSDLError();
        exit(1);
    }
    camera.w = width;
    camera.h = height;
    camera.pos.x = 0;
    camera.pos.y = 0;
    camera.newPos = camera.pos;
}
