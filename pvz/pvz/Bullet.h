#pragma once
#include "Object.h"
#include "Animation.h"
#include "Resource.h"
#include <functional>

class Bullet : public Object {
public:
    enum class BulletType {//ËÄÖÖ×Óµ¯
        Normal, Cool,  Blast,Puff
    };
public:
    ~Bullet() override = default;
    explicit Bullet(Bullet::BulletType type);
public:
    void Update(int delta) override;
    void Draw() override;
    void Collide(Object* obj) override;
    void SetImage(IMAGE* img, IMAGE*  blast);
    void SetType(BulletType type);
public:
    int speed;
    int damage;
    BulletType type;
protected:
    IMAGE* img;
    IMAGE* imgBlast;
    int timer, idx;
};
