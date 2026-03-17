#pragma once
#include "Resource.h"
class Trophy {
public:
    int x, y;            // 奖杯当前位置
    int destX, destY;    // 奖杯目标位置
    int Vx, Vy;          // 水平和垂直速度
    int timer;           // 用于计时
    bool isActive;       // 奖杯是否正在运动
public:
    void InitTrophy();
    void put_trophy();
    void updateTrophy(int delta);
    void drawTrophy();
    bool pass_end_signal();
};
