#pragma once
#include "Plant.h"
class ScaredyShroom :public Plant
{
public:
	ScaredyShroom();
public:
	enum class ScaredyStatus {
		Normal,
		Scaredy
	};
public:
	void skills(int delta)override;
	void SetStatus(ScaredyStatus status);
	void CheckZombie();
private:
	ScaredyStatus status;
	int creatSpeed;
};

