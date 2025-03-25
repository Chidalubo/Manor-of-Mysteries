#include "Puzzle.hpp"
#include <algorithm>

Puzzle::Puzzle(const std::string& description, const std::string& solution)
    : description(description), solution(solution), isSolved(false) {}

std::string Puzzle::getDescription() const {
    return description;
}

bool Puzzle::attemptSolution(const std::string& playerInput) {
    std::string normalizedInput = playerInput;
    std::transform(normalizedInput.begin(), normalizedInput.end(), normalizedInput.begin(), ::tolower);
    if (normalizedInput == solution) {
        isSolved = true;
        return true;
    }
    return false;
}

bool Puzzle::getIsSolved() const {
    return isSolved;
}
