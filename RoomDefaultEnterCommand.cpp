#include "RoomDefaultEnterCommand.h"

// Definition of the execute method for RoomDefaultEnterCommand
void RoomDefaultEnterCommand::execute() {
    std::cout << gameObject->getDescription() << "\n";
}