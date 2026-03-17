#pragma once
#include "Plant.h"
class ThreePeater :public Plant
{
public:
	ThreePeater();
public:
	void skills(int delta)override;
private:
	int creatSpeed;
};

