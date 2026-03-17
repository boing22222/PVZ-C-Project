#include "ThreePeater.h"
#include "Bullet.h"
#include "GameScene.h"
#include "Singleton.h"

ThreePeater::ThreePeater() {
    type = plantType::ThreePeater;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetAtlas(atlas);
    this->action->SetLoop(true);
    this->action->SetInterval(75);
    this->creatSpeed = 2000;
}


void ThreePeater::skills(int delta) {
    bool hasz = false;
    for (int i = -1; i < 2; i++) {
        int row = this->row + i;
        if (row < 0 || row>4) { continue; }
        auto& v = Singleton<GameScene>::instance()->getZombies(row);
        if (!v.empty()) { hasz = true; }
    }
    if (!hasz)return;
    skillTime += delta;
    if (skillTime < creatSpeed) { return; }
    skillTime = 0;
    std::vector<Object*>& vec = Singleton<GameScene>::instance()->getBulletVec();
    for (int i = -1; i < 2; i++) {
        int row = this->row + i;
        if (row < 0 || row>4) { continue; }
        auto* a = new Bullet(Bullet::BulletType::Normal);
        a->row = row;
        a->x = x + 40, a->y = y+i*102;
        vec.push_back(a);
    }
}