#include "BucketZombie.h"
#include "Resource.h"
BucketZombie::BucketZombie() {
    type = ZombieType::BucketZombie;
    blood = 500;
    isArmor = true;
    for (int i = 0; i < atlas.size() ; i++) {
        atlas[i] = std::make_shared<Atlas>(atlas_zombie[int(type)][i]);
    }
    SetStatus(Zombie::ZombieStatus::Walking);

    this->action->SetLoop(true);
    this->action->SetInterval(60);
}

void BucketZombie::Update(int delta) {
    Zombie::Update(delta);
    if (blood < 100 && isArmor) {
        isArmor = false;
        for (int i = 0; i < atlas.size() ; i++) {
            atlas[i] = std::make_shared<Atlas>(atlas_zombie[0][i]);
        }
        SetStatus(status);
    }
}