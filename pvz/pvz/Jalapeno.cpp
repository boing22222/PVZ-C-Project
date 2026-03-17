#include "Jalapeno.h"
#include"GameScene.h"
#include"Singleton.h"
Jalapeno::Jalapeno() {
    type = plantType::Jalapeno;
    damage = 2500;
    Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
    this->action->SetAtlas(atlas);
    this->action->SetLoop(false);
    this->action->SetInterval(100);
    this->action->SetCallback([this]() {
        Boom();//类似樱桃炸弹
        x = 144;//贴图位置问题，火焰必须从最左端到右
        dy = -15;
        action->Reset();
        Atlas::SP atlas = std::make_shared<Atlas>(jalapenoBoom);

        action->SetAtlas(atlas);
        action->SetCallback([this]() {
            used = false;
            });
        });
}
void Jalapeno::skills(int delta) {
    Plant::skills(delta);
}
void Jalapeno::Boom() {
    //对当前行僵尸
    auto& v = Singleton<GameScene>::instance()->getZombies(row);
    for (auto& a : v) {
        if (a->x < 880) {
            a->blood -= damage;
            mciSendString("play res/music/jalapeno.mp3", 0, 0, 0);
        }
    }
}