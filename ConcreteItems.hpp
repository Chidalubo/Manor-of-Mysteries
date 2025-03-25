#ifndef CONCRETEITEMS_HPP
#define CONCRETEITEMS_HPP

#include "Item.hpp"

class Torch : public Item {
public:
    Torch();
    void use() override;
};

class Amulet : public Item {
public:
    Amulet();
    void use() override;
};

class Key : public Item {
public:
    Key();
    void use() override;
};

#endif // CONCRETEITEMS_HPP



