#include "PuffShroom.h"
#include"Resource.h"
#include"GameScene.h"
#include"Singleton.h"
#include"SceneManager.h"
#include"Bullet.h"
//类似豌豆射手，加个白天睡觉的判断
PuffShroom::PuffShroom() {
	type = plantType::PuffShroom;
    dy = -20;
    if (Singleton<SceneManager>::instance()->currentLevel->isDay) {
        Atlas::SP atlas = std::make_shared<Atlas>(puffShroomSleep);
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
void PuffShroom::skills(int delta) {
    if (Singleton<SceneManager>::instance()->currentLevel->isDay)return;
    auto& v = Singleton<GameScene>::instance()->getZombies(row);
    if (v.empty()) { return; }
    bool hasZ = false;

    for (auto& z : v) {
        if (z->x >= x-60 && z->x <= x + 240){
            hasZ = true;
            break;
        }
    }
    if (!hasZ)return;
    skillTime += delta;
    if (skillTime < creatSpeed) { return; }
    skillTime = 0;
    auto* a = new Bullet(Bullet::BulletType::Puff);
    a->row = row;
    a->x = x + 40, a->y = y+ 50;
    std::vector<Object*>& vec = Singleton<GameScene>::instance()->getBulletVec();
    vec.push_back(a);
}