#pragma once
#include "Animation.h"
#include "Object.h"

class Plant :public Object {//继承object
public:
    enum class plantType {//植物种类
        PeaShooter,
        SunFlower,
        WallNut,
        PotatoMine,
        CherryBomb,
        SnowPea,
        Chomper,
        Repeater,
        PuffShroom,
        SunShroom,
        ScaredyShroom, 
        IceShroom,
        Squash,
        Spikeweed,
        ThreePeater,
        Jalapeno,
        None,
    };
public:
    Plant();
    ~Plant() override = default;
    void Update(int delta) override;
    void Draw() override;
    virtual void skills(int delta) {};//持续触发的植物技能
public:
    plantType GetType();
protected:
    plantType type;//枚举类型
    Animation::SP action;//动画
    int skillTime;//技能冷却时间
};
