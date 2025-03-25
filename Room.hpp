#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Item.hpp"
#include "NPC.hpp"
#include "Puzzle.hpp"

class Room {
public:
    Room(const std::string& description);

    void describe() const;
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> findItem(const std::string& itemName) const;

    void setNPC(std::shared_ptr<NPC> npc);
    std::shared_ptr<NPC> getNPC() const;

    void setPuzzle(std::shared_ptr<Puzzle> puzzle);
    std::shared_ptr<Puzzle> getPuzzle() const;
    bool isPuzzleSolved() const;

    void setExit(const std::string& direction, std::shared_ptr<Room> room);
    std::shared_ptr<Room> getExit(const std::string& direction) const;

    void setChest(bool hasChest);
    bool hasChest() const;

    std::string getDescription() const;
       void addPuzzle(std::shared_ptr<Puzzle> puzzle);
    std::vector<std::shared_ptr<Puzzle>> getPuzzles() const;
    bool areAllPuzzlesSolved() const;

private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::unordered_map<std::string, std::shared_ptr<Room>> exits;
    std::shared_ptr<NPC> npc;
    std::shared_ptr<Puzzle> puzzle;
    bool chest; // Indicates if the room has a chest
     std::vector<std::shared_ptr<Puzzle>> puzzles;
};
