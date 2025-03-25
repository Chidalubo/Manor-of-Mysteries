#include "Room.hpp"
#include <iostream>
#include <algorithm>

// Constructor
Room::Room(const std::string& desc) : description(desc) {}

void Room::setChest(bool hasChest) {
    chest = hasChest;
}

bool Room::hasChest() const {
    return chest;
}
// Display the room's description and its contents
void Room::describe() const {
    // General room description
    std::cout << "You are in " << description << " The atmosphere is heavy with mystery. "
              << "A chill runs down your spine as you realize the room is locked.\n";

    // NPC interaction if present
    if (npc) {
        std::cout << npc->getName() << " whispers: '" << npc->getDialogue() << "'\n";
    }

    // Puzzle introduction
    if (puzzle && !puzzle->getIsSolved()) {
        std::cout << "The room feels mysterious and foreboding. To proceed, you must solve the following puzzle:\n"
                  << "Puzzle: '" << puzzle->getDescription() << "'\n";
    }

    // List items in the room
    if (!items.empty()) {
        std::cout << "Looking around, you notice the following items:\n";
        for (const auto& item : items) {
            std::cout << "- " << item->getName() << "\n";
        }
    }
}

// Add an item to the room
void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

// Remove an item from the room
void Room::removeItem(std::shared_ptr<Item> item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

// Find an item in the room by name
std::shared_ptr<Item> Room::findItem(const std::string& itemName) const {
    std::string normalizedInput = itemName;
    std::transform(normalizedInput.begin(), normalizedInput.end(), normalizedInput.begin(), ::tolower);

    for (const auto& item : items) {
        std::string normalizedItemName = item->getName();
        std::transform(normalizedItemName.begin(), normalizedItemName.end(), normalizedItemName.begin(), ::tolower);

        if (normalizedItemName == normalizedInput) {
            return item; // Found the item
        }
    }
    return nullptr; // Item not found
}

// Set the NPC in the room
void Room::setNPC(std::shared_ptr<NPC> npc) {
    this->npc = npc;
}

// Get the NPC in the room
std::shared_ptr<NPC> Room::getNPC() const {
    return npc;
}

// Set the puzzle in the room
void Room::setPuzzle(std::shared_ptr<Puzzle> puzzle) {
    this->puzzle = puzzle;
}

// Get the puzzle in the room
std::shared_ptr<Puzzle> Room::getPuzzle() const {
    return puzzle;
}

// Check if the puzzle in the room is solved
bool Room::isPuzzleSolved() const {
    return puzzle && puzzle->getIsSolved();
}

// Set an exit to another room
void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    exits[direction] = room;
}

// Get the room in the specified direction
std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    return (it != exits.end()) ? it->second : nullptr;
}

// Get the room's description
std::string Room::getDescription() const {
    return description;
}
void Room::addPuzzle(std::shared_ptr<Puzzle> puzzle) {
    puzzles.push_back(puzzle);
}

// Retrieve all puzzles in the room
std::vector<std::shared_ptr<Puzzle>> Room::getPuzzles() const {
    return puzzles;
}

// Check if all puzzles in the room are solved
bool Room::areAllPuzzlesSolved() const {
    return std::all_of(puzzles.begin(), puzzles.end(), [](const std::shared_ptr<Puzzle>& puzzle) {
        return puzzle->getIsSolved();
    });
}
