#include "ZOOrkEngine.h"
#include "Mushroom.h"
#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start, std::shared_ptr<Room> magic_forest)
    : startRoom(start), magicForest(magic_forest) {
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
        } else if (command == "open") {
            handleOpenCommand(arguments);
        } else if (command == "interact") {
            handleInteractCommand(arguments);
        } else if (command == "feed") {
            handleFeedCommand(arguments);
        } else if (command == "climb") {
            handleClimbCommand(arguments);
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

    if (currentRoom->getName() == "magic-forest" && direction != "east" && direction != "west") {
        std::cout << "It is impossible to go " << direction << "!\n";
        return;
    }

    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    // Kiểm tra xem người chơi có chỉ định tên vật phẩm không
    if (!arguments.empty()) {
        std::string itemName = arguments[0];
        // Kiểm tra vật phẩm trong phòng
        auto item = currentRoom->getItem(itemName);
        if (item) {
            std::cout << item->getDescription() << "\n";
            return;
        }
        // Kiểm tra vật phẩm trong inventory của người chơi
        item = player->getItem(itemName);
        if (item) {
            std::cout << item->getDescription() << "\n";
            return;
        }
        std::cout << "There is no " << itemName << " here.\n";
        return;
    }

    // Kiểm tra các cảnh vật đặc biệt trước khi hiển thị mô tả phòng
    if (currentRoom->getName() == "south-of-house" && !plantMoved && !keyTaken) {
        std::cout << "There is a pot of plant here.\n";
        return;
    }
    else if(currentRoom->getName() == "south-of-house" && plantMoved && !keyTaken){
        std::cout << "There is a key here.\n";
        return;
    }
    
    if(currentRoom->getName() == "ancient-tree" && climbTree && !mushroomTaken){
        std::cout << "There is a bunch of mushroom.\n";
        mushroomFound = true;
        return;
    }if(currentRoom->getName() == "ancient-tree" && climbTree && mushroomTaken){
        std::cout << "You are on the tree\n";
        mushroomFound = true;
        return;
    }

    if (currentRoom->getName() == "magic-forest" && !deerFound) {
        std::cout << "Suddenly you hear a rustling sound near a bush nearby. It seems like something is there.\n";
        deerFound = true;
        return;
    }

    if (currentRoom->getName() == "magic-forest" && deerFound && !mushroomFound) {
        std::cout << "You see a wounded deer lying near the bush. It looks like it needs help.\n";
        return;
    }

    // Hiển thị mô tả phòng hiện tại
    std::cout << currentRoom->getDescription() << "\n";

    // // Hiển thị mô tả của các nhân vật trong phòng
    // auto characters = currentRoom->getCharacters();
    // if (!characters.empty()) {
    //     std::cout << "You see the following characters:\n";
    //     for (const auto& character : characters) {
    //         std::cout << "- " << character->getName() << ": " << character->getDescription() << "\n";
    //     }
    // }
}


void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    std::string itemName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();

    // Đặc biệt xử lý nếu người chơi đang ở ancient-tree và muốn lấy nấm
    if (currentRoom->getName() == "ancient-tree" && itemName == "mushroom") {
        std::cout << "You take the healing mushroom from the ancient tree.\n";
        auto mushroom = std::make_shared<Mushroom>("mushroom", "A mushroom with healing properties.", 1, 3);
        player->addItem(mushroom);
        mushroomTaken = true;
        return;
    }

    // Retrieve item from the room and add to the player's inventory
    auto item = currentRoom->retrieveItem(arguments[0]);
    if (item) {
        player->addItem(item);
        std::cout << "You take the " << item->getName() << ".\n";
        if (itemName == "key") {
            keyTaken = true; // Đánh dấu key đã được lấy
        }
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
            std::cout << "You use the key to unlock the door.\n";
            currentRoom->setLocked(false); // Mở khóa cửa
            item->decreaseQuantity();
            if (item->getQuantity() <= 0) {
                player->removeItem(itemName);
            }
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
        plantMoved = currentRoom->isPlantMoved();
    } else {
        std::cout << "You can't lift that.\n";
    }
}

void ZOOrkEngine::handleOpenCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Open what?\n";
        return;
    }

    if (arguments[0] == "door") {
        Room* currentRoom = player->getCurrentRoom();
        if (currentRoom->getName() == "start-room" && !currentRoom->isLocked()) {
            std::cout << "A blinding light engulfs you as you step through the door...\n";
            player->setCurrentRoom(magicForest.get());
            std::cout << "You wake up in a new world.\n";
        } else {
            std::cout << "The door is locked. You need to unlock it first.\n";
        }
    } else {
        std::cout << "You can't open that.\n";
    }
}

void ZOOrkEngine::handleInteractCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Interact with whom?\n";
        return;
    }

    player->interactWithCharacter(arguments[0]);
}

void ZOOrkEngine::handleFeedCommand(std::vector<std::string> arguments) {
    if (arguments.size() < 3 || arguments[1] != "to") {
        std::cout << "Feed what to whom?\n";
        return;
    }

    std::string itemName = arguments[0];
    std::string characterName = arguments[2];
    auto item = player->getItem(itemName);
    if (!item) {
        std::cout << "You don't have " << itemName << ".\n";
        return;
    }

    auto character = player->getCurrentRoom()->getCharacter(characterName);
    if (character && itemName == "mushroom") {
        std::cout << "You feed the healing mushroom to the wounded deer.\n";
        player->removeItem(itemName);
        mushroomFound = false; // Reset trạng thái tìm nấm
        std::cout << "The deer recovers and thanks you. It gives you a fairy flower as a token of gratitude.\n";
        auto fairyFlower = std::make_shared<Item>("fairy-flower", "A beautiful flower given by the deer.");
        player->addItem(fairyFlower);
    } else {
        std::cout << "You can't feed that.\n";
    }
}

void ZOOrkEngine::handleClimbCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();
    if (currentRoom->getName() == "ancient-tree") {
        std::cout << "You climb up the ancient tree. \n";
        climbTree = true;
    } else {
        std::cout << "You can't climb here.\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || (quitStr == "yes")) {
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
