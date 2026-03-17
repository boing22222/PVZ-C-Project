#include "IceShroom.h"
#include "Resource.h"
#include "Singleton.h"
#include"GameScene.h"
#include "SceneManager.h"
IceShroom::IceShroom() {
    type = plantType::IceShroom;
    if (Singleton<SceneManager>::instance()->currentLevel->isDay) {
        Atlas::SP atlas = std::make_shared<Atlas>(iceShroomSleep);
        this->action->SetAtlas(atlas);
        this->action->SetLoop(true);
    }
    else {
        Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
        this->action->SetAtlas(atlas);
        this->action->SetLoop(false);
        this->action->SetCallback([this]() {
            Boom();//同樱桃炸弹
            action->Reset();
            Atlas::SP atlas = std::make_shared<Atlas>(iceShroomExplode);
            action->SetAtlas(atlas);
            action->SetCallback([this]() {
                used = false;
                });
            });
    }
    this->action->SetInterval(75);
}
void IceShroom::skills(int delta) {
    Plant::skills(delta);
}
void IceShroom::Boom() {//对全屏僵尸单位
    for (int row = 0; row < 5; row++) {
        auto& v = Singleton<GameScene>::instance()->getZombies(row);
        for (auto& a : v) {
                a->blood -= 40;
                a->SetEffect(3);//trap效果
        }
    }
}