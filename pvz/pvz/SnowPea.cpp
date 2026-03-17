#include "SnowPea.h"
#include "Resource.h"
#include "GameScene.h"
#include "Singleton.h"
#include "Bullet.h"
SnowPea::SnowPea() {
    type = plantType::SnowPea;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetAtlas(atlas);
    this->action->SetLoop(true);
    this->action->SetInterval(100);
    this->creatSpeed = 2000;
}


void SnowPea::skills(int delta) {
    auto& v = Singleton<GameScene>::instance()->getZombies(row);
    if (v.empty()) { return; }
    skillTime += delta;
    if (skillTime < creatSpeed) { return; }
    skillTime = 0;
    auto* a = new Bullet(Bullet::BulletType::Cool);
    a->row = row;
    a->x = x + 40, a->y = y;
    std::vector<Object*>& vec = Singleton<GameScene>::instance()->getBulletVec();
    vec.push_back(a);
}