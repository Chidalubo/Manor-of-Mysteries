#include "ConcreteItems.hpp"
#include <iostream>

// Torch Implementation
Torch::Torch() {
    name = "Torch";
    description = "A small torch that lights the way.";
}

void Torch::use() {
    std::cout << "The torch flickers and lights the room.\n";
}

// Amulet Implementation
Amulet::Amulet() {
    name = "Amulet";
    description = "The amulet glows with a mysterious power.";
}

void Amulet::use() {
    std::cout << "The amulet pulses with energy, dispelling darkness.\n";
}

// Key Implementation
Key::Key() {
    name = "Key";
    description = "A small, ornate key. It looks like it fits a chest.";
}

void Key::use() {
    std::cout << "You use the key.\n";
}

