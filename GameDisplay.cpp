#include "GameDisplay.hpp"
#include <iostream>

void GameDisplay::displayWelcomeMessage() {
    std::cout << "Welcome to Haunted Manor Adventure!\n";
    std::cout << "Explore the mysterious manor, solve puzzles, and restore its glory.\n\n";
}

void GameDisplay::displayGoodbyeMessage() {
    std::cout << "Thank you for playing! Goodbye!\n";
}

void GameDisplay::displayWinMessage() {
    std::cout << "Congratulations! You have saved the manor and banished the darkness!\n";
}
