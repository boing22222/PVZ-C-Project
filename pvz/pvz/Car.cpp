#include "Car.h"
Car::Car() {
    speed = 10;
    isRunning = false;
}

void Car::Update(int delta) {
    StaticObj::Update(delta);
    if (isRunning) {
        x += speed;
    }
    if (x > 950) {
        used = false;//出屏幕删掉
    }
}

void Car::Collide(Object* obj) {
    if (!obj->isCollide) { return; }
    if (CheckHitX(obj->x, x-25 ,20 )) {//检测到僵尸
        if (!isRunning) { isRunning = true; }//如果还没启动，就启动
        obj->used=false;
    }
}