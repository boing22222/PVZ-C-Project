
#include "MenuScene.h"
#include "Singleton.h"
void MenuScene::OnEnter() {
    startButton->Reset();//¿ªÊ¼°´Å¥
    mciSendString("play res/music/bg.mp3", 0, 0, 0);
}

void MenuScene::Update(int delta) {

}

void MenuScene::Draw() {
    putimage(0, 0, menu);
    startButton->Draw();
}

void MenuScene::Input(const ExMessage& msg) {
    if (msg.vkcode == VK_ESCAPE) {
        exit(0);
        return;
    }
    startButton->ProcessEvent(msg);
}

void MenuScene::OnExit() {
    if (startButton != nullptr) {
        delete startButton;
        startButton = nullptr;
    }
}

MenuScene::MenuScene() {
    menu = &menu_scene;
    startButton = new Button();

    startButton->SetRect({ 475,80,475 + 330,80 + 150 });
    startButton->SetImage(&button1,&button2);
    startButton->SetCallback([this]() {
        Singleton<SceneManager>::instance()->SwitchTo(SceneManager::SceneType::Select);
        });
}