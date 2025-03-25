#include "ConcreteNPCS.hpp"
#include <iostream>

// Whispering Voice Implementation
WhisperingVoice::WhisperingVoice()
    : NPC("A faint voice", "Focus on the air, and the answer will come to you.") {}

void WhisperingVoice::interact() {
    std::cout << dialogue << std::endl;
}

// Ghost Implementation
Ghost::Ghost()
    : NPC("Ghost", "The ghost looms before you, blocking your path."), scaredAway(false) {}

void Ghost::interact() {
    if (scaredAway) {
        std::cout << "The ghost has already been scared away. The room feels calm now.\n";
    } else {
        std::cout << dialogue << std::endl;
    }
}

void Ghost::scareAway() {
    scaredAway = true;
    std::cout << "The ghost shrieks and vanishes into the ether as the torch flickers brightly.\n";
}

bool Ghost::isScaredAway() const {
    return scaredAway;
}
