#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ZOOrkEngine {
public:
    ZOOrkEngine(std::shared_ptr<Room> start, std::shared_ptr<Room> magic_forest);

    void run();

private:
    bool gameOver = false;
    bool deerFound = false;
    bool mushroomFound = false;
    bool mushroomTaken = false;
    bool keyTaken = false;
    bool plantMoved = false;
    bool climbTree = false;
    Player *player;
    std::shared_ptr<Room> startRoom;
    std::shared_ptr<Room> magicForest;

    void handleGoCommand(std::vector<std::string>);
    void handleLookCommand(std::vector<std::string>);
    void handleTakeCommand(std::vector<std::string>);
    void handleDropCommand(std::vector<std::string>);
    void handleInventoryCommand(std::vector<std::string>);
    void handleUseCommand(std::vector<std::string>);
    void handleLiftCommand(std::vector<std::string>);
    void handleOpenCommand(std::vector<std::string>);
    void handleInteractCommand(std::vector<std::string>);
    void handleFeedCommand(std::vector<std::string>); 
    void handleClimbCommand(std::vector<std::string>);
    void handleQuitCommand(std::vector<std::string>);

    static std::vector<std::string> tokenizeString(const std::string&);
    static std::string makeLowercase(std::string);
};

#endif //ZOORK_ZOORKENGINE_H
