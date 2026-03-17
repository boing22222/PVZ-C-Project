#pragma once
#include "Scene.h"
#include"Level.h"
extern Scene* gameSence;
extern Scene* menuSence;
extern Scene* selectSence;
extern Scene* endScene;
extern Scene* failScene;
extern std::vector<Level*> levelList;
extern std::vector<int> selectNum;
class SceneManager {//场景管理者
public:
    enum class SceneType {
        Menu,
        Game,
        Select,
        End,
        Fail
    };
    Level* currentLevel = nullptr;
    int levelid = 0;
public:
    SceneManager();
    ~SceneManager() = default;
public:
    void SetCurrentState(Scene* scene);//设置场景
    void SwitchTo(SceneType type);//跳转
    void Input(ExMessage& msg);
    void Update(int delta);
    void Draw();
private:
    Scene* currentScene = nullptr;
    
};
