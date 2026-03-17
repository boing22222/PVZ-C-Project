#pragma once
#include "Zombie.h"
class RoadBlockZombie : public Zombie {
public:
    RoadBlockZombie();
    ~RoadBlockZombie() override = default;
public:
    void Update(int delta) override;
};



