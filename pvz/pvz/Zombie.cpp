
#include"Zombie.h"
#include"SceneManager.h"
#include"Singleton.h"
Zombie::Zombie() {
    atlas.resize(4);
    isArmor = false;
    action = std::make_shared<Animation>();
    speed = 2;
    timer = 0;
    count = 0;
    x = 850 + rand() % 100;
    row = Singleton<SceneManager>::instance()->currentLevel->rows==5?rand() % 5:1+rand()%3;
    y = 30 + 100 * row;
    damage = 20;
    sketch.SetCallback([this]() {
        action->SetSketch(false);
        });
    sketch.SetOneTrigger(false);
    sketch.SetWaitTime(300);
    cool.SetCallback([this]() {
        action->SetCool(false);
        });
    cool.SetOneTrigger(false);
    cool.SetWaitTime(3000);
    freeze.SetCallback([this]() {
        action->SetTrap(false);
        this->SetEffect(1);
        });
    freeze.SetWaitTime(6000);
    cool.SetOneTrigger(false);
}

void Zombie::Draw() {
    action->Draw(x, y);
}

void Zombie::Update(int delta) {
    action->Update(delta);
    timer += delta;
    if (x > 1000)this->used = false;
    if (action->GetTrap()) {
        freeze.Update(delta);
        this->SetEffect(1);
    }
    if (action->GetCool()) {
        cool.Update(delta);
    }
    if (action->GetSketch()) {
        sketch.Update(delta);
    }
    
    int t = action->GetCool() ? 240 : 120;
    if (timer < t) { return; }
    timer = 0;
    col = ((x - 144) / 81) + 1;
    if (blood<0&& blood>-1000 && status != ZombieStatus::FallDown) {
        SetStatus(ZombieStatus::FallDown);
        action->SetTrap(false);
        action->SetCool(false);
        cool.Restart();
        cool.Pause();
        freeze.Restart();
        freeze.Pause();
        isCollide = false;
        action->SetLoop(false);
        action->SetCallback([this]() {
            
            used = false;
            });
    }
    else if (blood <= -1000 && status != ZombieStatus::Ash) {
        action->SetTrap(false);
        action->SetCool(false);
        cool.Restart();
        cool.Pause();
        freeze.Restart();
        freeze.Pause();
        isCollide = false;
        SetStatus(ZombieStatus::Ash);
        action->SetLoop(false);
        action->SetCallback([this]() {
            used = false;
            });
    }
    
    switch (status) {
    case ZombieStatus::Walking:
        if(!action->GetTrap())x -= speed;
        if (x < 0) {
            Singleton<SceneManager>::instance()->SwitchTo(SceneManager::SceneType::Fail);
            used = false;
        }
        break;
    case ZombieStatus::Attack:
        break;
    case ZombieStatus::FallDown:
        break;
    default:
        break;
    }
}

void Zombie::Collide(Object* obj) {
    if (action->GetTrap())return;
    if (!obj->isCollide) { return; }
    if (status != ZombieStatus::Attack && status != ZombieStatus::Walking) { return; }
    if (CheckHitX(x, obj->x - 70, 30)) {
        if (status == ZombieStatus::Walking) {
            SetStatus(ZombieStatus::Attack);
        }
        count++;
        if (count > 30) {
            count = 0;
            obj->blood -= damage;
            mciSendString("play res/music/chomp.mp3", 0, 0, 0);
        }
        if (!obj->used) {
            SetStatus(ZombieStatus::Walking);
        }
    }
}

void Zombie::SetStatus(Zombie::ZombieStatus status) {
    this->status = status;
    action->Reset();
    action->SetAtlas(atlas[int(status)]);
}

void Zombie::SetEffect(int type) {
    if (GetType() == ZombieType::BucketZombie) {
        PlaySound(TEXT("res/music/shieldhit.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else {
        PlaySound(TEXT("res/music/splat2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    if (type == 0) {
        action->SetSketch(true);
        sketch.Restart();
    }
    else if (type == 1) {
        if (!action->GetCool()) {
            action->SetCool(true);
            mciSendString("play res/music/frozen.mp3", 0, 0, 0);
        }
        cool.Restart();
    }
    else if (type == 3) {
        if (!action->GetCool()) {
            action->SetCool(true);
            mciSendString("play res/music/frozen.mp3", 0, 0, 0);
        }
        if (!action->GetTrap()) {
            action->SetTrap(true);
        }
        cool.Restart();
        freeze.Restart();
    }
}
