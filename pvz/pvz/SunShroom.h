#pragma once
#include "Plant.h"
#include"Timer.h"
class SunShroom : public Plant
{
public:
    SunShroom();
    enum class SunShroomStatus {
        Small,
        Big
    };
public:
    void skills(int delta)override;
private:
    SunShroomStatus status;
    int sunSpeed;
    Timer growTimer;
};

