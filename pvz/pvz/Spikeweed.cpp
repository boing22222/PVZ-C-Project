#include "Spikeweed.h"
#include"Resource.h"
#include"Singleton.h"
#include"GameScene.h"
Spikeweed::Spikeweed() {
	type = plantType::Spikeweed;
	damage = 13;
	this->dy = 50;
	attackSpeed = 600;
	Atlas::SP atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
	this->action->SetAtlas(atlas);
	this->action->SetLoop(true);
	this->action->SetInterval(100);
	this->isCollide = false;
}
void Spikeweed::skills(int delta) {
	auto& v = Singleton<GameScene>::instance()->getZombies(row);
	if (v.empty()) { return; }
	skillTime += delta;
	if (skillTime < attackSpeed) { return; }
	skillTime = 0;
	for (auto& obj : v) {
		if (!obj->isCollide)continue;
		if (CheckHitX(obj->x, x - 95, 95)) {
			obj->blood -= damage;
			obj->SetEffect(0);
		}
	}
}