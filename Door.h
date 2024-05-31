#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include "Player.h"

// The Door class represents a door that connects two rooms and requires a certain level to pass through.
class Door : public Passage {
public:

    // Constructor that initializes the door with a name, description, from and to rooms, and the required level to pass.
    Door(const std::string &n, const std::string &d, Room* from, Room* to, int requiredLevel)
        : Passage(n, d, from, to), requiredLevel(requiredLevel) {}

    // Method to handle entering through the door.
    void enter() override {
        Player* player = Player::instance();

        // Check if the player's level is sufficient to enter the room.
        if (player->getLevel() < requiredLevel) {
            std::cout << "You need to be at least level " << requiredLevel << " to enter the " << toRoom->getName() << ".\n\n";
            player->setCurrentRoom(fromRoom);  // Ensure the player remains in the current room.
            return;
        }
        Passage::enter();
        
        // Create a basic passage after the player successfully enters the target room.
        if (toRoom->getName() == "ancient-temple") {
            Passage::createBasicPassage(toRoom, fromRoom, "east", true);
        }
    }

private:
    // The required level to pass through the door.
    int requiredLevel;
};

#endif // ZOORK_DOOR_H
