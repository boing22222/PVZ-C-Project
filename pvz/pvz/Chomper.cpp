#include "Chomper.h"
#include"Resource.h"
#include"GameScene.h"
#include"Singleton.h"
Chomper::Chomper() {
    type = plantType::Chomper;
    this->temp = nullptr;
    this->dy -= 25;
    this->damage = 900;
    this->SetStatus(ChomperStatus::Normal);
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetLoop(true);
    this->action->SetInterval(75);
    this->timer.SetWaitTime(15000);
    this->timer.SetOneTrigger(true);
    this->timer.SetCallback([this]() {//计时器结束后回到normal
        SetStatus(ChomperStatus::Normal);
        });
}



void Chomper::SetStatus(Chomper::ChomperStatus status) {
    this->status = status;
    Atlas::SP atlas;
    switch (status) {
    case ChomperStatus::Normal:
        atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
        break;
    case ChomperStatus::Attack:
        atlas = std::make_shared<Atlas>(chomperAttack);
        action->SetLoop(false);
        action->SetCallback([this]() {//攻击动画结束后吃掉
            if (damage >= temp->blood) {
                SetStatus(ChomperStatus::Digestion);
                temp->used = false;
            }
            else {
                action->Reset();
                temp->blood -= damage;
                temp->SetEffect(0);
            }
            });
        break;
    case ChomperStatus::Digestion:
        atlas = std::make_shared<Atlas>(chomperDigest);
        action->SetLoop(true);
        this->timer.Restart();
        break;
    }
    this->action->SetAtlas(atlas);
}

void Chomper::Collide(Object* obj) {
    if (!obj->isCollide) { return; }
    if (CheckHitX(obj->x, x - 50, 150) && status == ChomperStatus::Normal) {//normal下才能进入攻击
        SetStatus(ChomperStatus::Attack);
        temp = obj;
    }
}

void Chomper::skills(int delta) {//更新计时器
    if (status == ChomperStatus::Digestion) {
        timer.Update(delta);
    }
}
