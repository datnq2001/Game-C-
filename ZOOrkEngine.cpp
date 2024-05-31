#include "ZOOrkEngine.h"
#include "Mushroom.h"
#include "Merchant.h"
#include "FairyFlower.h"
#include <utility>

// Constructor for ZOOrkEngine which initializes the start room and the magic forest
ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start, std::shared_ptr<Room> magic_forest)
    : startRoom(start), magicForest(magic_forest) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

// Method to run the game loop
void ZOOrkEngine::run() {
    while (!gameOver) {     // Game loop
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        // Handle different commands
        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "inventory") {
            handleInventoryCommand(arguments);
        } else if (command == "equipment") {
            handleEquipmentCommand(arguments);
        } else if (command == "use") {
            handleUseCommand(arguments);
        } else if (command == "unattach") {
            handleUnattachCommand(arguments);
        } else if (command == "lift") {
            handleLiftCommand(arguments);
        } else if (command == "open") {
            handleOpenCommand(arguments);
        } else if (command == "interact") {
            handleInteractCommand(arguments);
        } else if (command == "feed") {
            handleFeedCommand(arguments);
        } else if (command == "buy") {
            handleBuyCommand(arguments);
        } else if (command == "sell") {
            handleSellCommand(arguments);
        } else if (command == "attack") {
            handleAttackCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "check-info") {
            handleCheckInfoCommand(arguments);
        } else if (command == "quest-status") {
            handleQuestStatusCommand(arguments); 
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

// Method to handle the attack command
void ZOOrkEngine::handleAttackCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {     // Check if the player has specified a target
        std::cout << "Attack whom?\n";
        return;
    }

    auto targetName = arguments[0];
    auto target = player->getCurrentRoom()->getCharacter(targetName);  // Get the target character
    if (target) {   // If the target exists, attack it
        player->attackEnemy(target);
    } else {
        std::cout << "There is no " << targetName << " here.\n\n";
    }
}

// Method to handle the equipment command
void ZOOrkEngine::handleEquipmentCommand(std::vector<std::string> arguments) {
    player->listEquipment();
}

// Method to handle the unattach command
void ZOOrkEngine::handleUnattachCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Unattach what?\n";
        return;
    }
    player->unattachItem(arguments[0]);
}

// Method to handle the go command
void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Go where?\n\n";
        return;
    }

    std::string direction = arguments[0];   // Get the direction specified by the player
    Room* currentRoom = player->getCurrentRoom();     // Get the current room

    // Check if the player is in the magic forest and is trying to go in the wrong direction
    if (currentRoom->getName() == "magic-forest" && direction != "east" && direction != "west") {
        std::cout << "It is impossible to go " << direction << "!\n\n";
        return;
    }

    // Check if the player is in the ancient tree and is trying to go up
    if (currentRoom->getName() == "ancient-tree" && direction == "up") {
        if (!ancientTreeTop) {
            ancientTreeTop = std::make_shared<Room>("ancient-tree-top",
                            "You are on top of the ancient tree. You can see the whole forest from here.\n");
            Passage::createBasicPassage(currentRoom, ancientTreeTop.get(), "up", true);
        }
    }

    // Check if the player is in the ancient tree top and is trying to go down
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();     // Enter the passage
}

// Method to handle the look command
void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    // Check if the player is in the dark cave and initialize the goblins
    if (currentRoom->getName() == "dark-cave") {
        currentRoom->initializeGoblins();
        return;
    }

    // Check if the player is in the devastated village and initialize the villagers
    if (!arguments.empty()) {
        std::string itemName = arguments[0];
        auto item = currentRoom->getItem(itemName);
        if (item) {     // If the item exists, display its description
            std::cout << item->getDescription() << "\n\n";
            return;
        }
        item = player->getItem(itemName);
        if (item) {     // If the item exists in the player's inventory, display its description
            std::cout << item->getDescription() << "\n\n";
            return;
        }
        std::cout << "There is no " << itemName << " here.\n\n";
        return;
    }

    // Check if the player is in the start room and the door is locked
    if (currentRoom->getName() == "south-of-house" && !plantMoved && !keyTaken) {
        std::cout << "There is a pot of plant here.\n\n";
        return;
    } else if (currentRoom->getName() == "south-of-house" && plantMoved && !keyTaken) {
        std::cout << "There is a key here.\n\n";
        return;
    }

    // Check if the player is in the ancient tree top and the mushroom is not taken
    if (currentRoom->getName() == "ancient-tree-top" && !mushroomTaken) {
        std::cout << "There is a bunch of mushroom.\n\n";
        mushroomFound = true;
        return;
    } 
    if (currentRoom->getName() == "ancient-tree-top" && mushroomTaken) {
        std::cout << "You are on the tree\n\n";
        mushroomFound = true;
        return;
    }

    // Check if the player is in the magic forest and the deer is not found
    if (currentRoom->getName() == "magic-forest" && !deerFound) {
        std::cout << "Suddenly you hear a rustling sound near a bush nearby. It seems like something is there.\n\n";
        deerFound = true;
        return;
    }
    if (currentRoom->getName() == "magic-forest" && deerFound && !deerFeed) {
        std::cout << "You see a wounded deer lying near the bush. It looks like it needs help.\n\n";
        return;
    }

    // Check if the player is in the ancient temple and the merchant is not found
    if (currentRoom->getName() == "ancient-temple" || currentRoom->getName() == "dark-cave" || currentRoom->getName() == "devastated-village" || currentRoom->getName() == "mystic-lake" || currentRoom->getName() == "tower-of-sorcery" || currentRoom->getName() == "dragon-lair") {
        auto characters = currentRoom->getCharacters();
        if (!characters.empty()) {
            for (const auto& character : characters) {
                std::cout << "- " << character->getName() << ": " << character->getDescription() << "\n\n";
            }
        }
        return;
    }
    
    std::cout << currentRoom->getDescription() << "\n";

    
}

// Method to handle the take command
void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n\n";
        return;
    }
    
    std::string itemName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    
    if (itemName == "plant" || itemName == "pot" || itemName == "a pot of plant") {
        std::cout << "Invalid item: plant cannot be taken.\n\n";
        return;
    }
    
    // Check if the player is in the ancient tree top and the mushroom is not taken
    if (currentRoom->getName() == "ancient-tree-top" && itemName == "mushroom") {
        std::cout << "You take the healing mushroom from the ancient tree.\n\n";
        auto mushroom = std::make_shared<Mushroom>("mushroom", "A mushroom with healing properties.", 1, 3);
        player->addItem(mushroom);
        mushroomTaken = true;
        return;
    }

    auto item = currentRoom->retrieveItem(itemName);
    if (item) {
        player->addItem(item);
        std::cout << "You take the " << item->getName() << ".\n\n";
        if (itemName == "key") {  // Check if the player has taken the key
            keyTaken = true;
        }
    } else {
        std::cout << "There is no " << arguments[0] << " here.\n\n";
    }
}

// Method to handle the drop command
void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n\n";
        return;
    }

    auto item = player->retrieveItem(arguments[0]);
    if (item) {
        player->getCurrentRoom()->addItem(item);
        std::cout << "You drop the " << item->getName() << " (Quantity: " << item->getQuantity() << ").\n\n";
    } else {
        std::cout << "You don't have " << arguments[0] << ".\n\n";
    }
}

// Method to handle the inventory command
void ZOOrkEngine::handleInventoryCommand(std::vector<std::string> arguments) {
    player->listInventory();
}

// Method to handle the use command
void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Use what?\n\n";
        return;
    }

    auto itemName = arguments[0];
    auto item = player->getItem(itemName);
    if (!item) {
        std::cout << "You don't have " << itemName << ".\n\n";
        return;
    }

    if (itemName == "key") {
        Room* currentRoom = player->getCurrentRoom();
        if (currentRoom->getName() == "start-room" && currentRoom->isLocked()) {  // Check if the player is in the start room and the door is locked
            std::cout << "You use the key to unlock the door.\n\n";
            currentRoom->setLocked(false);  // Unlock the door
            item->decreaseQuantity();  // Decrease the quantity of the key
            if (item->getQuantity() <= 0) {  // Check if the key has been used up
                player->removeItem(itemName);   // Remove the key from the player's inventory
            }
        } else {
            std::cout << "You can't use the key here.\n\n";
        }
    } else {
        player->useItem(itemName);  // Use the item
    }
}

// Method to handle the lift command
void ZOOrkEngine::handleLiftCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Lift what?\n\n";
        return;
    }

    if (arguments[0] == "plant") {
        Room* currentRoom = player->getCurrentRoom();
        currentRoom->pickUpPlant();
        plantMoved = currentRoom->isPlantMoved();
    } else {
        std::cout << "You can't lift that.\n\n";
    }
}

// Method to handle the open command
void ZOOrkEngine::handleOpenCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Open what?\n\n";
        return;
    }

    if (arguments[0] == "door") {
        Room* currentRoom = player->getCurrentRoom();
        if (currentRoom->getName() == "start-room" && !currentRoom->isLocked()) {
            std::cout << "A blinding light engulfs you as you step through the door...\n";
            player->setCurrentRoom(magicForest.get());
            std::cout << "You wake up in a new world.\n\n";
        } else {
            std::cout << "The door is locked. You need to unlock it first.\n\n";
        }
    } else {
        std::cout << "You can't open that.\n\n";
    }
}

// Method to handle the interact command
void ZOOrkEngine::handleInteractCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Interact with whom?\n\n";
        return;
    }

    player->interactWithCharacter(arguments[0]);
}

// Method to handle the feed command
void ZOOrkEngine::handleFeedCommand(std::vector<std::string> arguments) {
    if (arguments.size() < 3 || arguments[1] != "to") {
        std::cout << "Feed what to whom?\n\n";
        return;
    }

    std::string itemName = arguments[0];
    std::string characterName = arguments[2];
    auto item = player->getItem(itemName);
    if (!item) {
        std::cout << "You don't have " << itemName << ".\n\n";
        return;
    }

    auto character = player->getCurrentRoom()->getCharacter(characterName);
    if (character && itemName == "mushroom") {
        std::cout << "You feed the healing mushroom to the wounded deer.\n";
        player->removeItem(itemName);
        mushroomFound = false;
        std::cout << "The deer recovers and thanks you.\nIt gives you a fairy flower as a token of gratitude.\n";
        player->addExperience(50);
        auto fairyFlower = std::make_shared<FairyFlower>("fairy-flower", "A beautiful flower given by the deer.", 1, 199);
        player->addItem(fairyFlower);

        player->getCurrentRoom()->removeCharacter(characterName);
        deerFeed = true;
    } else {
        std::cout << "You can't feed that.\n\n";
    }
}

// Method to handle the buy command
void ZOOrkEngine::handleBuyCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Buy what?\n\n";
        return;
    }

    std::string itemName = arguments[0];
    auto merchant = std::dynamic_pointer_cast<Merchant>(player->getCurrentRoom()->getCharacter("merchant"));
    if (merchant) {
        merchant->sellItem(itemName, player);
    } else {
        std::cout << "There is no merchant here.\n\n";
    }
}

// Method to handle the check-info command
void ZOOrkEngine::handleCheckInfoCommand(std::vector<std::string> arguments) {
    std::cout << "Gold: " << player->getGold() << " \n";
    std::cout << "HP: " << player->getHealth() << "\n";
    std::cout << "Attack: " << player->getAttack() << "\n";
    std::cout << "Level: " << player->getLevel() << "\n";
    std::cout << "EXP: " << player->getExperience() << " / " << player->getNextLevelExperience() << "\n\n";
}

// Method to handle the sell command
void ZOOrkEngine::handleSellCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Sell what?\n\n";
        return;
    }

    std::string itemName = arguments[0];
    auto merchant = std::dynamic_pointer_cast<Merchant>(player->getCurrentRoom()->getCharacter("merchant"));
    if (merchant) {
        merchant->buyItemFromPlayer(itemName, player);
    } else {
        std::cout << "There is no merchant here.\n\n";
    }
}

// Method to handle the quest-status command
void ZOOrkEngine::handleQuestStatusCommand(std::vector<std::string> arguments) {
    player->checkQuestStatus();
}

// Method to handle the quit command
void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || (quitStr == "yes")) {
        gameOver = true;
    }
}

// Method to tokenize a string
std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

// Method to convert a string to lowercase
std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
