#pragma once
#include "NPC.hpp"

class WhisperingVoice : public NPC {
public:
    WhisperingVoice();
    void interact() override;
};

class Ghost : public NPC {
private:
    bool scaredAway;

public:
    Ghost();
    void interact() override;
    void scareAway();
    bool isScaredAway() const;
};
