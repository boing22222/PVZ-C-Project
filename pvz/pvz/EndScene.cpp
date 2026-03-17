#include "EndScene.h"
#include"Resource.h"
void EndScene::OnEnter() {
}
void EndScene::Draw() {
	putimage(0, 0, &end_of_level);
}
void EndScene::Update(int delta) {

}
void EndScene::Input(const ExMessage& msg) {//点击或esc退出游戏
	if (msg.vkcode == VK_ESCAPE) {
		exit(0);
		return;
	}
	if (msg.message == WM_LBUTTONDOWN)
		exit(0);
}
void EndScene::OnExit() {

}