#include "Bullet.h"

void Bullet::Collide(Object* obj) {//子弹碰撞效果
    if (type == BulletType::Blast || !obj->isCollide) { return; }
    if (CheckHitX(x, obj->x + 80, 30)) {
        obj->blood -= damage;
        if (type == BulletType::Cool) {
            obj->SetEffect(1);
        }
        else {
            obj->SetEffect(0);
        }
        SetType(BulletType::Blast);
    }
}

void Bullet::Draw() {
    if (type != BulletType::Blast) {
        putimagePNG(x, y, img);
    }
    else {
        putimagePNG(x, y, imgBlast);
    }
}

void Bullet::Update(int delta) {//更新位置
    timer += delta;
    if (timer < 30) { return; }
    timer = 0;
    if (x >= 900) {
        used = false;
    }
    if (type != BulletType::Blast) {
        x += speed;
    }
    else {
        idx++;
        if (idx == 2) {
            used = false;
        }
    }
}

Bullet::Bullet(BulletType type) {
    idx = 0;
    timer = 0;
    speed = 10;
    damage = 13;
    SetType(type);
}

void Bullet::SetImage(IMAGE* img, IMAGE* blast) {
    this->img = img;
    this->imgBlast = blast;
}

void Bullet::SetType(Bullet::BulletType type) {
    switch (type) {
    case BulletType::Normal:
        SetImage(&imageBulletNormal, &imageBulletBlast);
        break;
    case BulletType::Cool:
        SetImage(&imgCoolBullet, &imgCoolBlast);
        break;
    case BulletType::Blast:
        break;
    case BulletType::Puff:
        SetImage(&imgPuffNormal, &imgPuffBlast);
        break;
    }
    this->type = type;
}
