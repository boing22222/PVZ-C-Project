#pragma once
#include <functional>
#include <memory>

class Timer {
public:
    using SP = std::shared_ptr<Timer>;
    Timer() = default;
    ~Timer() = default;
public:
    void Restart();//重启
    void SetWaitTime(int val);//设置触发时间
    void SetOneTrigger(bool flag);//是否只触发一次
    void SetCallback(std::function<void()>callback);//回调
    void Pause();//暂停
    void Resume();//继续
    void Update(int delta);//如果不在暂停，更新计时，触发回调
    bool IsTrigger();
    bool isRunning=false;//是否在运行
private:
    int passTime = 0;//已过时间
    int waitTime = 0;//等待时间
    bool isPaused = false;//是否暂停
    bool isTrigger = false;//是否触发
    bool isOneTrigger = false;//是否单次触发
    std::function<void()>callback;//触发回调函数
};
