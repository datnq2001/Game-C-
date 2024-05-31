#include "Passage.h"
#include "PassageDefaultEnterCommand.h"
#include "Player.h"

// This function returns the opposite direction of the given string
std::string Passage::oppositeDirection(const std::string &s) {
    if (s == "north") return "south";
    else if (s == "south") return "north";
    else if (s == "east") return "west";
    else if (s == "west") return "east";
    else if (s == "up") return "down";
    else if (s == "down") return "up";
    else if (s == "in") return "out";
    else if (s == "out") return "in";
    else return "unknown_direction";
}

// This function creates a basic passage between two rooms, optionally making it bidirectional
void Passage::createBasicPassage(Room* from, Room* to, const std::string &direction, bool bidirectional) {
    std::string passageName = from->getName() + "_to_" + to->getName();
    auto temp1 = std::make_shared<Passage>(passageName, "A totally normal passageway.", from, to);
    from->addPassage(direction, temp1);

    // If the passage is bidirectional, create a passage in the opposite direction as well
    if (bidirectional) {
        std::string passageName2 = to->getName() + "_to_" + from->getName();
        auto temp2 = std::make_shared<Passage>(passageName2, "A totally normal passageway.", to, from);
        to->addPassage(oppositeDirection(direction), temp2);
    }
}

// Constructor for Passage that sets the enter command to a default passage enter command
Passage::Passage(const std::string &n, const std::string &d, Room* from, Room* to)
        : Location(n, d), fromRoom(from), toRoom(to) {
    setEnterCommand(std::make_shared<PassageDefaultEnterCommand>(this));
}

// Constructor for Passage that allows specifying a custom command
Passage::Passage(const std::string &n, const std::string &d, std::shared_ptr<Command> c, Room* from, Room* to)
        : Location(n, d, std::move(c)), fromRoom(from), toRoom(to) {}

// Sets the room this passage starts from
void Passage::setFrom(Room* r) {
    fromRoom = r;
}

// Returns the room this passage starts from
Room* Passage::getFrom() const {
    return fromRoom;
}

// Sets the room this passage leads to
void Passage::setTo(Room* r) {
    toRoom = r;
}

// Returns the room this passage leads to
Room* Passage::getTo() const {
    return toRoom;
}
