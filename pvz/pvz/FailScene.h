#pragma once
#include "Scene.h"
class FailScene :public Scene
{
public:
    FailScene() = default;
    ~FailScene() = default;
public:
    void OnEnter() override;
    void Update(int delta) override;
    void Draw() override;
    void Input(const ExMessage& msg) override;
    void OnExit() override;
};
