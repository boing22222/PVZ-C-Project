#pragma once
#include "Plant.h"
class SunFlower :public Plant
{
public:
    SunFlower();
public:
    void skills(int delta)override;
private:
    int sunSpeed;
};

