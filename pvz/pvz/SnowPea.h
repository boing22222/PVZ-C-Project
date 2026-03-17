#pragma once
#include "Plant.h"
class SnowPea :public Plant
{
public:
    SnowPea();
public:
    void skills(int delta)override;
private:
    int creatSpeed;
};

