#pragma once
#include "Plant.h"
#include "Timer.h"
class Chomper :public Plant
{
public:
    Chomper();
public:
    enum class ChomperStatus {
        Normal,
        Attack,
        Digestion
    };//三种状态
public:
    void Collide(Object* obj)override;//接触判断
    void skills(int delta)override;
private:
    void SetStatus(ChomperStatus status);//状态切换
private:
    ChomperStatus status;//食人花状态
    Timer timer;//消化时定时器
    int damage;//伤害
    Object* temp;//临时僵尸对象指针
};

