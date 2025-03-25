#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>
#include <string>
#include "Room.hpp"
#include "Item.hpp"

class Player {
private:
    std::shared_ptr<Room> currentRoom;
    std::vector<std::shared_ptr<Item>> inventory;
    bool hasTorchLit;

public:
    Player(std::shared_ptr<Room> startingRoom);

    void move(const std::string& direction);
    void pickUp(std::shared_ptr<Item> item);
    void dropItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> findItemInInventory(const std::string& itemName) const;
    const std::vector<std::shared_ptr<Item>>& getInventory() const;
    std::shared_ptr<Room> getCurrentRoom() const;

    void lightTorch();
    bool isTorchLit() const;
};

#endif // PLAYER_HPP


