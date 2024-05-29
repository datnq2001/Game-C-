#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>
#include <vector>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    void addItem(std::shared_ptr<Item>);

    void removeItem(const std::string&);

    std::shared_ptr<Item> getItem(const std::string&);

    std::shared_ptr<Item> retrieveItem(const std::string&);

    void addCharacter(std::shared_ptr<Character>);

    void removeCharacter(const std::string&);

    std::shared_ptr<Character> getCharacter(const std::string&);

    std::vector<std::shared_ptr<Character>> getCharacters() const;

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &);

    void pickUpPlant();

    bool isPlantMoved() const;

    bool isLocked() const;
    void setLocked(bool locked);
    void initializeGoblins();
    int getGoblinCount() const;

protected:
    std::vector<std::shared_ptr<Item>> items;
    std::vector<std::shared_ptr<Character>> characters;
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    bool plantMoved = false;
    bool locked = false;  // Cờ để xác định phòng có bị khóa hay không
    bool goblinsInitialized = false;
};

#endif //ZOORK_ROOM_H
