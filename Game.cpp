#include "Game.hpp"
#include "ConcreteItems.hpp"
#include "ConcreteNPCS.hpp"
#include <iostream>
#include <algorithm>

Game::Game() : isGameOver(false) {
    setupGame();
}

Game::~Game() = default;

void Game::setupGame() {
    // Create items
    auto torch = std::make_shared<Torch>();
    auto keyItem = std::make_shared<Key>();
    auto amulet = std::make_shared<Amulet>();

    // Create rooms
    auto foyer = std::make_shared<Room>("A dimly lit foyer. The room feels locked and mysterious.");
    auto library = std::make_shared<Room>("a grand library filled with dusty books.");
    auto basement = std::make_shared<Room>("You are in a damp, dark basement. The air is heavy, and you sense danger. "
                                       "You must scare the ghost, or you will be possessed.");

    // Add items to rooms
    foyer->addItem(torch);
    library->addItem(keyItem);

    // Other setup remains unchanged

    // Add puzzles to rooms
    auto foyerPuzzle = std::make_shared<Puzzle>(
        "Riddle: I'm light as a feather, yet the strongest man can't hold me for more than 5 minutes. What am I?",
        "breath");
    auto libraryPuzzle = std::make_shared<Puzzle>(
        "Three explorers set out on an adventure. The first carries 5 apples. The second carries twice as many oranges as the first has apples."
        "The third carries three times as many bananas as the first has apples. How many of each fruit do they carry",
        "5 10 15");
    auto basementPuzzle = std::make_shared<Puzzle>(
        "Riddle: The more of me you take, the more you leave behind. What am I?",
        "footsteps");
           // Add secondary puzzles
    auto foyerPuzzle2 = std::make_shared<Puzzle>(
        "Riddle: What has hands but cannot clap?",
        "clock");
    auto libraryPuzzle2 = std::make_shared<Puzzle>(
        "Riddle: The more you take, the more you leave behind. What am I?",
        "footsteps");


    foyer->setPuzzle(foyerPuzzle);
     foyer->addPuzzle(foyerPuzzle);
       foyer->addPuzzle(foyerPuzzle2);
    library->setPuzzle(libraryPuzzle);
       library->addPuzzle(libraryPuzzle);
        library->addPuzzle(libraryPuzzle2);
    basement->setPuzzle(basementPuzzle);
       basement->addPuzzle(basementPuzzle);

    // Set room exits
    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);

    // Set player's starting room
    player = std::make_shared<Player>(foyer);

    // Add the ghost to the basement transition
    auto ghost = std::make_shared<Ghost>();
    basement->setNPC(ghost);
}


void Game::displayInstructions() const {
    std::cout << "Welcome to Haunted Manor Adventure!\n"
              << "Your goal is to find the amulet and restore the manor.\n"
              << "Commands:\n"
              << "  look          - Look around the room.\n"
              << "  move <dir>    - Move in a direction (e.g., 'move north').\n"
              << "  take <item>   - Take an item in the room.\n"
              << "  drop <item>   - Drop an item from your inventory.\n"
              << "  use <item>    - Use an item in your inventory.\n"
              << "  solve         - Solve a puzzle in the room.\n"
              << "  inventory     - View your inventory.\n"
              << "  quit          - Exit the game.\n"
              << "  help          - Display the game instructions.\n";
}

void Game::start() {
    displayInstructions();

    while (!isGameOver) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);
        processCommand(command);

        if (checkWinCondition()) {
            std::cout << "The amulet glows brightly, banishing the darkness. You have restored the manor!\n";
            isGameOver = true;
        }
    }

    std::cout << "Thank you for playing! Goodbye!\n";
}

void Game::processCommand(const std::string& command) {
    auto currentRoom = player->getCurrentRoom();
    std::string action, argument;
    size_t spaceIndex = command.find(' ');

    if (spaceIndex != std::string::npos) {
        action = command.substr(0, spaceIndex); // Extract action (e.g., "take", "move")
        argument = command.substr(spaceIndex + 1); // Extract argument (e.g., "torch")
    } else {
        action = command; // Command without argument (e.g., "look", "inventory")
    }

    // Convert action and argument to lowercase for consistency
    std::transform(action.begin(), action.end(), action.begin(), ::tolower);
    std::transform(argument.begin(), argument.end(), argument.begin(), ::tolower);

    static int wrongAttempts = 0; // Counter for wrong puzzle attempts

    if (action == "look") {
        currentRoom->describe();
    } 
    else if (action == "move") {
        if (!argument.empty()) {
            auto nextRoom = currentRoom->getExit(argument);
            if (nextRoom) {
                if (!currentRoom->isPuzzleSolved()) {
                    std::cout << "The room is locked. Solve the puzzle first to proceed.\n";
                } else if (currentRoom->getNPC() && currentRoom->getNPC()->getName() == "Ghost") {
                    if (!player->findItemInInventory("torch")) {
                        std::cout << "The ghost looms before you. Without the torch, you are powerless. The ghost devours your soul. You have lost the game!\n";
                        isGameOver = true;
                        return;
                    }
                } else {
                    player->move(argument);
                    if (argument == "north" && currentRoom->getDescription().find("foyer") != std::string::npos) {
                        std::cout << "The Foyer is now unlocked. You can proceed to the North Wing.\n";
                    } else if (argument == "down" && currentRoom->getDescription().find("library") != std::string::npos) {
                        std::cout << "The Library's secrets are revealed. A dark abyss opens below...\n";
                    }
                }
            } else {
                std::cout << "There is no exit in that direction.\n";
            }
        } else {
            std::cout << "Specify a direction to move (e.g., 'move north').\n";
        }
    } 
    else if (action == "take") {
        if (!argument.empty()) {
            auto item = currentRoom->findItem(argument);
            if (item) {
                player->pickUp(item);
                currentRoom->removeItem(item);
                std::cout << "You picked up the " << item->getName() << ".\n";
            } else {
                std::cout << "There is no " << argument << " here.\n";
            }
        } else {
            std::cout << "Specify an item to take (e.g., 'take torch').\n";
        }
    } 
    else if (action == "drop") {
        if (!argument.empty()) {
            auto item = player->findItemInInventory(argument);
            if (item) {
                player->dropItem(item);
                currentRoom->addItem(item);
                std::cout << "You dropped the " << item->getName() << " in the room.\n";
            } else {
                std::cout << "You don't have " << argument << " in your inventory.\n";
            }
        } else {
            std::cout << "Specify an item to drop (e.g., 'drop torch').\n";
        }
    } 
    else if (action == "use") {
    if (!argument.empty()) {
        auto item = player->findItemInInventory(argument);
        if (item) {
            // Check if the player is trying to use the key in the basement
            if (argument == "key" && currentRoom->getDescription().find("basement") != std::string::npos) {
                // Ensure the puzzle in the basement is solved
                if (!currentRoom->isPuzzleSolved()) {
                    std::cout << "The chest is locked. You must solve the puzzle first.\n";
                    return;
                }
                // If the puzzle is solved, allow the key to be used
                std::cout << "You use the key and open the chest to reveal the Amulet of Truth!\n";
                std::cout << "The Amulet shines brightly, dispelling the darkness and restoring the manor!\n";
                player->pickUp(std::make_shared<Amulet>()); // Add the amulet to the player's inventory
                isGameOver = true; // End the game after winning
                std::cout << "Congratulations! You have won the game!\n";
                return;
            }

            // Handle other items being used
            item->use();
            // Additional logic for specific items like the torch
            if (argument == "torch" && currentRoom->getNPC() && currentRoom->getNPC()->getName() == "Ghost") {
                std::cout << "The torch flickers and lights the room.\n";
                std::cout << "The ghost screams and vanishes into the darkness. You are now safe.\n";
                currentRoom->setNPC(nullptr); // Remove the ghost
            } else if (argument == "key" && currentRoom->getDescription().find("basement") == std::string::npos) {
                std::cout << "Using the key has no effect here.\n";
            }
        } else {
            std::cout << "You don't have " << argument << " in your inventory.\n";
        }
    } else {
        std::cout << "Specify an item to use (e.g., 'use torch').\n";
    }
}
 
   else if (action == "solve") {
    auto puzzles = currentRoom->getPuzzles(); // Get all puzzles in the room
    bool hasUnsolvedPuzzle = false;

    // Iterate over puzzles and find the first unsolved one
    for (const auto& puzzle : puzzles) {
        if (!puzzle->getIsSolved()) {
            hasUnsolvedPuzzle = true;

            // Present the puzzle to the player
            std::cout << puzzle->getDescription() << "\nAnswer: ";
            std::string answer;
            std::getline(std::cin, answer);
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

            // Check the player's answer
            if (puzzle->attemptSolution(answer)) {
                std::cout << "You solved the puzzle!\n";

                // Check if all puzzles are solved
                if (currentRoom->areAllPuzzlesSolved()) {
                    std::cout << "All puzzles in this room are solved. You can now proceed to the next area.\n";
                }
            } else {
                wrongAttempts++;
                if (wrongAttempts >= 3) {
                    std::cout << "You have failed to solve the puzzle and lost the game!\n";
                    isGameOver = true;
                    return;
                } else {
                    std::cout << "That's not correct. You have " << (3 - wrongAttempts) << " attempt(s) left.\n";
                }
            }

            return; // Process only the first unsolved puzzle
        }
    }

    // If no unsolved puzzles remain
    if (!hasUnsolvedPuzzle) {
        std::cout << "There are no puzzles to solve here.\n";
    }
}



    else if (action == "inventory") {
        const auto& inventory = player->getInventory();
        if (inventory.empty()) {
            std::cout << "Your inventory is empty.\n";
        } else {
            std::cout << "Your inventory contains:\n";
            for (const auto& item : inventory) {
                std::cout << "- " << item->getName() << "\n";
            }
        }
    } 
    else if (action == "help") {
        displayInstructions();
    } 
    else if (action == "quit") {
        isGameOver = true;
    } 
    else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

bool Game::checkWinCondition() const {
     auto amulet = player->findItemInInventory("amulet");
    return amulet != nullptr;
}
