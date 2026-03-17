
#include "Plant.h"
//Ö²Îï×ÜÀà
void Plant::Draw() {
    action->Draw(x , y );
}

void Plant::Update(int delta) {
    if (blood <= 0) { used = false; }
    action->Update(delta);
    skills(delta);
}

Plant::plantType Plant::GetType() {
    return this->type;
}
Plant::Plant() {
    action = std::make_shared<Animation>();
    skillTime = 0;
}