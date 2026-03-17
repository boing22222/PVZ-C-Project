#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"
class MenuScene :public Scene {//²Ëµ¥³¡¾°
public:
    MenuScene();
    ~MenuScene() = default;
public:
    void OnEnter() override;
    void Update(int delta) override;
    void Draw() override;
    void Input(const ExMessage& msg)override;
    void OnExit()override;
private:
    IMAGE* menu;
    Button* startButton;
};


