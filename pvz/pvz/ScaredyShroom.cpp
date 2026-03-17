#include "ScaredyShroom.h"
#include"GameScene.h"
#include"Resource.h"
#include"SceneManager.h"
#include"Singleton.h"
#include"Bullet.h"
ScaredyShroom::ScaredyShroom() {
    type = plantType::ScaredyShroom;
    status = ScaredyStatus::Normal;
    if (Singleton<SceneManager>::instance()->currentLevel->isDay) {
        Atlas::SP atlas = std::make_shared<Atlas>(scaredyShroomSleep);
        this->action->SetAtlas(atlas);
        this->action->SetLoop(true);
        this->action->SetInterval(75);
        this->creatSpeed = 0;
    }
    else {
        Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
        this->action->SetAtlas(atlas);
        this->action->SetLoop(true);
        this->action->SetInterval(75);
        this->creatSpeed = 2000;
    }
}
void ScaredyShroom::SetStatus(ScaredyStatus status)
{
    this->status = status;
    switch (status)
    {
    case ScaredyShroom::ScaredyStatus::Normal: {
        Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
        this->action->SetAtlas(atlas);
        break;
    }
    case ScaredyShroom::ScaredyStatus::Scaredy: {
        Atlas::SP atlas = std::make_shared<Atlas>(scaredyShroomCry);
        this->action->SetAtlas(atlas);
        break;
    }
    default:
        break;
    }
}
void ScaredyShroom::CheckZombie() {
    bool hasZ = false;
    for (int i = -1; i < 2; i++) {
        int row = this->row + i;
        if (row < 0 || row>4) { continue; }
        auto& v = Singleton<GameScene>::instance()->getZombies(row);
        for (auto& a : v) {
            if (a->col >= col - 1 && a->col <= col + 1) {
                hasZ = true;
                if (status == ScaredyStatus::Normal) {
                    SetStatus(ScaredyStatus::Scaredy);
                    return;
                }
            }
        }
    }
    if (!hasZ && status == ScaredyStatus::Scaredy)
        SetStatus(ScaredyStatus::Normal);
    
}
void ScaredyShroom::skills(int delta) {
    if (Singleton<SceneManager>::instance()->currentLevel->isDay)return;
    CheckZombie();
    if (status == ScaredyStatus::Scaredy)return;
    auto& v = Singleton<GameScene>::instance()->getZombies(row);
    if (v.empty()) { return; }
    skillTime += delta;
    if (skillTime < creatSpeed) { return; }
    skillTime = 0;
    auto* a = new Bullet(Bullet::BulletType::Puff);
    a->row = row;
    a->x = x + 40, a->y = y + 30;
    std::vector<Object*>& vec = Singleton<GameScene>::instance()->getBulletVec();
    vec.push_back(a);
}