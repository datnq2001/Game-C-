#include "Room.h"
#include "NullPassage.h"
#include "RoomDefaultEnterCommand.h"
#include "Key.h"
#include "Enemy.h"

// Constructor for Room with default values for name and description
Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

// Constructor for Room with a command
Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

// Sets the passage in the specified direction
void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

// Removes the passage in the specified direction
void Room::removePassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        passageMap.erase(direction);
    }
}

// Returns the passage in the specified direction
std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n\n";
        return std::make_shared<NullPassage>(this);
    }
}

// Returns the map of passages
void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

// Removes the item with the specified name
void Room::removeItem(const std::string &itemName) {
    items.erase(std::remove_if(items.begin(), items.end(),
                [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; }),
                items.end());
}

// Returns the item with the specified name
std::shared_ptr<Item> Room::getItem(const std::string &itemName) {
    auto it = std::find_if(items.begin(), items.end(),
                [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; });
    return it != items.end() ? *it : nullptr;
}

// Returns the vector of items
std::shared_ptr<Item> Room::retrieveItem(const std::string &itemName) {
    auto item = getItem(itemName);
    if (item) {
        removeItem(itemName);
    }
    return item;
}

// Returns the vector of items
void Room::addCharacter(std::shared_ptr<Character> character) {
    characters.push_back(std::move(character));
}

// Removes the character with the specified name
void Room::removeCharacter(const std::string &characterName) {
    characters.erase(std::remove_if(characters.begin(), characters.end(),
                [&characterName](const std::shared_ptr<Character>& character) { return character->getName() == characterName; }),
                characters.end());
}

// Returns the character with the specified name
std::shared_ptr<Character> Room::getCharacter(const std::string &characterName) {
    auto it = std::find_if(characters.begin(), characters.end(),
                [&characterName](const std::shared_ptr<Character>& character) { return character->getName() == characterName; });
    return it != characters.end() ? *it : nullptr;
}

// Returns the vector of characters
std::vector<std::shared_ptr<Character>> Room::getCharacters() const {
    return characters;
}

// Handles picking up the plant in the "south-of-house" room
void Room::pickUpPlant() {
    if (name == "south-of-house") {
        if (!plantMoved) {
            auto key = std::make_shared<Key>("key", "A small rusty key.", 1, 0); // Giá trị của key là 0G
            addItem(key);
            std::cout << "You move the plant and find a key underneath it.\n\n";
            plantMoved = true;
        } else {
            std::cout << "The plant has already been moved.\n";
        }
    } else {
        std::cout << "There is no plant to lift here.\n";
    }
}

// Returns whether the plant in the "south-of-house" room has been moved
bool Room::isPlantMoved() const{
    return plantMoved;
}

// Returns whether the room is locked
bool Room::isLocked() const {
    return locked;
}

// Initializes goblins in the "dark-cave" room
void Room::initializeGoblins() {
    addCharacter(std::make_shared<Enemy>("goblin", "A menacing goblin.", 100, 20));
    goblinsInitialized = true;
    std::cout << "A mob of many hostile goblins have appeared in the dark cave!\n\n";
}  

// Sets whether the room is locked
void Room::setLocked(bool locked) {
    this->locked = locked;
}
