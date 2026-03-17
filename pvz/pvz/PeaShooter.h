#pragma once
#include "Plant.h"
class PeaShooter :public Plant
{
public:
    PeaShooter();
public:
    
    void skills(int delta)override;
private:
    int creatSpeed;//子弹生成速度
};

