#pragma once
#include "Object.h"
#include "Animation.h"
#include "Timer.h"
class Zombie :public Object {//僵尸基类
public:
    Zombie();
    ~Zombie() override = default;
public:
    enum class ZombieType {//僵尸类型
        NormalZombie,
        RoadBlockZombie,
        BucketZombie,
    };
    enum class ZombieStatus {//僵尸状态
        Walking,
        Attack,
        FallDown,
        Ash,
        None
    };
public:
    void Update(int delta) override;
    void Draw() override;
    void Collide(Object* obj) override;
    void SetEffect(int type) override;
public:
    void SetStatus(ZombieStatus status);//设置状态
    virtual ZombieType GetType() { return type; }
protected:
    int isArmor;//是否有防具
    Timer cool;//冰冻效果和打击效果定时器
    Timer freeze;
    Timer sketch;
    int speed;//移动速度
    int timer;//控制僵尸整体刷新帧率
    int damage;//伤害
    int count = 0;//出伤间隔
    ZombieStatus status;//状态
    ZombieType type = ZombieType::NormalZombie;
    Animation::SP action;//动画
 

    std::vector<Atlas::SP> atlas;//动画所需图集数组
};