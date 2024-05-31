#ifndef ZOORK_VILLAGER_H
#define ZOORK_VILLAGER_H

#include "Character.h"

// The Villager class represents a character in the game.
class Villager : public Character {
public:

    // Constructor for the Villager class. Initializes the villager with a name and description.
    Villager(const std::string &n, const std::string &d);

    // Method to interact with the villager.
    void interact() override;

private:
    bool questGiven;        // A flag to track if the villager has given a quest.
    bool questCompleted;    // A flag to track if the quest has been completed.
};

#endif //ZOORK_VILLAGER_H