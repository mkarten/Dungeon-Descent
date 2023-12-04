#include <iostream>
#include "../include/event_manager.hpp"
#include "../include/utils.hpp"


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
    mouse.setLastButtons(mouse.Buttons);

}

EventManager::~EventManager()
{

}

void EventManager::update() {
    // update the delta time
    currentTime = utils::hireTimeInSeconds();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // save the current mouse buttons state
    mouse.setLastButtons(mouse.Buttons);
    // save the current keys state
    setLastKeys(Keys);

    // reset the mouse scroll
    mouse.ScrolledUp = false;
    mouse.ScrolledDown = false;

    // Update the events
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                sendMessage(Messages::IDs::GAME, Messages::IDs::GAME, Messages::QUIT_GAME);
                break;
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
            case SDL_MOUSEWHEEL:
                if(event.wheel.y > 0)
                {
                    mouse.ScrolledUp = true;
                }
                else if(event.wheel.y < 0)
                {
                    mouse.ScrolledDown = true;
                }
                break;
            default:
                break;
        }
    }
    // print the message queue
//     for(int i = 0; i < Messages.size(); i++) {
//         std::cout << Messages[i].MessageID << " " << Messages[i].receiverID << " " << Messages[i].senderID << " "
//                   << Messages[i].message << std::endl;
//     }
}