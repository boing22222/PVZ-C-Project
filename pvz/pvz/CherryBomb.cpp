#include "CherryBomb.h"
#include"GameScene.h"
#include"Singleton.h"
CherryBomb::CherryBomb() {
    type = plantType::CherryBomb;
    damage = 2500;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetAtlas(atlas);
    this->action->SetLoop(false);
    this->action->SetInterval(100);
    this->action->SetCallback([this]() {
        Boom();
        action->Reset();
        Atlas::SP atlas = std::make_shared<Atlas>(cherryBombBoom);
        action->SetAtlas(atlas);
        action->SetCallback([this]() {//第二段播放完清除
            used = false;
            });
        });
}


void CherryBomb::skills(int delta) {
    Plant::skills(delta);
}

void CherryBomb::Boom() {
    //三行三列内造成伤害
    for (int i = -1; i < 2; i++) {
        int row = this->row + i;
        if (row < 0 || row>4) { continue; }
        auto& v = Singleton<GameScene>::instance()->getZombies(row);
        for (auto& a : v) {
            if (a->col >= col - 1 && a->col <= col + 1) {
                a->blood -= damage;
                mciSendString("play res/music/cherrybomb.mp3", 0, 0, 0);
            }
        }
    }
}