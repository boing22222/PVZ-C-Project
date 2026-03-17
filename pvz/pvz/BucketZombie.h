#pragma once
#include "Zombie.h"
class BucketZombie :public Zombie {
public:
    BucketZombie();
    ~BucketZombie() override = default;
public:
    void Update(int delta) override;
};
