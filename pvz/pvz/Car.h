#pragma once
#include "StaticObj.h"


class Car :public StaticObj {
public:
    Car();
    ~Car() override = default;
public:
    void Update(int delta) override;
    void Collide(Object* obj) override;
private:
    bool isRunning;
    int speed;
};

