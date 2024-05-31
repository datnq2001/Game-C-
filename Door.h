#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include "Player.h"

class Door : public Passage {
public:
    Door(const std::string &n, const std::string &d, Room* from, Room* to, int requiredLevel)
        : Passage(n, d, from, to), requiredLevel(requiredLevel) {}

    void enter() override {
        Player* player = Player::instance();
        if (player->getLevel() < requiredLevel) {
            std::cout << "You need to be at least level " << requiredLevel << " to enter the " << toRoom->getName() << ".\n\n";
            player->setCurrentRoom(fromRoom);  // Đảm bảo người chơi vẫn ở phòng hiện tại
            return;
        }
        Passage::enter();
    }

private:
    int requiredLevel;
};

#endif // ZOORK_DOOR_H
