#include "SunShine.h"
#include"Resource.h"
#include<cmath>
void SunShine::Update(int delta) {
    action->Update(delta);
    switch (status) {
    case SunStatus::SUNSHINE_DOWN://下落
        t += speed;
        curx = x1 + t * (x4 - x1);
        cury = y1 + t * (y4 - y1);
        if (t >= 1) {
            status = SunStatus::SUNSHINE_GROUND;
            timer = 0;
            t = 0;
        }
        break;
    case SunStatus::SUNSHINE_GROUND://静止
        timer += delta;
        if (timer >= 4000) {
            used = false;
            timer = 0;
        }
        break;
    case SunStatus::SUNSHINE_COLLECT://向阳光槽移动
        t += speed;
        curx = x1 + t * (x4 - x1);
        cury = y1 + t * (y4 - y1);
        if (t >= 1) {
            used = false;
        }
        break;
    case SunStatus::SUNSHINE_PRODUCT://三次贝塞尔曲线轨迹，x1y1是起点，x4y4是终点
        t += speed;
        curx = (1 - t) * (1 - t) * (1 - t) * x1 + 3 * (1 - t) * (1 - t) * t * x2 + 3 * (1 - t) * t * t * x3 + t * t * t * x4;
        cury = (1 - t) * (1 - t) * (1 - t) * y1 + 3 * (1 - t) * (1 - t) * t * y2 + 3 * (1 - t) * t * t * y3 + t * t * t * y4;
        if (t >= 1) {
            status = SunStatus::SUNSHINE_GROUND;
            timer = 0;
            t = 0;
        }
        break;
    default:
        break;
    }
}

void SunShine::Draw() {
    x = (int)curx;
    y = (int)cury;
    if (used) {
        action->Draw(x,y);
    }
}

SunShine::SunShine(SunType type) {
    this->type = type;
    action = std::make_shared<Animation>();
    switch (this->type) {
    case SunType::Small: {
        Atlas::SP atlas = std::make_shared<Atlas>(atlasSunShineSmall);
        this->action->SetAtlas(atlas);
        value = 15;
        break;
    }
    case SunType::Normal: {
        Atlas::SP atlas = std::make_shared<Atlas>(atlasSunShine);
        this->action->SetAtlas(atlas);
        value = 25;
        break;
    }
    case SunType::Big: {
        Atlas::SP atlas = std::make_shared<Atlas>(atlasSunShineBig);
        this->action->SetAtlas(atlas);
        value = 50;
        break;
    }
    }
    
    this->action->SetLoop(true);
    this->action->SetInterval(75);

    status = SunShine::SunStatus::SUNSHINE_DOWN;
    x1 = 260 + rand() % 540;
    y1=60;
    x4 = x1;
    y4=230 + (rand() % 4) * 90;
    t = 0;
    float distance = sqrt((x1 - x4)* (x1 - x4)+ (y1 - y4)* (y1 - y4));
    float off = 1;
    speed = 1.0 / (distance / off);
}


SunShine* SunShine::creatSunShine(int x, int y,SunType type) {
    SunShine* a = new SunShine(type);
    a->status = SunShine::SunStatus::SUNSHINE_PRODUCT;
    a->x1 = x;
    a->y1 = y;
    int w = (40 + rand() % 10) * (rand() % 2 ? 1 : -1);
    a->x4 = x + w;//终点横坐标随机偏移
    a->y4=y;
    a->x2 = a->x1 + w * 0.3;//两个中间点坐标在起点上方100，偏移30%和70%处，位置网上找的
    a->y2= a->y1 - 100;
    a->x3 = a->x1 + w * 0.7;
    a->y3= a->y1 - 100;
    a->t = 0;
    a->speed = 0.06;
    return a;
}

void SunShine::Collect() {
    status = SunShine::SunStatus::SUNSHINE_COLLECT;
    t = 0;
    x1 = curx;
    y1=cury;
    //阳光槽
    x4 = 150;
    y4 = 0; 
    float distance = sqrt((x1 - x4) * (x1 - x4) + (y1 - y4) * (y1 - y4));
    float off = 50;
    speed = 1.0 / (distance / off);
}
