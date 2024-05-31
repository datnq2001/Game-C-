#include "Villager.h"
#include "Player.h"
#include "Item.h"
#include <iostream>

// Constructor for Villager, calls the base class Character constructor
Villager::Villager(const std::string &n, const std::string &d) : Character(n, d), questGiven(false), questCompleted(false) {}

// Definition of the interact method for Villager
void Villager::interact() {
    Player* player = Player::instance();

    // Check if the quest has been completed
    if (questCompleted) {
        std::cout << "The villager says: 'Thank you, brave hero! Our village is forever in your debt.'\n\n";
    } else if (!questGiven) {       // Check if the quest has been given
        std::cout << "The villager says: 'Dear visitor, Our village has been devastated by goblins residing in the dark cave to the west. They stole our sacred rice seeds, causing a famine. Please, defeat 3 goblins and retrieve the seeds to save us.\nReward: 150EXP and 400G.'\n\n";
        player->startQuest("Retrieve the Sacred Rice Seeds", 3, "goblin", 150, 400);    // Start the quest
        questGiven = true;
    } else if (questGiven && !questCompleted) {
        if (player->isQuestCompleted()) {        // Check if the player has completed the quest
            auto seeds = player->getItem("sacred-rice-seeds");
            if (seeds) {        // Check if the player has the seeds
                std::cout << "The villager says: 'You did it! You defeated the goblins and retrieved the sacred rice seeds. Here is your reward: 150EXP and 400G.'\n\n";
                player->addExperience(150);         // Reward the player with experience and gold
                player->addGold(400);
                player->completeQuest();
                player->removeItem("sacred-rice-seeds");     // Remove the seeds from the player's inventory
                questCompleted = true;
            } else {
                std::cout << "The villager says: 'You have defeated the goblins, but where are the seeds?'\n\n";
            }
        } else {
            std::cout << "The villager says: 'Please, defeat 3 goblins and retrieve the seeds to save us.\nReward: 150EXP and 400G.'\n\n";
        }
    }
}
