#include "Room.h"
#include "NullPassage.h"
#include "RoomDefaultEnterCommand.h"
#include "Key.h"

Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

void Room::removeItem(const std::string &itemName) {
    items.erase(std::remove_if(items.begin(), items.end(),
                [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; }),
                items.end());
}

std::shared_ptr<Item> Room::getItem(const std::string &itemName) {
    auto it = std::find_if(items.begin(), items.end(),
                [&itemName](const std::shared_ptr<Item>& item) { return item->getName() == itemName; });
    return it != items.end() ? *it : nullptr;
}

std::shared_ptr<Item> Room::retrieveItem(const std::string &itemName) {
    auto item = getItem(itemName);
    if (item) {
        removeItem(itemName);
    }
    return item;
}

void Room::addCharacter(std::shared_ptr<Character> character) {
    characters.push_back(std::move(character));
}

void Room::removeCharacter(const std::string &characterName) {
    characters.erase(std::remove_if(characters.begin(), characters.end(),
                [&characterName](const std::shared_ptr<Character>& character) { return character->getName() == characterName; }),
                characters.end());
}

std::shared_ptr<Character> Room::getCharacter(const std::string &characterName) {
    auto it = std::find_if(characters.begin(), characters.end(),
                [&characterName](const std::shared_ptr<Character>& character) { return character->getName() == characterName; });
    return it != characters.end() ? *it : nullptr;
}

void Room::pickUpPlant() {
    if (!plantMoved) {
        auto key = std::make_shared<Key>("key", "A small rusty key.");
        addItem(key);
        std::cout << "You move the plant and find a key underneath it.\n";
        plantMoved = true;
    } else {
        std::cout << "The plant has already been moved.\n";
    }
}

bool Room::isLocked() const {
    return locked;
}

void Room::setLocked(bool locked) {
    this->locked = locked;
}
