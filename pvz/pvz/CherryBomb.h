#pragma once
#include "Plant.h"
class CherryBomb :public Plant
{
public:
    CherryBomb();
public:
    void skills(int delta)override;
private:
    void Boom();//第一段动画结束后回调
private:
    int damage;
};

