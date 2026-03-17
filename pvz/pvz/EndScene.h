#pragma once
#include "Scene.h"
class EndScene :public Scene
{
public:
    EndScene()=default;
    ~EndScene() = default;
public:
    void OnEnter() override;
    void Update(int delta) override;
    void Draw() override;
    void Input(const ExMessage& msg) override;
    void OnExit() override;
};

