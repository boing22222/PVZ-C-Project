#include "Repeater.h"
#include"Resource.h"
#include"GameScene.h"
#include"Singleton.h"
#include "Bullet.h"
Repeater::Repeater() {
    type = plantType::Repeater;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetAtlas(atlas);
    this->action->SetLoop(true);
    this->action->SetInterval(75);
    this->creatSpeed = 2000;
    timer.SetWaitTime(300);
    timer.SetOneTrigger(true);
    timer.SetCallback([this]() {
        //第一次射击后开始计时器，计时器结束后再射一发
        auto* a = new Bullet(Bullet::BulletType::Normal);
        a->row = row;
        a->x = x + 40, a->y = y;
        std::vector<Object*>& vec = Singleton<GameScene>::instance()->getBulletVec();
        vec.push_back(a);
        timer.Pause();
        });
    timer.Pause();
}


void Repeater::skills(int delta) {
    timer.Update(delta);
    auto& v = Singleton<GameScene>::instance()->getZombies(row);
    if (v.empty()) { return; }
    skillTime += delta;
    if (skillTime < creatSpeed) { return; }
    skillTime = 0;
    auto* a = new Bullet(Bullet::BulletType::Normal);
    a->row = row;
    a->x = x + 40, a->y = y;
    std::vector<Object*>& vec = Singleton<GameScene>::instance()->getBulletVec();
    vec.push_back(a);
    timer.Restart();
}