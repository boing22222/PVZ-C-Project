#pragma once
#include "Plant.h"
class Squash :public Plant
{
public:
	Squash();
public:
	enum class SquashStatus {
		Normal,
		Aim,
		Attack
	};
public:
	void skills(int delta)override;
	void SetStatus(SquashStatus status);
	void Collide(Object* obj)override;
private:
	SquashStatus status;
	Object* temp;
	int temp_x;
};

