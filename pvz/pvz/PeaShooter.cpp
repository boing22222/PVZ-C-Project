#include "PeaShooter.h"
#include "Bullet.h"
#include "GameScene.h"
#include "Singleton.h"

PeaShooter::PeaShooter() {
    type = plantType::PeaShooter;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetAtlas(atlas);
    this->action->SetLoop(true);
    this->action->SetInterval(75);
    this->creatSpeed = 2000;
}


void PeaShooter::skills(int delta) {
    auto& v = Singleton<GameScene>::instance()->getZombies(row);
    if (v.empty()) { return; }//没有目标不攻击
    skillTime += delta;
    if (skillTime < creatSpeed) { return; }//时间限制
    skillTime = 0;
    auto* a = new Bullet(Bullet::BulletType::Normal);
    a->row = row;
    a->x = x + 40, a->y = y;
    std::vector<Object*>& vec = Singleton<GameScene>::instance()->getBulletVec();//新子弹加入子弹池
    vec.push_back(a);
}