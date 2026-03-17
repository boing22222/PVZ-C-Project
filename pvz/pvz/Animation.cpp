#include "Animation.h"

#include <utility>
#include "Resource.h"

void Animation::Reset() {
    timer = 0;
    idx = 0;
}

void Animation::SetAtlas(Atlas::SP &atlas) {
    Reset();
    this->atlas = atlas;
}

void Animation::SetLoop(bool flag) {
    isLoop = flag;
}

void Animation::SetInterval(int ms) {
    interval = ms;
}

bool Animation::CheckFinished() {
    if (isLoop) {
        return false;
    }
    return idx == atlas->GetSize() - 1;
}

IMAGE* Animation::GetImage() {
    return atlas->GetImage(idx);
}

int Animation::GetIdxFrame() {
    return idx;
}

void Animation::Update(int delta) {
    if (isTrap)return;
    timer += delta;
    if (timer >= interval) {
        timer = 0;
        idx++;
        if (idx >= atlas->GetSize()) {
            idx = isLoop ? 0 : atlas->GetSize() - 1;
            if (!isLoop && callback) {
                callback();
            }
        }
    }
}

void Animation::Draw(int x, int y) const {
    IMAGE* img = atlas->GetImage(idx);
    IMAGE specialEffect;
    if (isCool) {
        CoolImage(img, &specialEffect);
        img = &specialEffect;
    }
    if (isSketch&&idx%2 ) {
        SketchImage(img, &specialEffect);
        img = &specialEffect;
    }
    putimagePNG(x, y, img);
    if (isTrap) {
        putimagePNG(x+67, y + 100, &imgIceTrap);
    }
}

void Animation::SetCallback(std::function<void()>callback) {
    this->callback = std::move(callback);
}

void Animation::SetSketch(bool flag) {
    isSketch = flag;
}

bool Animation::GetSketch() {
    return isSketch;
}
void Animation::SetCool(bool flag) {
    isCool = flag;
}

bool Animation::GetCool() {
    return isCool;
}
void Animation::SetTrap(bool flag) {
    isTrap = flag;
}
bool Animation::GetTrap() {
    return isTrap;
}