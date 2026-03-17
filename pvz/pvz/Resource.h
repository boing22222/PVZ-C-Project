#pragma once
#include <graphics.h>
#include"tools.h"
#include"Atlas.h"
#define numberof_zm_type 3
#define number_plant 16
//IMAGE
extern IMAGE imgbg[3];
extern IMAGE imbar;
extern IMAGE car;
extern IMAGE imgCardMask;
extern IMAGE imgCardSmallMask;
extern IMAGE imageBulletNormal;
extern IMAGE imageBulletBlast;
extern IMAGE imgCoolBullet;
extern IMAGE imgCoolBlast;
extern IMAGE imgPuffNormal;
extern IMAGE imgPuffBlast;
extern IMAGE imgIceTrap;
extern IMAGE Shovel_state; //铲子
extern IMAGE end_of_level; //每关结算页面
extern IMAGE next_level_button; // 按下这个按钮进下一关

extern IMAGE menu_scene, button1, button2;
extern IMAGE fightButton1, fightButton2;
extern IMAGE selecting_card_bar;
extern IMAGE game_card_bar;
extern IMAGE card_cao;
extern IMAGE chuansongdai;
extern IMAGE trophy;
extern IMAGE gameFail;
extern IMAGE cards[16];
extern IMAGE selectCards[16];
//Atlas
#pragma region 植物
extern std::vector<Atlas> atlas_plant;
extern Atlas nutInjured;
extern Atlas nutNearDie;
extern Atlas potatoInit;
extern Atlas potatoExplode;
extern Atlas cherryBombBoom;
extern Atlas chomperAttack;
extern Atlas chomperDigest;
extern Atlas puffShroomSleep;
extern Atlas sunShroomSleep;
extern Atlas sunShroomBig;
extern Atlas scaredyShroomSleep;
extern Atlas scaredyShroomCry;
extern Atlas iceShroomSleep;
extern Atlas iceShroomExplode;
extern Atlas squashAim;
extern Atlas squashAttack;
extern Atlas jalapenoBoom;

#pragma endregion

#pragma region 僵尸
extern std::vector<std::vector<Atlas>>atlas_zombie;
#pragma endregion

#pragma region 杂项
extern Atlas CoolMask;
extern Atlas atlasSunShine;
extern Atlas atlasSunShineSmall; 
extern Atlas atlasSunShineBig;
#pragma endregion

extern void loadAllImage();

