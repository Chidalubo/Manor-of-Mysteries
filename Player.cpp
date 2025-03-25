#include "Player.hpp"
#include <iostream>
#include <algorithm>

Player::Player(std::shared_ptr<Room> startingRoom) 
    : currentRoom(startingRoom), hasTorchLit(false) {}

// Move the player to a new room in the specified direction
void Player::move(const std::string& direction) {
    auto room = currentRoom->getExit(direction);
    if (room) {
        if (currentRoom->isPuzzleSolved()) { // Ensure the puzzle is solved before moving
            currentRoom = room;
            currentRoom->describe();
        } else {
            std::cout << "You must solve the puzzle here before you can move.\n";
        }
    } else {
        std::cout << "There is no exit in that direction.\n";
    }
}

// Add an item to the player's inventory
void Player::pickUp(std::shared_ptr<Item> item) {
    if (item) {
        inventory.push_back(item);
        std::cout << item->getName() << " has been added to your inventory.\n";
    } else {
        std::cout << "You cannot pick that up.\n";
    }
}


// Drop an item from the player's inventory
void Player::dropItem(std::shared_ptr<Item> item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
    std::cout << item->getName() << " has been removed from your inventory.\n";
}

// Find an item in the player's inventory by name (case-insensitive)
std::shared_ptr<Item> Player::findItemInInventory(const std::string& itemName) const {
    std::string normalizedItemName = itemName;
    std::transform(normalizedItemName.begin(), normalizedItemName.end(), normalizedItemName.begin(), ::tolower);

    for (const auto& item : inventory) {
        std::string normalizedStoredName = item->getName();
        std::transform(normalizedStoredName.begin(), normalizedStoredName.end(), normalizedStoredName.begin(), ::tolower);

        if (normalizedStoredName == normalizedItemName) {
            return item;
        }
    }
    return nullptr; // Return nullptr if no match is found
}

// Get the player's current inventory
const std::vector<std::shared_ptr<Item>>& Player::getInventory() const {
    return inventory;
}

// Get the player's current room
std::shared_ptr<Room> Player::getCurrentRoom() const {
    return currentRoom;
}

// Light the torch and set its state to lit
void Player::lightTorch() {
    hasTorchLit = true;
    std::cout << "The torch is now lit. It flickers, illuminating the darkness.\n";
}

// Check if the torch is currently lit
bool Player::isTorchLit() const {
    return hasTorchLit;
}
