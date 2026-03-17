#pragma once
#include "Atlas.h"
#include "tools.h"
#include <functional>
class Animation {
public:
    using SP = std::shared_ptr<Animation>;
    Animation() = default;
    ~Animation() = default;
public:
    void Reset();
    void SetAtlas(Atlas::SP &atlas);
    void SetLoop(bool flag);
    void SetInterval(int ms);
    int GetIdxFrame();
    IMAGE* GetImage();
    bool CheckFinished();
public:
    bool GetSketch();
    void SetSketch(bool flag);
    bool GetCool();
    bool GetTrap();
    void SetCool(bool flag);
    void SetTrap(bool flag);
public:
    void Update(int delta);
    void Draw(int x, int y)const;
    void SetCallback(std::function<void()>callback);
private:
    bool isCool = false;
    bool isTrap = false;
    bool isSketch = false;
    int timer = 0;//计时器
    int interval = 60;//帧间隔
    int idx = 0;//帧索引
    bool isLoop = true;//是否循环
    Atlas::SP atlas = nullptr;
    std::function<void()>callback = nullptr;
};

