#pragma once
#include "Resource.h"
class Level
{
public:
	Level(bool day,bool trans,IMAGE* bg,int row,int z);
	~Level() = default;
public:
	int rows;
	bool isDay;
	bool hasTransmission;
	IMAGE* background;
	int zombieNumber;

};

