#pragma once
#include <iostream>
#include <memory>
#pragma comment(lib, "winmm.lib")
class Object {
public:
    Object() = default;
    virtual ~Object() = default;
public:
    void SetName(const std::string& cName);//设置类名
    std::string GetName();//获取类名
public:
    virtual void Draw() {};//绘图
    virtual void Update(int delta) {};//更新
    virtual void Collide(Object* obj) {};//碰撞
    virtual void SetEffect(int type) {};//设置特效
    virtual void Collect() {};//收集
public:
    int value;
    int row, col;//目标所在行列信息
    int x{}, y{};//坐标
    int dx = 0, dy = 0;//坐标偏移量
    int blood = 400;//血量
    bool used = true;//是否能被回收内存
    bool isCollide = true;//是否能被碰撞检测
public:
    std::string className;//类名
    int id;
};
