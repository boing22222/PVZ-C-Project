#pragma once
#include "Plant.h"
class Jalapeno :public Plant
{
public:
	Jalapeno();
public:
    void skills(int delta)override;
private:
    void Boom();
private:
    int damage;
};

