#include "SceneManager.h"
std::vector<Level*> levelList;
std::vector<int> selectNum = std::vector<int>(8, -1);
void SceneManager::SetCurrentState(Scene* scene) {
    currentScene = scene;
    currentScene->OnEnter();
}

void SceneManager::SwitchTo(SceneManager::SceneType type) {
    currentScene->OnExit();
    switch (type) {
    case SceneType::Game:
        currentScene = gameSence;
        break;
    case SceneType::Menu:
        currentScene = menuSence;
        break;
    case SceneType::Select:
        currentScene = selectSence;
        break;
    case SceneType::End:
        currentScene = endScene;
        break;
    case SceneType::Fail:
        currentScene = failScene;
        break;
    default:
        break;
    }
    currentScene->OnEnter();
}

void SceneManager::Input(ExMessage& msg) {
    currentScene->Input(msg);
}

void SceneManager::Draw() {
    currentScene->Draw();
}

void SceneManager::Update(int delta) {
    currentScene->Update(delta);
}

SceneManager::SceneManager() {
    levelList.clear();
    levelList.resize(3,nullptr);
    levelList[0] = new Level(true, false, &imgbg[0], 3, 3);
    levelList[1] =new Level(false, false, &imgbg[1],5,3);
    levelList[2] = new Level(true, true, &imgbg[2],5,3);
    currentLevel = levelList[levelid];
}