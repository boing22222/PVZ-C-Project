#include "RoadBlockZombie.h"
#include "Resource.h"
RoadBlockZombie::RoadBlockZombie() {
    type = ZombieType::RoadBlockZombie;
    blood = 200;
    isArmor = true;
    for (int i = 0; i < atlas.size() ; i++) {
        atlas[i] = std::make_shared<Atlas>(atlas_zombie[int(type)][i]);
    }
    SetStatus(Zombie::ZombieStatus::Walking);

    this->action->SetLoop(true);
    this->action->SetInterval(60);
}

void RoadBlockZombie::Update(int delta) {
    Zombie::Update(delta);
    if (blood < 100 && isArmor) {
        isArmor = false;
        for (int i = 0; i < atlas.size() - 1; i++) {
            atlas[i] = std::make_shared<Atlas>(atlas_zombie[0][i]);
        }
        SetStatus(status);
    }
}