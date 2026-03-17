#pragma once
#include "Object.h"
#include "tools.h"

class StaticObj :public Object {//静态对象,只要draw
public:
    StaticObj() = default;
    ~StaticObj() override = default;
    void SetImage(IMAGE* img);
public:
    void Draw() override;
    void Update(int delta) override;
public:
    bool isDraw = true;
private:
    IMAGE* img;
};
