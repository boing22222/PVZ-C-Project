#include "SelectScene.h"
#include"Singleton.h"
SelectScene::SelectScene() {
	fightButton = new Button();
	cardWidth = 50;
	cardHeight = 72;
	isCardSelect.resize(number_plant);
	fightButton->SetRect({ 155,545,150 + 150,550 + 40 });
	fightButton->SetImage(&fightButton1, &fightButton2);
	fightButton->SetCallback([this]() {
		mciSendString("play res/music/seedlift.mp3", 0, 0, 0);
		end.Resume();
		});
}

void SelectScene::OnEnter() {
	mciSendString("play res/music/bg.mp3 repeat", 0, 0, 0);
	//设置按钮和计时器
	fightButton->Reset();
	start.Restart();
	start.SetWaitTime(2910);
	start.SetOneTrigger(true);
	start.SetCallback([this]() {
		start.Pause();
		});
	end.Restart();
	end.SetWaitTime(2070);
	end.SetOneTrigger(true);
	end.Pause();
	end.SetCallback([this]() {
		end.Pause();
		Singleton<SceneManager>::instance()->SwitchTo(SceneManager::SceneType::Game);
	});
}

void SelectScene::Update(int delta) {
	//更新计时器，根据计时器是否运行决定位移
	start.Update(delta);
	end.Update(delta);
	if (start.isRunning) {
		dx += 1;
	}
	else if (end.isRunning) {
		dx -= 1;
	}
}

void SelectScene::Draw() {
	putimage(0 - dx, 0 - dy, Singleton<SceneManager>::instance()->currentLevel->background);
	if (!start.isRunning&&!end.isRunning) {
		int objY = card_cao.getheight();
		putimage(0, 0, &card_cao);
		putimage(0, objY, &selecting_card_bar);
		fightButton->Draw();
		//卡槽卡片
		for (int i = 0; i < selectNum.size(); i++) {
			if (selectNum[i] == -1) { break; }
			int num = selectNum[i];
			int x = 78 + i * (cardWidth + 5);
			int y = 5;
			putimage(x, y, &selectCards[num]);
		}
		//图鉴卡片
		for (int i = 0; i <number_plant; i++) {
			int row = i / 8, col = i % 8;
			int x = 25 + col * (cardWidth + 2);
			int y = objY + 40 + row * (cardHeight + 1);
			putimage(x, y, &selectCards[i]);
			if (isCardSelect[i]) {//如果被选中，加上遮罩层
				putimagePNG(x, y, &imgCardSmallMask);
			}
		}
	}
}

void SelectScene::Input(const ExMessage& msg) {
	fightButton->ProcessEvent(msg);
	static int num = -1, idx = -1;
	
	switch (msg.message) {
	case WM_KEYDOWN:
		if (msg.vkcode == VK_ESCAPE) {
			exit(0);
		}
		break;
	case WM_LBUTTONDOWN:
		//在卡槽
		if (msg.x > 78 && msg.x < 78 + 55 * (selectNum.size()) && msg.y < 5 + cardHeight && msg.y>5) {
			idx = (msg.x - 78) / 55;
			if (selectNum[idx] == -1)idx = -1;
		}
		//在图鉴
		else if (msg.x > 25 && msg.x < 24 + 52 * 8 && msg.y < 76 * 3 + 131 && msg.y>131) {
			num = (msg.x - 25) / 52 + ((msg.y - 131) / 76) * 8;
			if (num >= 16)num = -1;
		}
		break;
	case WM_LBUTTONUP:
		//卡槽
		if (idx != -1) {
			if (selectNum[idx] == -1) {
				break;
			}
			isCardSelect[selectNum[idx]] = false;
			for (int i = idx; i < selectNum.size() - 1; i++) {
				selectNum[i] = selectNum[i + 1];
			}
			selectNum.back() = -1;
			idx = -1;
		}
		//图鉴
		if (num != -1) {
			if (isCardSelect[num]) {
				break;
			}
			for (int i = 0; i < selectNum.size(); i++) {
				if (selectNum[i] == -1) {
					selectNum[i] = num;
					isCardSelect[num] = true;
					break;
				}
			}
			num = -1;
		}
		break;
	default:
		break;
	}
}

void SelectScene::OnExit() {
}