#pragma once
#include "Plant.h"
class WallNut : public Plant
{
public:
    WallNut();
public:
    enum class WallNutStatus {
        Normal,
        Injured,
        NearDeath
    };
public:
    void skills(int delta)override;
private:
    void SetStatus(WallNutStatus status);
private:
    WallNutStatus status;
};

