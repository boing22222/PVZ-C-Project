#pragma once
#include<vector>
#include"Resource.h"
class Card
{
public:
	Card();
public:
	void Draw(int x, int y);
	void Update(int delta);
public:
	int x=0, y=0;
	int id;
	int coolTime;
	int count;
	int cost;
	int time = 0;
	bool isCool;
	
};
extern std::vector<Card*>cardList;
extern int coolTimeList[16];
extern int costList[16];
class SelectCard {
public:
	int x, y;     // 卡牌左上角坐标
	int width;    // 卡牌宽度
	int height;   // 卡牌高度
	bool chosen;  // 是否被选中
	int count_card_number; // 被放进卡槽的第几位
};
