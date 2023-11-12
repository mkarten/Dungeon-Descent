#pragma once

#include <SDL2/SDL.h>
#include <vector>

struct Mouse{
    int x;
    int y;
    bool Buttons[5];
};

class EventManager{
public:
    EventManager();
    ~EventManager();
    void update();
    bool GameIsRunning = true;
    bool Keys[322];
    Mouse mouse;

};