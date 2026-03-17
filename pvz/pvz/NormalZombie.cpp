#include "NormalZombie.h"
#include "Resource.h"
NormalZombie::NormalZombie() {
    type = ZombieType::NormalZombie;
    blood = 120;
    for (int i = 0; i < atlas.size() ; i++) {
        atlas[i] =std::make_shared<Atlas>(atlas_zombie[int(type)][i]);
    }
    SetStatus(Zombie::ZombieStatus::Walking);
    this->action->SetLoop(true);
    this->action->SetInterval(60);
}