#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Key.h"
#include "Enemy.h"
#include "Merchant.h"
#include "Villager.h"
#include "WoundedDeer.h"
#include "FairyFlower.h"
#include "OtherLegendaryCharacters.h"
#include "Door.h" 

int main() {
    // Initial rooms
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                           "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                    "You are facing the south side of a white house. There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                  "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    std::shared_ptr<Room> magic_forest = std::make_shared<Room>("magic-forest",
                                  "You find yourself in a magic forest filled with glowing plants and strange creatures. This is where your journey as a hero begins.\n");

    std::shared_ptr<Room> ancient_temple = std::make_shared<Room>("ancient-temple",
                                  "You stand before an ancient temple covered in moss and vines. Legends say it holds many secrets and ancient treasures.\n");

    std::shared_ptr<Room> dark_cave = std::make_shared<Room>("dark-cave",
                                  "You enter a dark cave. The air is thick and you can hear the distant sound of dripping water.\n");

    std::shared_ptr<Room> devastated_village = std::make_shared<Room>("devastated-village",
                                  "You walk into a devastated village. The houses are in ruins, and it feels like no one has lived here for a long time.\n");

    std::shared_ptr<Room> mystic_lake = std::make_shared<Room>("mystic-lake",
                                  "You arrive at a mystic lake. The water glows with a strange light, and you feel an unexplainable power emanating from it.\n");

    std::shared_ptr<Room> moonlit_grove = std::make_shared<Room>("tower-of-sorcery",
                                  "You stand before the tower of sorcery. It stretches high into the sky, and you can sense a powerful presence within.\n");

    std::shared_ptr<Room> dragon_lair = std::make_shared<Room>("dragon-lair",
                                  "You enter the lair of the dragon. The air is hot, and you can see the glint of treasure and the shadow of the dragon lurking in the darkness.\n");

    std::shared_ptr<Room> ancient_tree = std::make_shared<Room>("ancient-tree",
                                  "You stand before an ancient tree.\n");

    std::shared_ptr<Room> ancient_tree_top = std::make_shared<Room>("ancient-tree-top",
                                  "You are on top of the ancient tree. You can see the whole forest from here.\n");

    // Creating passages between rooms
    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", true);
    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);

    // Using Door instead of Passage for magic_forest and ancient_temple
    auto doorToAncientTemple = std::make_shared<Door>("door-to-ancient-temple", "A sturdy door blocking the way to the ancient temple.", magic_forest.get(), ancient_temple.get(), 2);
    magic_forest->addPassage("west", doorToAncientTemple);

    Passage::createBasicPassage(magic_forest.get(), ancient_tree.get(), "east", true);
    Passage::createBasicPassage(ancient_temple.get(), devastated_village.get(), "south", true);
    Passage::createBasicPassage(devastated_village.get(), dark_cave.get(), "west", true);
    Passage::createBasicPassage(dark_cave.get(), mystic_lake.get(), "north", true);
    Passage::createBasicPassage(mystic_lake.get(), moonlit_grove.get(), "west", true);
    Passage::createBasicPassage(moonlit_grove.get(), dragon_lair.get(), "north", true);

    // Add the passage from ancient_tree to ancient_tree_top
    Passage::createBasicPassage(ancient_tree.get(), ancient_tree_top.get(), "up", true);

    // Adding characters to rooms
    magic_forest->addCharacter(std::make_shared<WoundedDeer>("deer", "A deer that is severely wounded and lying on the ground."));
    ancient_temple->addCharacter(std::make_shared<Merchant>("merchant", "A merchant with various goods."));
    devastated_village->addCharacter(std::make_shared<Villager>("villager", "A lonely villager looking for help."));
    mystic_lake->addCharacter(std::make_shared<OtherLegendaryCharacters>("water-spirit", "A mystical water spirit that guards the lake."));
    moonlit_grove->addCharacter(std::make_shared<OtherLegendaryCharacters>("crystal-fairy", "A fairy with immense power that resides in the the moonlit grove."));
    dragon_lair->addCharacter(std::make_shared<OtherLegendaryCharacters>("ancient-dragon", "A legendary dragon that guards its treasure."));
    
    // Lock the start-room door initially
    start->setLocked(true);

    // Create the game engine and start the game
    ZOOrkEngine zoork(start, magic_forest);

    zoork.run();

    return 0;
}
