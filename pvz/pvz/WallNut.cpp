#include "WallNut.h"
#include"Resource.h"
WallNut::WallNut() {
    type = plantType::WallNut;
    this->SetStatus(WallNutStatus::Normal);
    this->action->SetLoop(true);
    this->action->SetInterval(75);
    this->blood = 1800;
}


void WallNut::SetStatus(WallNut::WallNutStatus status) {
    this->status = status;
    Atlas::SP atlas;
    switch (status) {
    case WallNutStatus::Normal:
        atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
        break;
    case WallNutStatus::Injured:
        atlas = std::make_shared<Atlas>(nutInjured);
        break;
    case WallNutStatus::NearDeath:
        atlas = std::make_shared<Atlas>(nutNearDie);
        break;
    }
    this->action->SetAtlas(atlas);
}

void WallNut::skills(int delta) {
    skillTime += delta;
    if (skillTime < 60) { return; }
    skillTime = 0;
    if (blood < 1200 && status == WallNutStatus::Normal) {
        SetStatus(WallNutStatus::Injured);
    }
    if (blood < 600 && status == WallNutStatus::Injured) {
        SetStatus(WallNutStatus::NearDeath);
    }
}

