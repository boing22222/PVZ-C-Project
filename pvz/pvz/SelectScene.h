#pragma once
#include "Scene.h"
#include "Resource.h"
#include "SceneManager.h"
#include "Button.h"
#include "Timer.h"

class SelectScene :public Scene {//选卡场景
public:
    SelectScene();
    ~SelectScene() = default;
public:
    void OnEnter() override;
    void Update(int delta) override;
    void Draw() override;
    void Input(const ExMessage& msg) override;
    void OnExit() override;
private:
    Button* fightButton;//开战按钮
    std::vector<bool>isCardSelect;//图鉴卡片是否被选
    int cardWidth, cardHeight;
    float dx=0, dy = 0;
    Timer start, end;//两次平移动画的计时器
};
