#pragma once
#include "Plant.h"
class IceShroom :public Plant
{
public:
	IceShroom();
public:
	void skills(int delta)override;
	void Boom();
};

