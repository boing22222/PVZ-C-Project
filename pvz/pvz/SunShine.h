#pragma once
#include "Object.h"
#include "Animation.h"
class SunShine :public Object {
public: 
    enum class SunStatus {
        SUNSHINE_COLLECT,
        SUNSHINE_DOWN,
        SUNSHINE_GROUND,
        SUNSHINE_PRODUCT
    };
    enum class SunType {
        Small,
        Normal,
        Big
    };
public:
    SunShine(SunType type);
    ~SunShine() override = default;

   
public:
    static  SunShine* creatSunShine(int x, int y,SunType type);//静态成员函数，用sunshine::名字调用
    void Collect() override;
public:
    int timer = 0;
    float t;
    float x1, y1, x2, y2, x3, y3, x4, y4;
    float curx, cury;
    float speed;
    SunStatus status;
    SunType type;
    Animation::SP action;
public:
    void Draw() override;
    void Update(int delta) override;
};

