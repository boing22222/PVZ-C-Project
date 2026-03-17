#pragma once
#include "Plant.h"
class PuffShroom :public Plant
{
public:
	PuffShroom();
public:
	void skills(int delta)override;
private:
	int creatSpeed;//子弹生成速度
};

