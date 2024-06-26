#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include "Merchant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// The ZOOrkEngine class is the main class for the game. It handles the game loop and player input.
class ZOOrkEngine {
public:
    // Constructor for the ZOOrkEngine class. Initializes the game with a starting room and the magic forest.
    ZOOrkEngine(std::shared_ptr<Room> start, std::shared_ptr<Room> magic_forest);

    void run();

private:
    
    bool gameOver = false;
    bool deerFound = false;
    bool deerFeed = false;
    bool mushroomFound = false;
    bool mushroomTaken = false;
    bool keyTaken = false;
    bool plantMoved = false;
    Player *player;
    std::shared_ptr<Room> startRoom;
    std::shared_ptr<Room> magicForest;
    std::shared_ptr<Room> ancientTreeTop;

    void handleGoCommand(std::vector<std::string>);
    void handleLookCommand(std::vector<std::string>);
    void handleTakeCommand(std::vector<std::string>);
    void handleDropCommand(std::vector<std::string>);
    void handleInventoryCommand(std::vector<std::string>);
    void handleEquipmentCommand(std::vector<std::string>);
    void handleUseCommand(std::vector<std::string>);
    void handleUnattachCommand(std::vector<std::string>);
    void handleLiftCommand(std::vector<std::string>);
    void handleOpenCommand(std::vector<std::string>);
    void handleInteractCommand(std::vector<std::string>);
    void handleFeedCommand(std::vector<std::string>);
    void handleBuyCommand(std::vector<std::string>);
    void handleSellCommand(std::vector<std::string>);
    void handleAttackCommand(std::vector<std::string>);
    void handleQuitCommand(std::vector<std::string>);
    void handleCheckInfoCommand(std::vector<std::string>);
    void handleQuestStatusCommand(std::vector<std::string>); 

    static std::vector<std::string> tokenizeString(const std::string&);
    static std::string makeLowercase(std::string);
};

#endif //ZOORK_ZOORKENGINE_H
