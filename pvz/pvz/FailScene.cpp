#include "FailScene.h"
#include"Singleton.h"
#include"SceneManager.h"
#include"Resource.h"
void FailScene::OnEnter() {
}
void FailScene::Draw() {
	putimage(0, 0, &gameFail);
}
void FailScene::Update(int delta) {

}
void FailScene::Input(const ExMessage& msg) {//点击重新开始，esc退出
	if (msg.vkcode == VK_ESCAPE) {
		exit(0);
		return;
	}
	if (msg.message == WM_LBUTTONDOWN)
		Singleton<SceneManager>::instance()->SwitchTo(SceneManager::SceneType::Select);
}
void FailScene::OnExit() {

}