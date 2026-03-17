#include "Squash.h"
#include"Resource.h"
#include"Singleton.h"
#include"GameScene.h"
Squash::Squash() {
	type = plantType::Squash;
	temp = nullptr;
	this->dy = -150;
	this->dx = -20;
	this->SetStatus(SquashStatus::Normal);
	this->action->SetLoop(true);
	this->action->SetInterval(75);
}
void Squash::SetStatus(SquashStatus status) {
	this->status = status;
	Atlas::SP atlas;
	switch (status) {
	case SquashStatus::Normal:
		atlas = std::make_shared<Atlas>(atlas_plant[int(type)]);
		break;
	case SquashStatus::Attack:
		atlas = std::make_shared<Atlas>(squashAttack);
		action->SetLoop(false);
		action->SetCallback([this]() {
			auto& v = Singleton<GameScene>::instance()->getZombies(row);
			for (auto& a : v) {
				if (CheckHitX(a->x, x-90, 100))
					a->used = false;
			}
			this->used = false;
			});
		break;
	case SquashStatus::Aim:
		atlas = std::make_shared<Atlas>(squashAim);
		action->SetLoop(false);
		action->SetCallback([this]() {
			if (temp) {
				if (temp->used)
					this->x = temp->x+20;
				else
					this->x = temp_x;
			}
			else
				this->x = temp_x;
			this->SetStatus(SquashStatus::Attack);
			});
		break;
	}
	this->action->SetAtlas(atlas);
}
void Squash::Collide(Object* obj) {

	if (!obj->isCollide) { return; }
	if (CheckHitX(obj->x, x-150, 200) && status == SquashStatus::Normal) {
		SetStatus(SquashStatus::Aim);
		temp = obj;
		temp_x = temp->x;
	}
}
void Squash::skills(int delta) {
}