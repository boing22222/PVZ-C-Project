#include "StaticObj.h"

void StaticObj::Draw() {
    if (isDraw) {
        putimagePNG(x, y+dy, img);
    }
}

void StaticObj::Update(int delta) {
    Object::Update(delta);
}

void StaticObj::SetImage(IMAGE* img) {
    this->img = img;
}