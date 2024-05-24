#include "ZOOrkEngine.h"

#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

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
        } else if (command == "use") {
            handleUseCommand(arguments);
        } else if (command == "lift") {
            handleLiftCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Go where?\n";
        return;
    }

    std::string direction = arguments[0];

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();
    std::cout << currentRoom->getDescription() << "\n";
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    Room* currentRoom = player->getCurrentRoom();
    // Retrieve item from the room and add to the player's inventory
    auto item = currentRoom->retrieveItem(arguments[0]);
    if (item) {
        player->addItem(item);
        std::cout << "You take the " << item->getName() << ".\n";
    } else {
        std::cout << "There is no " << arguments[0] << " here.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }

    // Retrieve item from the player's inventory and add to the current room
    auto item = player->retrieveItem(arguments[0]);
    if (item) {
        player->getCurrentRoom()->addItem(item);
        std::cout << "You drop the " << item->getName() << ".\n";
    } else {
        std::cout << "You don't have " << arguments[0] << ".\n";
    }
}

void ZOOrkEngine::handleInventoryCommand(std::vector<std::string> arguments) {
    // Display the player's inventory
    player->listInventory();
}

void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Use what?\n";
        return;
    }

    auto itemName = arguments[0];
    auto item = player->getItem(itemName); // Kiểm tra xem người chơi có item trong inventory không
    if (!item) {
        std::cout << "You don't have " << itemName << ".\n";
        return;
    }

    if (itemName == "key") {
        Room* currentRoom = player->getCurrentRoom();
        if (currentRoom->getName() == "start-room" && currentRoom->isLocked()) {
            std::cout << "You use the key to open the door.\n";
            currentRoom->setLocked(false); // Mở khóa cửa
        } else {
            std::cout << "You can't use the key here.\n";
        }
    } else {
        // Use an item from the player's inventory
        player->useItem(itemName);
    }
}

void ZOOrkEngine::handleLiftCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Lift what?\n";
        return;
    }

    if (arguments[0] == "plant") {
        Room* currentRoom = player->getCurrentRoom();
        currentRoom->pickUpPlant();
    } else {
        std::cout << "You can't lift that.\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
