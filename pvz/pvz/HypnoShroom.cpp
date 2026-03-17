#include "HypnoShroom.h"
#include"Resource.h"
#include"Singleton.h"
#include"SceneManager.h"
#include"GameScene.h"
HypnoShroom::HypnoShroom() {
    type = plantType::HypnoShroom;
    if (Singleton<SceneManager>::instance()->currentLevel->isDay) {
        Atlas::SP atlas = std::make_shared<Atlas>(hypnoShroomSleep);
        this->action->SetAtlas(atlas);
    }
    else {
        Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
        this->action->SetAtlas(atlas);
    }
    this->action->SetLoop(true);
    this->action->SetInterval(75);
}
void HypnoShroom::skills(int delta) {
    if (Singleton<SceneManager>::instance()->currentLevel->isDay)return;
    auto& v = Singleton<GameScene>::instance()->getZombies(row);
    auto& h = Singleton<GameScene>::instance()->getHypnoZombies(row);
    for (auto z : v) {
        if (CheckHitX(z->x, this->x - 50, 30) && z->isCollide){
            this->used = false;
            std::swap(z, v.back());
            v.pop_back();
            h.push_back(z);
            z->SetEffect(2);
        }
    }
}