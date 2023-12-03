#pragma once

#include <SDL2/SDL.h>
#include <vector>

struct Message{
    int MessageID;
    int receiverID;
    int senderID;
    std::string message;
};

namespace Messages{
    const std::string PLAYER_DIED = "PLAYER_DIED";
    const std::string QUIT_GAME = "QUIT_GAME";
    const std::string ENTER_EDITOR_MODE = "ENTER_EDITOR_MODE";
    const std::string START_GAME = "START_GAME";
    const std::string COOLDOWN_RESET = "COOLDOWN_RESET";

    enum IDs{
        GAME,
        EVENT_MANAGER,
        PLAYER,
        PLAYER_WEAPON,
        LEVEL,
    };
}

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
    bool Keys[322];
    bool LastKeys[322];
    int NewMessagesID = 0;
    float deltaTime;
    float currentTime;
    float lastTime;
    std::vector<Message> Messages;
    void sendMessage(int receiverID, int senderID, std::string message){
        Message m;
        m.receiverID = receiverID;
        m.senderID = senderID;
        m.message = message;
        m.MessageID = NewMessagesID;
        NewMessagesID++;
        Messages.push_back(m);
    }
    std::vector<Message> getMessages(int receiverID){
        std::vector<Message> messages;
        for(int i = 0; i < Messages.size(); i++){
            if(Messages[i].receiverID == receiverID){
                messages.push_back(Messages[i]);
            }
        }
        return messages;
    }
    void clearMessage(int MessageID){
        for(int i = 0; i < Messages.size(); i++){
            if(Messages[i].MessageID == MessageID){
                Messages.erase(Messages.begin() + i);
            }
        }
    }
    void setLastKeys(const bool b[322])
    {
        for(int i = 0; i < 322; i++)
        {
            LastKeys[i] = b[i];
        }
    }
    Mouse mouse;

};