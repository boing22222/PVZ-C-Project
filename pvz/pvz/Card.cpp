#include "Card.h"
std::vector<Card*>cardList(8);
int coolTimeList[16] = { 100,100,500,500,700,100,500,100,150,100,100,500,500,400,200,500, };
int costList[16] = { 100,50,50,25,150,175,150,200,0,25,25,75,50,100,325,125,};
void Card::Draw(int x, int y) {//根据cd放遮罩层
	putimagePNG(x, y, &cards[id]);
	if (isCool) {
		int frame = count / (coolTimeList[id] / 48 + 1);
		if (frame > 47)frame = 47;
		putimagePNG(x, y, CoolMask.GetImage(frame));
	}
}
void Card::Update(int delta) {//更新cd
	time+=delta;
	if (time <= 60)return;
	time = 0;
	if (count < coolTimeList[id] && isCool == true) {
		count++;
	}
	else {
		isCool = false;
		count = 0;
	}
}
Card::Card() {
	count = 0;
	coolTime = 0;
	isCool = false;
	cost = 0;
	time = 0;
}