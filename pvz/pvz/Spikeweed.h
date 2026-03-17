#pragma once
#include "Plant.h"
class Spikeweed : public Plant
{
public:
	Spikeweed();
public:
	void skills(int delta)override;
private:
	int damage;
	int attackSpeed;
};

