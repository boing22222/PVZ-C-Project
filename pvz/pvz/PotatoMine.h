#pragma once
#include "Plant.h"
#include"Timer.h"
class PotatoMine :public Plant
{
public:
    PotatoMine();
public:
    enum class PotatoMineStatus {
        UnderGround,
        Normal,
        Boom
    };//三种状态
public:
    void skills(int delta)override;
    void Draw()override;
    void Collide(Object* obj)override;
private:
    Timer timer;//从地底钻出和爆炸动画持续时间定时器
    PotatoMineStatus status;//土豆地雷状态
    int damage;
};

