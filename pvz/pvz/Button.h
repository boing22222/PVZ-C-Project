#pragma once
#include "Resource.h"
#include "tools.h"
#include <vector>
#include <functional>
class Button {
public:
    Button() = default;
    ~Button() = default;
public:
    void Reset();
    void SetRect(RECT rect);
    void SetImage(IMAGE* image1,IMAGE* image2 );
    void SetCallback(std::function<void()>callback);
    void ProcessEvent(const ExMessage& msg);
    void Draw();
private:
    bool CheckHit(int x, int y);
private:
    enum class Status {
        Idle,
        Push,
    };
private:
    RECT region;
    IMAGE* imgIdle;
    IMAGE* imgPush;
    Status status = Status::Idle;
    std::function<void()>callback;//触发回调函数
};