#include <iostream>
#include "../include/event_manager.hpp"


EventManager::EventManager()
{
    // Initialize the Keys array
    for(int i = 0; i < 322; i++)
    {
        Keys[i] = false;
    }
    // Initialize the mouse buttons array
    for(int i = 0; i < 5; i++)
    {
        mouse.Buttons[i] = false;
    }

}

EventManager::~EventManager()
{

}

void EventManager::update(std::vector<SDL_Event> &events) {
    // Update the events
    for(SDL_Event &event: events)
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                Keys[event.key.keysym.scancode]=true;
                break;
            case SDL_KEYUP:
                Keys[event.key.keysym.scancode]=false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse.Buttons[event.button.button] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mouse.Buttons[event.button.button] = false;
                break;
            case SDL_MOUSEMOTION:
                mouse.x = event.motion.x;
                mouse.y = event.motion.y;
                break;
            default:
                break;
        }
    }
}