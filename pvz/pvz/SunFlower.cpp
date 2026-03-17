#include "SunFlower.h"
#include"GameScene.h"
#include"Singleton.h"
#include"SunShine.h"
SunFlower::SunFlower() {
    type = plantType::SunFlower;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetAtlas(atlas);
    this->action->SetLoop(true);
    this->action->SetInterval(75);
    this->sunSpeed = 8000;
}



void SunFlower::skills(int delta) {
    skillTime += delta;
    if (skillTime < sunSpeed) { return; }
    skillTime = 0;
    SunShine* a = SunShine::creatSunShine(x, y,SunShine::SunType::Normal);
    auto& vec = Singleton<GameScene>::instance()->getSunShineVec();
    vec.push_back(a);
}