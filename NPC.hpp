#ifndef NPC_HPP
#define NPC_HPP

#include <string>

class NPC {
protected:
    std::string name;
    std::string dialogue;

public:
    NPC(const std::string& name, const std::string& dialogue);
    virtual ~NPC() = default;

    virtual void interact() = 0;

    std::string getName() const { return name; }
    std::string getDialogue() const { return dialogue; }
};

#endif // NPC_HPP


