#pragma once
#include "Plant.h"
#include"Timer.h"
class Repeater :public Plant
{
public:
    Repeater();
public:

    void skills(int delta)override;
private:
    int creatSpeed;
    Timer timer;//两发子弹的时间差
};

