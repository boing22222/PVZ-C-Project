#include "Trophy.h"
void Trophy::InitTrophy() {
	x = 600;          // 奖杯初始位置（屏幕中央水平位置）
	y = -50;          // 奖杯开始时在屏幕外顶部
	destX = 600;      // 奖杯目标位置（屏幕中央水平位置）
	destY = 200;      // 奖杯目标垂直位置
	Vx = 0;           // 水平速度为 0（不需要水平移动）
	Vy = 1;           // 垂直初速度
	timer = 0;
	isActive = false; // 初始奖杯未激活
}

void Trophy::put_trophy() {
	if (!isActive) {
		isActive = true; // 激活奖杯
		timer = 0;
		Vx = 0;          // 确保水平速度为 0
		Vy = 10;          // 设置垂直初速度
		mciSendString("stop res/music/UraniwaNi.mp3 repeat", 0, 0, 0);
		mciSendString("stop res/music/UraniwaNi.mp3", 0, 0, 0);
		mciSendString("play res/music/win.mp3", 0, 0, 0);
	}
}

void Trophy::updateTrophy(int delta) {
	static int count = 0;
	count += delta;
	if (count <= 100)count++;
	count = 0;
	if (isActive) {
		timer++;

		// 只更新垂直位置
		if (y < destY) {
			y += Vy; // 奖杯缓缓下落
		}
		else {
			y = destY; // 到达目标位置
		}
	}
}

bool Trophy::pass_end_signal() {
	if (y == destY)
	{
		return true;
	}
	return false;
}

void Trophy::drawTrophy() {
	if (isActive) {
		putimagePNG(x, y, &trophy); // 绘制奖杯
	}
}