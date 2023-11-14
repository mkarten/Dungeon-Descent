#pragma once

#include <SDL2/SDL.h>
#include <vector>

struct Mouse{
    int x;
    int y;
    bool Buttons[5];
    bool LastButtons[5];
    bool ScrolledUp = false;
    bool ScrolledDown = false;
    void setLastButtons(const bool b[5])
    {
        for(int i = 0; i < 5; i++)
        {
            LastButtons[i] = b[i];
        }
    }
};

class EventManager{
public:
    EventManager();
    ~EventManager();
    void update();
    bool GameIsRunning = true;
    bool Keys[322];
    bool LastKeys[322];
    void setLastKeys(const bool b[322])
    {
        for(int i = 0; i < 322; i++)
        {
            LastKeys[i] = b[i];
        }
    }
    Mouse mouse;

};