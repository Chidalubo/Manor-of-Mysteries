#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>

class Puzzle {
private:
    std::string description;
    std::string solution;
    bool isSolved;

public:
    Puzzle(const std::string& description, const std::string& solution);

    std::string getDescription() const;
    bool attemptSolution(const std::string& playerInput);
    bool getIsSolved() const;
};

#endif // PUZZLE_HPP
