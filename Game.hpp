#pragma once
#include "Player.hpp"
#include "Room.hpp"
#include <memory>
#include <string>

class Game {
public:
    Game();
    ~Game();
    void start();

private:
    void setupGame();
    void displayInstructions() const;
    void processCommand(const std::string& command);
    bool checkWinCondition() const;

    std::shared_ptr<Player> player;
    bool isGameOver;
};
