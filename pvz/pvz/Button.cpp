#include "Button.h"
#include "Button.h"

bool Button::CheckHit(int x, int y) {//点击位置
    return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
}

void Button::ProcessEvent(const ExMessage& msg) {
    switch (msg.message) {
    case WM_LBUTTONDOWN://按下换贴图
        if (status==Status::Idle&&CheckHit(msg.x, msg.y)) {
            status = Status::Push;
        }
        break;
    case WM_LBUTTONUP://弹起用回调
        if (status == Status::Push && callback) {
            callback();
        }
        break;
    default:
        break;
    }
}

void Button::Draw() {
    switch (status) {
    case Status::Idle:
        putimagePNG(region.left, region.top, imgIdle);
        break;
    case Status::Push:
        putimagePNG(region.left, region.top, imgPush);
        break;
    default:
        break;
    }
}

void Button::SetRect(RECT rect) {
    region = rect;
}

void Button::SetImage(IMAGE* image1, IMAGE* image2) {
    imgIdle = image1;
    imgPush = image2;
}

void Button::SetCallback(std::function<void()> callback) {
    this->callback = callback;
}

void Button::Reset() {
    status = Status::Idle;
}