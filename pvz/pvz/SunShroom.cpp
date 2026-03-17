#include "SunShroom.h"
#include "SunShine.h"
#include"Resource.h"
#include"SceneManager.h"
#include"Singleton.h"
#include"GameScene.h"
SunShroom::SunShroom() {
    type = plantType::SunShroom;
    status = SunShroomStatus::Small;
    if (Singleton<SceneManager>::instance()->currentLevel->isDay) {
        Atlas::SP atlas = std::make_shared<Atlas>(sunShroomSleep);
        this->action->SetAtlas(atlas);
        this->action->SetLoop(true);
        this->action->SetInterval(75);
        this->growTimer.Restart();
        this->growTimer.Pause();
        this->sunSpeed = 0;
    }
    else {
        Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
        this->action->SetAtlas(atlas);
        this->action->SetLoop(true);
        this->action->SetInterval(75);
        this->sunSpeed = 8000;
    }
    growTimer.Restart();
    growTimer.SetOneTrigger(true);
    growTimer.SetWaitTime(32000);
    growTimer.SetCallback([this]() {
        growTimer.Pause();
        status = SunShroomStatus::Big;
        Atlas::SP atlas = std::make_shared<Atlas>(sunShroomBig);
        this->action->SetAtlas(atlas);
        });
}
void SunShroom::skills(int delta) {
    if (Singleton<SceneManager>::instance()->currentLevel->isDay)return;
    growTimer.Update(delta);
    skillTime += delta;
    if (skillTime < sunSpeed) { return; }
    skillTime = 0;
    SunShine* a = SunShine::creatSunShine(x, y, status==SunShroomStatus::Small?SunShine::SunType::Small:SunShine::SunType::Big);
    auto& vec = Singleton<GameScene>::instance()->getSunShineVec();
    vec.push_back(a);
}