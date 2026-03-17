#include "PotatoMine.h"
#include"Resource.h"
#include "GameScene.h"
#include"Singleton.h"

PotatoMine::PotatoMine() {
    type = plantType::PotatoMine;
    this->dy = -5;
    this->damage = 900;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->status = PotatoMineStatus::UnderGround;
    this->action->SetAtlas(atlas);
    this->action->SetLoop(true);
    this->action->SetInterval(150);

    this->timer.SetWaitTime(5000);
    this->timer.SetOneTrigger(true);
    this->timer.SetCallback([this]() {
        status = PotatoMineStatus::Normal;
        isCollide = false;//防止长大后被吃掉
        });
}


void PotatoMine::skills(int delta) {
    if (status == PotatoMineStatus::Normal) { return; }
    timer.Update(delta);//更新计时器
}

void PotatoMine::Draw() {
    switch (status) {
    case PotatoMineStatus::UnderGround:
        putimagePNG(x, y, potatoInit.GetImage(0));
        break;
    case PotatoMineStatus::Normal:
        action->Draw(x, y);
        break;
    case PotatoMineStatus::Boom:
        putimagePNG(x, y, potatoExplode.GetImage(0));
        break;
    default:
        break;
    }
}

void PotatoMine::Collide(Object* obj) {
    if (!obj->isCollide) {  return; }
    if (CheckHitX(obj->x, x - 85, 90) && status == PotatoMineStatus::Normal) {
        //攻击单行单列僵尸
        
        status = PotatoMineStatus::Boom;
        auto& v = Singleton<GameScene>::instance()->getZombies(row);
        for (auto& a : v) {
            if (CheckHitX(a->x, x - 85, 95)) {
                a->blood -= damage;
                mciSendString("play res/music/potato_mine.mp3", 0, 0, 0);
            }
        }
        this->timer.SetWaitTime(1000);
        this->timer.Restart();
        this->timer.SetCallback([this]() {
            used = false;
            });
    }
}